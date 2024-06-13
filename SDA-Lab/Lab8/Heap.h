#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	PriQueue* h = malloc(sizeof(PriQueue));
    h->maxHeapSize = maxHeapSize;
    h->size = 0;
    h->elem = malloc(maxHeapSize * sizeof(ItemType));
    return h;
}

int getLeftChild(int i){
	return 2 * i + 1;
}

int getRightChild(int i) {
	return 2 * i + 2;
}

int getParent(int i) {
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
    while (idx >= 0 && h->elem[(idx - 1) / 2].prior < h->elem[idx].prior) {
        ItemType aux = h->elem[(idx - 1) / 2];
        h->elem[(idx - 1) / 2] = h->elem[idx];
        h->elem[idx] = aux;
        idx = (idx - 1) / 2;
    }
}


void insert(PriQueue *h, ItemType x) {
  if (h->size == h->maxHeapSize) {
    h->maxHeapSize *= 2;
    h->elem = realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
  }
  h->elem[h->size] = x;
  siftUp(h, h->size);
  h->size++;
}

void siftDown(APriQueue h, int idx) {
    int r = getRightChild(idx);
    int l = getLeftChild(idx);
    int maxIndex = idx;
    if (l < h->size && h->elem[l].prior > h->elem[maxIndex].prior) {
        maxIndex = idx * 2 + 1;
    }
    if (r < h->size && h->elem[r].prior > h->elem[maxIndex].prior) {
        maxIndex = r;
    }
    if (idx != maxIndex) {
        ItemType aux = h->elem[idx];
        h->elem[idx] = h->elem[maxIndex];
        h->elem[maxIndex] = aux;
        siftDown(h, maxIndex);
    }
}

void removeMax(APriQueue h) {    
    h->elem[0] = h->elem[h->size-1];
    h->size--;
    siftDown(h, 0);
}

void freeQueue(APriQueue h){
	free(h->elem);
    free(h);
}

#endif

