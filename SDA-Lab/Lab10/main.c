/*
*	Created by Nan Mihai on 16.05.2022
*	Copyright (c) 2022 Nan Mihai. All rights reserved.
*	Laborator - Structuri de date și Algoritmi (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2021-2022, Seria CD
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"
#include "stack.h"

int check(int *v1, int *v2, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (v1[i] != v2[i])
			return 0;
	}
	return 1;
}

/*
* Funcție care determină sortarea topologică pentru un graf orientat aciclic
* Obs: Rezultatul este reținut în vectorul result care a fost deja alocat!
*/
void recursiveDFS(Graph g, int start, Stack *topSort) {
    g->visited[start] = 1;
    // Parcurge toți vecinii nevizitați ai nodului v
    List tmp = g->adjLists[start];
    while (tmp != NULL) {
        if (!g->visited[tmp->data.v]) {
            recursiveDFS(g, tmp->data.v, topSort);
        }
        tmp = tmp->next;
    }
    *topSort = push(*topSort, start);
}


void topologicalSort(Graph graph, int *result) {
	int i, current = 0, k = 0;
    Stack topSort = NULL;
    // Initializam vect cu 0
    for (i = 0; i < graph->V; i++) {
        result[i] = 0;
    }
	//parcurge cu dfs adauga varf in stiva
    for (i = 0; i < graph->V; i++) {
        if (graph->visited[i] == 0) {
            recursiveDFS(graph, i, &topSort);
        }
    }
    // adaugare vf in vect
    while (!isEmptyStack(topSort)) {
        current = top(topSort);
        topSort = pop(topSort);
        // Adaugă vf in rez
        result[k] = current;
		k++;
    }
}

/*
* Funcție care determină costurile drumurilor minime care pornesc din start
* Obs: Rezultatul este reținut în vectorul distances care a fost deja alocată!
*/
void BellmanFord(Graph graph, int start, int *distances) {
for (int i = 0; i < graph->V; i++) {
	distances[i] = INFINITY;
}
distances[start] = 0;
for (int i = 0; i < graph->V - 1; i++) {
    for (int j = 0; j < graph->V; j++) {
        List tmp = graph->adjLists[j];
        while (tmp != NULL) {
            int u = j;
            int v = tmp->data.v;
            int cost = tmp->data.cost;

            if (distances[u] != INFINITY && distances[u] + cost < distances[v]) {
                distances[v] = distances[u] + cost;
            }
            tmp = tmp->next;
        }
    }
}
}

/*
* Funcție care determină costurile drumurilor minime de la orice nod la orice nod
* Obs: Rezultatul este reținut în matricea distances care a fost deja alocată!
*/
void FloydWarshall(Graph graph, int **distances) {
    int n = graph->V;
	for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        distances[i][j] = INFINITY;
    }
}
for (int i = 0; i < n; i++) {
    List tmp = graph->adjLists[i];
    while (tmp != NULL) {
        distances[i][tmp->data.v] = tmp->data.cost;
        tmp = tmp->next;
    }
}
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j] && distances[k][j] != INFINITY && distances[i][k] != INFINITY) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
}

int main() {
	freopen("test0.in", "r", stdin);
	int V, type, i, x, y, M, cost, j, ok;
	double punctaj = 0;
	int res1[] = {0, 1, 3, 5, 0, 3};
	int top1[] = {0, 3, 2, 1, 4, 5};
	scanf("%d %d", &V, &type);
	Graph graph = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &cost);
		graph = insertEdge(graph, x, y, cost);
	}
	printGraph(graph);
	drawGraph(graph, "graph0.dot");
	int *result;
	result = calloc(graph->V, sizeof(int));
	topologicalSort(graph, result);
	printf("\nRezultat sortarea topologica: ");
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, top1, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	printf("\nRezultat Bellman Ford: ");
	BellmanFord(graph, 0, result);
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, res1, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	
	printf("\nRezultat Floyd Warshall\n");
	int **distances;
	distances = malloc(graph->V * sizeof(int*));
	for (i = 0; i < graph->V; i++) {
		distances[i] = calloc(graph->V, sizeof(int));
	}
	FloydWarshall(graph, distances);
	FILE *fin = fopen("test0.ref", "r");
	ok = 1;
	for (i = 0; i < graph->V; i++) {
		for (j = 0; j < graph->V; j++) {
			printf("%6d ", distances[i][j]);
			fscanf(fin, "%d", &cost);
			if (cost != distances[i][j]) {
				ok = 0;
			}
		}
		free(distances[i]);
		printf("\n");
	}
	if (!ok) {
		printf("Incorect\n");
	} else {
		printf("Corect\n");
		punctaj += 1.5;
	}
	graph = freeGraph(graph);
	free(distances);
	free(result);
	fclose(fin);
	printf("=============================================\n");

	freopen("test1.in", "r", stdin);
	int top2[][7] = {{0, 3, 5, 2, 1, 4, 6}, {0, 3, 2, 1, 4, 5, 6},
					{0, 3, 2, 1, 5, 4, 6}, {0, 3, 2, 5, 1, 4, 6}};
	int res2[] = {0, 1, 3, 5, 0, 4, 3};
	scanf("%d %d", &V, &type);
	graph = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &cost);
		graph = insertEdge(graph, x, y, cost);
	}
	printGraph(graph);
	drawGraph(graph, "graph1.dot");
	result = calloc(graph->V, sizeof(int));
	topologicalSort(graph, result);
	printf("\nRezultat sortarea topologica: ");
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, top2[0], graph->V) || check(result, top2[1], graph->V) ||
		check(result, top2[2], graph->V) || check(result, top2[3], graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	printf("\nRezultat Bellman Ford: ");
	BellmanFord(graph, 0, result);
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, res2, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	
	printf("\nRezultat Floyd Warshall\n");
	distances = malloc(graph->V * sizeof(int*));
	for (i = 0; i < graph->V; i++) {
		distances[i] = calloc(graph->V, sizeof(int));
	}
	FloydWarshall(graph, distances);
	fin = fopen("test1.ref", "r");
	ok = 1;
	for (i = 0; i < graph->V; i++) {
		for (j = 0; j < graph->V; j++) {
			printf("%6d ", distances[i][j]);
			fscanf(fin, "%d", &cost);
			if (cost != distances[i][j]) {
				ok = 0;
			}
		}
		free(distances[i]);
		printf("\n");
	}
	if (!ok) {
		printf("Incorect\n");
	} else {
		printf("Corect\n");
		punctaj += 1.5;
	}
	graph = freeGraph(graph);
	free(distances);
	free(result);
	fclose(fin);


	printf("=============================================\n");
	printf("Punctaj total: %.2lf\n", punctaj);
	printf("Observație: Se acordă 1p de către asistent dacă nu există erori / pierderi de memorie\n");
	return 0;
}
