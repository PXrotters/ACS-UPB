#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


MinHeapNode* newNode(int v, int d)
{
 MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->v = v;
    node->d = d;
    return node;
}

MinHeap* newQueue(int capacity)
{
   MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->elem = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    heap->size = 0; 
    heap->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        heap->elem[i] = NULL;
    }
    return heap;
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
   MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void SiftDown(MinHeap* h, int idx)
{
    int smallest = idx; // seteaza nodul de la indexul dat ca fiind cel mai mic
    int left = 2 * idx + 1; // calculeaza indexul nodului din stanga
    if (left < h->size && h->elem[left]->d < h->elem[smallest]->d) {
        smallest = left; // daca nodul din stanga are o prioritate mai mica, il setam ca fiind cel mai mic
    }
    int right = 2 * idx + 2; // calculeaza indexul nodului din dreapta
    if (right < h->size && h->elem[right]->d < h->elem[smallest]->d) {
        smallest = right; // daca nodul din dreapta are o prioritate mai mica,il setam ca fiind cel mai mic
    }
    if (smallest != idx) {
        // daca nodul de la indexul dat nu este cel mai mic, il interschimbam cu nodul cel mai mic
        MinHeapNode* smallest_node = h->elem[smallest];
        MinHeapNode* idx_node = h->elem[idx];
        h->pos[smallest_node->v] = idx;
        h->pos[idx_node->v] = smallest;
        swap(&h->elem[smallest], &h->elem[idx]);
        SiftDown(h, smallest); // sift-down catre noduri copii pana MinHeap este actualizat
    }
}

int isEmpty(MinHeap* h)
{
    if (h->size == 0) {
        return 1; // 1 daca heapul este vid
    } else {
        return 0; // 0 altfel
    }
}

MinHeapNode* removeMin(MinHeap* h)
{
    if (isEmpty(h)) {
        return NULL;
    }
    MinHeapNode* min_node = h->elem[0]; // nodul minim

    // muta ultimul nod in locul primului nod
    MinHeapNode* last_node = h->elem[h->size - 1];
    h->elem[0] = last_node;

    // actualizeaza pozitia ultimului nod
    h->pos[min_node->v] = h->size - 1;
    h->pos[last_node->v] = 0;

    // scade dimensiunea Min Heapului
    h->size--;
    return min_node;

}

int parent(int i) {
    return (i - 1) / 2;
}

void SiftUp(MinHeap* h, int v, int d)
{
    int i = h->size; // i este pozitia noului nod în Min Heap
    MinHeapNode* new_node = newNode(v, d);

    // adaugam noul nod la sfarsitul Min Heap-ului
    h->elem[i] = new_node;
    h->pos[v] = i;
    h->size++;
    while (i != 0 && h->elem[i]->d < h->elem[parent(i)]->d) {
        swap(&h->elem[i], &h->elem[parent(i)]);
        i = parent(i);
    }
}

int isInMinHeap(MinHeap *h, int v)
{
  if (h->pos[v] < h->size) {
        return 1;
    } else {
        return 0;
    }
}

#endif

