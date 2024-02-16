#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

void dijkstra(TGraphL G, int s) {
    int* dist = (int*)malloc(G.nn * sizeof(int)); // distanțele minime de la sursă la fiecare nod
    int* prev = (int*)malloc(G.nn * sizeof(int)); // predecesorii nodurilor pe calea cea mai scurtă
	
    MinHeap* heap = newQueue(G.nn);  //cream un minheap care va fi utilizat pentru selectarea nodurilor cu distante minime

    // inițializare
    for (int i = 1; i < G.nn; i++) {
        dist[i] = INT_MAX;  //toate nodurile se initializeaza cu INF
        prev[i] = -1;  //toti predecesorii se initializeaza cu -1
    }
    dist[s] = 0;  //nodul de start se initializeaza cu 0
    SiftUp(heap, s, 0);  //inseram nodul de start in minheap cu distanta 0

    while (!isEmpty(heap)) {
        MinHeapNode* min_node = removeMin(heap);  //extragem nodul cu distanta minima din MinHeap
        int u = min_node->v;  //retinem indicele acestui nod
        free(min_node);
        for (ATNode neightbours = G.adl[u]; neightbours != NULL; neightbours = neightbours->next) {  //parcurgem toti vecinii nodului u din graf
            int v = neightbours->v;  //retinem vecinul
            int cost = neightbours->c;  //retinem costul vecinului
            int new_dist = dist[u] + cost;  //calculam noua distanta
            if (new_dist < dist[v]) {  //daca noua distanta este mai mica decat distanta curenta stocata in dist[v]
                dist[v] = new_dist;  //actualizam distanta vecinului
                prev[v] = u;  //predecesorul vecinului este setat ca fiind u
                SiftUp(heap, v, new_dist);  //inseram nodul v in minHeap cu distanta new_dist
				//Se continua extragerea si procesarea nodurilor pana cand MinHeap-ul devine gol, adica nu mai exista noduri cu distante minime.
            }
        }
    }
	//Afisam distantele minime calculate pentru fiecare nod
    printf("Dijkstra:\n");
    for (int i = 0; i < G.nn; i++) {
        if (dist[i] != INT_MAX) {
            printf("%d: %d\n", i, dist[i]);
        }
    }

    free(dist);
    free(prev);
    free(heap->elem);
    free(heap->pos);
    free(heap);
}

void Prim(TGraphL graph) {
    int* dist = (int*)malloc(graph.nn * sizeof(int)); // distanțele minime de la sursă la fiecare nod
    int* prev = (int*)malloc(graph.nn * sizeof(int)); // predecesorii nodurilor pe calea cea mai scurtă
    int* added = (int*)calloc(graph.nn, sizeof(int)); // nodurile deja adăugate în arbore

	MinHeap* heap = newQueue(graph.nn);  //cream un minheap care va fi utilizat pentru selectarea nodurilor cu distante minime

	// inițializare
	for (int i = 0; i < graph.nn; i++) {
        dist[i] = INT_MAX;  //toate nodurile se initializeaza cu INF
        prev[i] = -1;  //toti predecesorii se initializeaza cu -1
    }
    dist[0] = 0;  //nodul de start se initializeaza cu 0
    SiftUp(heap, 0, 0);  //inseram nodul de start in minheap cu distanta 0

    while (!isEmpty(heap)) {
        MinHeapNode* min_node = removeMin(heap);  //extragem nodul cu distanta minima din MinHeap
        int u = min_node->v;  //retinem indicele acestui nod
        added[u] = 1;  //marcam nodul u ca fiind adaugat in MinHeap
        free(min_node);
        for (ATNode neightbours = graph.adl[u]; neightbours != NULL; neightbours = neightbours->next) {  //parcurgem toti vecinii nodului u din graf
            int v = neightbours->v;  //retinem vecinul
			int cost = neightbours->c;  //retinem costul vecinului
            if (added[v] == 0 && cost < dist[v]) {  //verificam daca vecinul v nu a fost adaugat in arbore si daca ponderea muchiei este mai mica decat distanta curenta
                dist[v] = cost;  //actualizam distanta vecinului
                prev[v] = u;  //predecesorul vecinului este setat ca fiind u
                SiftUp(heap, v, dist[v]);  //inseram nodul v in minHeap cu distanta new_dist
				//Se continua extragerea si procesarea nodurilor pana cand MinHeap-ul devine gol, adica nu mai exista noduri cu distante minime.
            }
        }
    }

	//Afisam muchiile arborelui minim
    printf("PRIM:\n");
    for (int i = 1; i < graph.nn; i++) {
        if (prev[i] != -1) {
            printf("%d - %d\n", prev[i], i);
        }
    }

    free(dist);
    free(prev);
    free(added);
    free(heap->elem);
    free(heap->pos);
    free(heap);
}



int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}
