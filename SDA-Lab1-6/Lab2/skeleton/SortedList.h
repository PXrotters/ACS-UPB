#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T element) {
    TSortedList head = (TSortedList)malloc(sizeof(struct node));
    head -> value = element;
    head -> next = NULL;
    return head;
}

int isEmpty (TSortedList head) {
    if (head == NULL)
    return 1;
    else
    return 0;
}

int contains (TSortedList head, T element) {
    TSortedList iter;
    iter = head;
    while (iter != NULL) {
        if (iter -> value == element) {
            return 1;
        }
        iter = iter -> next;
    }
    return 0;
}

TSortedList insert (TSortedList head, T element) {
    TSortedList iter, temp, node;
    int i, k = 0;
    node = create (element);
    if (head == NULL) {
    head = node;
    } else if(node -> value < head -> value) {
        node -> next = head;
        head = node;
    } else {
        iter = head;
        while (iter -> next != NULL && iter -> next -> value < node -> value) {
            iter = iter -> next;
        }
    node -> next = iter -> next;
    iter -> next = node;
    }
    return head;
}


TSortedList deleteOnce (TSortedList head, T element) {
    TSortedList prev = NULL, iter = head;
    while (iter != NULL) {
        if (iter -> value == element) {
            if (prev == NULL) {
            head = iter -> next;
        } else {
            prev -> next = iter -> next;
        }
        free (iter);
        return head;
    }
    prev = iter;
    iter = iter -> next;
    }
return head;
}


long length (TSortedList head) {
    if (head == NULL)
    return 0;
    return 1 + length(head -> next);
}

int getNth (TSortedList head, unsigned int N) {
    int count = 1;
    TSortedList iter;
    iter = head;
    while (iter != NULL) {
        if (count == N) {
            return iter -> value;
        }
        count++;
        iter = iter -> next;
    }
    return 0;
}


TSortedList freeTSortedList (TSortedList head) {
    TSortedList iter;
    while (head != NULL) {
        iter = head;
        head = head -> next;
        free (iter);
    }
    return NULL;
}
#endif
