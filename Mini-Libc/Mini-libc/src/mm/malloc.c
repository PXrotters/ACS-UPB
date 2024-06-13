// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

void *malloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }

    size_t total_size = size + sizeof(size_t);
    void *mem = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        return NULL;
    }

    *(size_t *)mem = total_size;

    return (void *)((char *)mem + sizeof(size_t));
}

void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t total_size = nmemb * size;

    void *mem = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        return NULL;
    }

    memset(mem, 0, total_size);

    return mem;
}

void free(void *ptr)
{
	 if (ptr != NULL) {
        void *block_start = (char *)ptr - sizeof(size_t);

        size_t total_size = *((size_t *)block_start);

        if (munmap(block_start, total_size) == -1) {
            // Handle deallocation failure
        }
    }
}

void *realloc(void *ptr, size_t size)
{
	  if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        return malloc(size);
    }

    size_t total_size = size;

    void *new_ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (new_ptr == MAP_FAILED) {
        return NULL;
    }

    size_t old_size = *((size_t*) ptr);
    if (old_size > size) old_size = size;
    memcpy(new_ptr, ptr, old_size);

    munmap(ptr, 0);

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb > 0 && SIZE_MAX / nmemb < size) {
        return NULL;
    }

    size_t total_size = nmemb * size;

    if (ptr == NULL) {
        return malloc(total_size);
    } else {
        void *new_ptr = malloc(total_size);
        if (new_ptr == NULL) {
            return NULL;
        }

        size_t old_size = *((size_t *)ptr);
        if (old_size > total_size) old_size = total_size;
        memcpy(new_ptr, ptr, old_size);

        free(ptr);

        return new_ptr;
    }
}
