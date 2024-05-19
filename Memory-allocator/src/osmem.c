// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/errno.h>

#include "osmem.h"
#include "block_meta.h"

#define MMAP_THRESHOLD (128 * 1024)
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

struct block_meta *global_base;


static struct block_meta *best_fit(size_t size) {
    struct block_meta *current = global_base;
    struct block_meta *best_block = NULL;
    while (current != NULL) {
        if (current->status == STATUS_FREE && current->size >= size) {
            if (!best_block || current->size < best_block->size) {
                best_block = current;
            }
        }
        current = current->next;
    }
    return best_block;
}

static void first_time_prealloc(void) {
    global_base = sbrk(0);
    global_base = sbrk(MMAP_THRESHOLD);
    global_base->size = MMAP_THRESHOLD;
    global_base->status = STATUS_FREE;
    global_base->next = NULL;
}

static void split_block(struct block_meta *block, size_t size) {
    struct block_meta *new_block = (void *)block + size;
    new_block->size = block->size - size;
    new_block->status = STATUS_FREE;
    new_block->next = block->next;
    block->size = size;
    block->next = new_block;
}

static struct block_meta *coalesce_blocks(void) {
    struct block_meta *current = global_base;
    struct block_meta *prev = NULL;

    while (current != NULL) {
        if (current->status == STATUS_FREE) {
            if (prev && prev->status == STATUS_FREE) {
                prev->size = prev->size + current->size;
                prev->next = current->next;
                current = prev;
            }
            if (current->next && current->next->status == STATUS_FREE) {
                current->size = current->size + current->next->size;
                current->next = current->next->next;
            }
        }
        prev = current;
        current = current->next;
    }
    return prev;
}

static struct block_meta *space_malloc(size_t size) {
    struct block_meta *block;

    if (size < MMAP_THRESHOLD) {
        block = sbrk(0);
        block = sbrk(size);
        block->size = size;
        block->status = STATUS_ALLOC;
        block->next = NULL;
    } else {
        block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        block->size = size;
        block->status = STATUS_MAPPED;
        block->next = NULL;
    }
    return block;
}

static struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta *)(ptr - ALIGN(sizeof(struct block_meta)));
}

void *os_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    int aligned_size = ALIGN(sizeof(struct block_meta)) + ALIGN(size);

    if (!global_base && aligned_size < MMAP_THRESHOLD) {
        first_time_prealloc();
    }

    struct block_meta *last = coalesce_blocks();
    struct block_meta *block = best_fit(aligned_size);

    if (block) {
        if (block->size >= aligned_size + ALIGN(sizeof(struct block_meta) + ALIGN(1))) {
            split_block(block, aligned_size);
        }
        block->status = STATUS_ALLOC;
        return (void *)block + ALIGN(sizeof(struct block_meta));
    }

    if (last && last->status == STATUS_FREE) {
        block = space_malloc(aligned_size - last->size);

        if (!block) {
            return NULL;
        }
        last->size = last->size + block->size;
        block = last;

        if (block->size >= aligned_size + ALIGN(sizeof(struct block_meta) + ALIGN(1))) {
            split_block(block, aligned_size);
        }
        block->status = STATUS_ALLOC;
        return (void *)block + ALIGN(sizeof(struct block_meta));
    }

    block = space_malloc(aligned_size);

    if (!block) {
        return NULL;
    }
        if (block->status == STATUS_ALLOC) {
            last->next = block;
        }

        if (last->status == STATUS_FREE) {
            last->size = last->size + block->size;
            last->next = block->next;
        }

    return (void *)block + ALIGN(sizeof(struct block_meta));
}

void os_free(void *ptr) {
    if (!ptr) {
        return;
    }

    struct block_meta *block = get_block_ptr(ptr);

    if (block->status == STATUS_ALLOC) {
        block->status = STATUS_FREE;
    } else {
        munmap(block, block->size);
    }
}


void *os_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb < size) {
        return NULL;
    }
    size_t total_size = nmemb * size;

    if (total_size / nmemb != size) {
        return NULL;
    }

    void *ptr = os_malloc(total_size);

    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}


void *os_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return os_malloc(size);
    }

    if (size == 0) {
        os_free(ptr);
        return NULL;
    }

    struct block_meta *block = get_block_ptr(ptr);

    if (block->status == STATUS_FREE) {
        return NULL;
    }

    size_t old_size = block->size - ALIGN(sizeof(struct block_meta));

    if (size <= old_size) {
        if (old_size - size > ALIGN(sizeof(struct block_meta) + ALIGN(1))) {
            split_block(block, size + ALIGN(sizeof(struct block_meta)));
        }
        return ptr;
    }

    struct block_meta *next = block->next;

    while (next && next->status == STATUS_FREE) {
        if (block->size + next->size >= size + ALIGN(sizeof(struct block_meta) + ALIGN(1))) {
            block->size = block->size + next->size;
            block->next = next->next;

            if (block->size - size > ALIGN(sizeof(struct block_meta) + ALIGN(1))) {
                split_block(block, size + ALIGN(sizeof(struct block_meta)));
            }

            return ptr;
        }

        block->size = block->size + next->size;
        block->next = next->next;

        next = block->next;
    }

    void *new_ptr = os_malloc(size);

    if (new_ptr) {
        memcpy(new_ptr, ptr, old_size);
        os_free(ptr);
    }

    return new_ptr;
}
