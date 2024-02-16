#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

Queue* createQueue(void){
	Queue *q= (Queue *)malloc(sizeof(Queue));
	q -> front = NULL;
	q -> rear = NULL;
	q -> size = 0;
	
	return q;
} 

int isQueueEmpty(Queue *q){
	if (q -> front == NULL || q -> rear == NULL) 
	return 1;
	return 0;
}

void enqueue(Queue *q, Item elem){
	QueueNode* newnode = (QueueNode *)malloc(sizeof(QueueNode));
	newnode -> elem = elem;
	newnode -> next = NULL;
	q -> size++;
	if (isQueueEmpty(q) == 1) {
		q -> front = q -> rear = newnode;
	} else { 
		q -> rear -> next = newnode;
		q -> rear = newnode;
	} 
}

Item front(Queue* q){
	if (!isQueueEmpty(q)) {
		return q -> front -> elem;
	} else {
		exit (1);
	}
}

void dequeue(Queue* q){
	QueueNode *temp;
	if (q -> front == q -> rear) {
		free (q -> front);
		q -> front = NULL;
		q -> rear = NULL;
		q -> size--;
	} else if (!isQueueEmpty (q)) {
		temp = q -> front;
		q -> front = q -> front -> next;
		free(temp);
		q -> size--;
	}
}

void destroyQueue(Queue *q){
	while (!isQueueEmpty(q)) {
		dequeue(q);
	}
	if (q)
	free (q);
}


#endif
