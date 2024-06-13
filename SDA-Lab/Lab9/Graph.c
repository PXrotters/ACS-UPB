#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"


TGraphL* createGraphAdjList(int numberOfNodes) {
	TGraphL* graph = (TGraphL*) malloc(sizeof(TGraphL));
    graph->nn = numberOfNodes;
    graph->adl = (ATNode*) malloc(numberOfNodes * sizeof(ATNode));
    for (int i = 0; i < numberOfNodes; i++) {
        graph->adl[i] = NULL;
    }
    return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	TNode* node1 = (TNode*) malloc(sizeof(TNode));
    node1->v = v1;
    node1->next = graph->adl[v2];  //nodul 1 este adaugat la inceputul list de ad a lui v2
    graph->adl[v2] = node1;
    TNode* node2 = (TNode*) malloc(sizeof(TNode));
    node2->v = v2;
    node2->next = graph->adl[v1];  //nodul 2 este adaugat la inceputul list de ad a lui v1
    graph->adl[v1] = node2;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	visited[s] = 1;
    TNode* node = graph->adl[s];
    while (node != NULL) {
        int v = node->v;
        if (visited[v] == 0) {
            enqueue(path, v);
            dfsRecHelper(graph, visited, path, v);
        }
        node = node->next;
    }
}

List* dfsRecursive(TGraphL* graph, int s) {
	List* path = createList();
    int* visited = (int*) calloc(graph->nn, sizeof(int));
    enqueue(path, s);
    dfsRecHelper(graph, visited, path, s);
    free(visited);
    return path;
}

List* bfs(TGraphL* graph, int s){
	List* path = createList();
    int* visited = (int*) calloc(graph->nn, sizeof(int));
    Queue* q = createQueue();
    enqueue(q, s);
    visited[s] = 1;
    while (!isQueueEmpty(q)) {
        int v = front(q);
        dequeue(q);
        enqueue(path, v);
        TNode* node = graph->adl[v];
        while (node != NULL) {
            int w = node->v;
            if (visited[w] == 0) {
                visited[w] = 1;
                enqueue(q, w);
            }
            node = node->next;
        }
    }
    destroyQueue(q);
    free(visited);
    return path;
}

void destroyGraphAdjList(TGraphL* graph) {
    for (int i = 0; i < graph->nn; i++) {
        TNode* temp= graph->adl[i];
        while (temp!= NULL) {
            TNode* next = temp->next;
            free(temp);
            temp= next;
        }
    }
    free(graph->adl);
    free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
