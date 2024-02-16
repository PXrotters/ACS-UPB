#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet -> size = 0;                        // initially, the set is empty
  newSet -> capacity = initialCapacity;
  newSet -> elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

int BinarySearch (T *vect, int start, int end, int item) {
  if (end >= start) {
    int mid = start + (end - start) / 2;
    if (vect[mid] == item) {
      return 1;
      printf("1 ");
    } else {
      if (vect[mid] > item) {
      return BinarySearch (vect, start, mid - 1, item);
    }
    return BinarySearch (vect, mid + 1, end, item);
  }
  }
  return 0;
  printf("0 ");
}

int contains(OrderedSet* set, const T element) {
  return BinarySearch (set -> elements, 0, set -> size, element);
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void add(OrderedSet* set, const T newElement) {
  T *vect;
  if (contains(set, newElement) == 1)
    return set;
  if (set -> size == set -> capacity) {
    set->capacity *= 2;
    vect = realloc (set -> elements, set -> capacity * sizeof(T));
    if (vect == NULL) {
      return set;
    }
    set -> elements = vect;
  }
  set -> elements[set -> size] = newElement;
  set -> size++;
  for (int i = 0; i < set -> size - 1; i++) {
    for (int j = i + 1; j < set -> size; j++) {
      if (set -> elements[i] > set -> elements[j]) {
        int aux = set->elements[i];
        set -> elements[i] = set -> elements[j];
        set -> elements[j] = aux;
      }
    }
  }
  return set;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet *result = malloc(sizeof(struct OrderedSet));
  result -> size = 0;
  result -> capacity = s1 -> size + s2 -> size;
  result -> elements = malloc(result -> capacity * sizeof(T));
  int i = 0, j = 0, k = 0;
  while (i < s1 -> size && j < s2 -> size) {
    if (s1 -> elements[i] < s2 -> elements[j]) {
      result -> elements[k++] = s1 -> elements[i];
      i++;
    } else if (s1 -> elements[i] > s2 -> elements[j]) {
      result -> elements[k++] = s2 -> elements[j];
      j++;
    } else {
      result -> elements[k++] = s1 -> elements[i];
      i++;
      j++;
    }
  }
  while (i < s1 -> size)
  result -> elements[k++] = s1 -> elements[i++];
  while (j < s2->size)
  result -> elements[k++] = s2 -> elements[j++];
  result -> size = k;
  return result;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet *result = malloc(sizeof(struct OrderedSet));
  result -> size = 0;
  if (s1 -> size > s2 -> size)
  result -> capacity = s1 -> size;
  else
  result -> capacity = s2 -> size;
  result -> elements = malloc(result -> capacity * sizeof(T));
  int i = 0, j = 0, k = 0;
  while (i < s1 -> size && j < s2 -> size) {
    if (s1 -> elements[i] < s2 -> elements[j]) {
      i++;
    } else if (s1 -> elements[i] > s2 -> elements[j]) {
      j++;
    } else {
      result -> elements[k++] = s1 -> elements[i];
      i++;
      j++;
    }
  }
  result -> size = k;
  return result;
}


// -----------------------------------------------------------------------------

#endif
