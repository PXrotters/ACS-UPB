/*
*	Created by Nan Mihai on 16.05.2022
*	Copyright (c) 2022 Nan Mihai. All rights reserved.
*	Laborator - Structuri de date și Algoritmi (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2021-2022, Seria CD
*/
#include "queue.h"

Node *initNode(T data)
{
	Node *node;

	node = malloc(sizeof(struct node));
	node->data = data;
	node->next = NULL;
	return node;
}

Node *freeNode(Node *node)
{
	if (node) {
		free(node);
	}
	return NULL;
}

Queue initQueue(T data)
{
	Queue queue;

	queue = malloc(sizeof(struct queue));
	queue->head = queue->tail = initNode(data);
	queue->size = 1;
	return queue;
}

Queue enqueue(Queue queue, T data)
{
	Node *node;

	if (isEmptyQueue(queue)) {
		if (queue == NULL)
			return initQueue(data);
		free(queue);
		return initQueue(data);
	}
	node = initNode(data);
	queue->tail->next = node;
	queue->tail = node;
	queue->size++;
	return queue;
}

Queue dequeue(Queue queue)
{
	Node *tmp;

	if (!isEmptyQueue(queue)) {
		tmp = queue->head;
		queue->head = queue->head->next;
		tmp = freeNode(tmp);
		queue->size--;
	}
	return queue;
}

T first(Queue queue) {
	if (!isEmptyQueue(queue)) {
		return queue->head->data;
	} else {
		return -1;
	}
}

int isEmptyQueue(Queue queue) {
	if (queue == NULL || queue->head == NULL || queue->size == 0)
		return 1;
	return 0;
}

Queue freeQueue(Queue queue) {
	while (!isEmptyQueue(queue)) {
		queue = dequeue(queue);
	}
	if (queue)
		free(queue);
	return NULL;
}
