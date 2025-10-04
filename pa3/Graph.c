#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#define WHITE -1
#define GRAY 0
#define BLACK 1

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = malloc((n+1)*sizeof(List*));
    G->color = malloc((n+1)*sizeof(int));
    G->parent = malloc((n+1)*sizeof(int));
    G->discover = malloc((n+1)*sizeof(int));
    G->finish = malloc((n+1)*sizeof(int));

    for( int i=1; i<=n; i++){
        G->discover[i] = UNDEF;
        G->parent[i] = NIL;
	G->finish[i] = UNDEF;
	G->color[i] = WHITE;
	G->neighbor[i] = newList();
    }

    G->order = n;
    G->size = 0;  
    G->time = 0; 

    return(G);
}

void freeGraph(Graph* pG){
    if(pG!=NULL || *pG!=NULL){

        for (int x=1; x<=(*pG)->order; x++){
            freeList(&((*pG)->neighbor[x]));
        }
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->neighbor);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG=NULL;

    }
}


/*** Access functions ***/
int getOrder(Graph G){
    return(G->order);
}
int getSize(Graph G){
    return(G->size);
}
int getParent(Graph G, int u){
    return(G->parent[u]);   
}

int getDiscover(Graph G, int u){
    return(G->discover[u]);
}

int getFinish(Graph G, int u){
    return(G->finish[u]);
} 

/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v){
    bool inserted = false;
        moveFront(G->neighbor[u]);
        while ( index(G->neighbor[u])>=0 && inserted == false){
                if (get(G->neighbor[u]) > v){
                    insertBefore(G->neighbor[u], v);
                    inserted = true;
                } else {
                    moveNext(G->neighbor[u]);
                }
        }   
        if (inserted == false){
            append(G->neighbor[u], v);
            inserted = true;
        }

	inserted = false;
	moveFront(G->neighbor[v]);
	while(index(G->neighbor[v])>=0 && inserted == false) {
		if(get(G->neighbor[v]) > u) {
			insertBefore(G->neighbor[v], u);
			inserted = true;
		} else {
			moveNext(G->neighbor[v]);
		}
	}
	if (inserted == false) {
		append(G->neighbor[v], u);
		inserted= true;
	}
    G->size += 1;

}
void addArc(Graph G, int u, int v){
    
    
        bool inserted = false;
        moveFront(G->neighbor[u]);

        while ( index(G->neighbor[u])>=0 && inserted == false){

                if (get(G->neighbor[u]) == v) {
                    return;

                } else if ( get(G->neighbor[u]) > v){
                    insertBefore(G->neighbor[u], v);

                    inserted = true;

                } else {
                    moveNext(G->neighbor[u]);
                }
                

        }   
        if (inserted == false){
            append(G->neighbor[u], v);
            inserted = true;
        }
        G->size += 1;

}


void DFS(Graph G, List S){ 
    G->time = 0;

    for (int i = 1; i < getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->finish[i] = UNDEF;
        G->discover[i] = UNDEF;
    }

    List copy = copyList(S);
    clear(S);

    moveFront(copy);
    while (index(copy) != -1){
        if (G->color[get(copy)] == WHITE){
            Visit(G, S, get(copy));
        }
        moveNext(copy);
    }
    freeList(&copy);



} /* Pre: length(S)==getOrder(G) */

void Visit(Graph G, List S, int x){
    
    G->discover[x] = ++G->time;
    G->color[x] = GRAY;

    moveFront(G->neighbor[x]);
    while (index(G->neighbor[x]) != -1) { 
        int y = get(G->neighbor[x]);
        if (G->color[y] == WHITE){
            G->parent[y] = x;
            Visit(G, S, y);
        }
        moveNext(G->neighbor[x]);
    }
    G->color[x] = BLACK;
    G->finish[x] = ++G->time;
    prepend(S, x);
}

/*** Other operations ***/

Graph transpose(Graph G){
    Graph tG = newGraph(getOrder(G));
    for( int i = 1; i<=getOrder(G); i++){
        moveFront(G->neighbor[i]);
        while(index(G->neighbor[i]) >= 0){
            int x = get(G->neighbor[i]);
            addArc(tG, x, i);
            moveNext(G->neighbor[i]);
        }
    }
    return(tG);
}
Graph copyGraph(Graph G){
    Graph cG = newGraph(getOrder(G));
    for( int i = 1; i<=getOrder(G); i++){
        moveFront(G->neighbor[i]);
        while(index(G->neighbor[i]) >= 0){
            int x = get(G->neighbor[i]);
            addArc(cG, i, x);
            moveNext(G->neighbor[i]);
        }
    }
    return(cG);
}

void printGraph(FILE* out, Graph G){
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
        fprintf(out, "\n");
    }
}
