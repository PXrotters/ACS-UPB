#include <stdio.h>
#include <stdlib.h>


typedef long T;
typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;



OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet -> size = 0;                        // initially, the set is empty
  newSet -> capacity = initialCapacity;
  newSet -> elements = (long*) malloc(initialCapacity * sizeof(T));

  return newSet;
}



OrderedSet* constr(long x, long a, long b) {
  long idx, len = 0, k = 0;
  len = b - a + 1;
  OrderedSet* set = createOrderedSet(len);

  for (idx = a; idx < b; idx++)
    if(idx % x == 0) {
        set->elements[k] = idx;
        k++;
    }
    set -> size = k;
  return set;
}


void printOrderedlongSet(OrderedSet* set) {
  long idx;
  printf("There are %ld elements:", set->size);                 // print the size
  for(idx = 0; idx < set->size; idx++)
    printf(" %ld", set->elements[idx]);                     // print each element
  printf("\n");
}



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



int main(int argc, char* argv[]) {
  OrderedSet *s1, *s2, *sU, *sI;
//long a, b, x, c, d, y;
//scanf("%ld%ld%ld", &x, &a, &b);
//scanf("%ld%ld%ld", &y, &c, &d);
  s1 = constr(3, 4, 25);           
  printOrderedlongSet(s1);

  s2 = constr(4, 5, 30);
  printOrderedlongSet(s2);

  sU = unionOrderedSets(s1, s2);
  printf("reunion: ");
  printOrderedlongSet(sU);

  sI = intersectOrderedSets(s1, s2);
  printf("intersection: ");
  printOrderedlongSet(sI);


  return 0;
}