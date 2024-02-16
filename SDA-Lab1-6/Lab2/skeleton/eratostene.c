#include <stdio.h>

typedef int T;
#include "SortedList.h"

TSortedList getNaturals(int A, int B) {
    TSortedList nats = NULL;
    int i;
    for (i = A; i <= B; i++) {
        nats = insert(nats, i);
    }
    return nats;
}

TSortedList getPrimes(int N) {
    TSortedList nats = getNaturals(2, N);
    TSortedList head = nats;
    TSortedList iter, aux;
    T X;
    while (head -> next != NULL) {
        X = head -> value;
        iter = head -> next;
        while (iter != NULL) {
            if ((iter -> value) % X == 0) {
                aux = iter -> next;
                nats = deleteOnce (nats, iter -> value);
                iter = aux;
            } else {
                aux = iter -> next;
            }
            if (aux != NULL)
            iter = iter -> next;
            else 
            iter = NULL;
        } 
    head = head -> next;
    }
    return nats;
}

void printInts(TSortedList list) {
    while (!isEmpty(list)) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printInts(getPrimes(100));
    return 0;
}
