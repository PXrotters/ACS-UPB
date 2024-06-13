#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	Item elem;
	struct StackNode *next;
} StackNode;

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
} Stack;

Stack* createStack(void){
	Stack *top;
	top = (Stack *)malloc(sizeof(Stack));
	top -> size = 0;
	top -> head = NULL;
	return top;
}

int isStackEmpty(Stack* stack) {
	if (stack -> head == NULL) {
		return 1;
	} else {
		return 0;
	}
}

void push(Stack *stack, Item elem){
	StackNode *newelement = (StackNode *)malloc(sizeof(StackNode));
	if (newelement == NULL) {
		return ;
	}
	newelement -> elem = elem;
	newelement -> next = stack -> head;
	stack -> head = newelement;
	stack -> size++ ;
}

Item top(Stack *stack){	
	if (!isStackEmpty) {
		return stack -> head -> elem;
	} else {
		exit(1);
	}
} 

void pop(Stack *stack){
	StackNode *temp = stack -> head;
	if (stack -> head -> next != NULL) {
		stack -> head = temp -> next;
		free (temp);
	} else {
		stack -> head = NULL;
	}
	stack -> size--;
}

void destroyStack(Stack *stack){
	while (!isStackEmpty(stack)) {
		pop(stack);
	}
}

#endif 
