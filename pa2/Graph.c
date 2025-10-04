//----------------------------------------------
// Graph.c
// Nathan Pham
// Student ID: 2069891
// Assignment: 2
//----------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

/*** Constructors-Destructors  ***/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->distance = malloc((n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int x = 1; x < n + 1; x++) {
        G->neighbor[x] = newList();
        G->color[x] = INF;
        G->parent[x] = NIL;
        G->distance[x] = INF; 
    }
    return G;
}

void freeGraph(Graph *pG) {
    if (pG != NULL || *pG != NULL) {
        for (int x = 1; x < (*pG)->order + 1; x++) {
            freeList(&((*pG)->neighbor[x]));
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    return G->source;
}

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDist(Graph G, int u) {
    return G->distance[u];
}

void getPath(List L, Graph G, int u) {
	if (L == NULL) {
		return;
	}
	if (G == NULL) {
		return;
	}
	if (u == 0) {
		return;
	}
	if(u == G->source) {
		append(L, u);
		return;
	}
	List temp = newList();
	append(temp, u);
	int p = getParent(G, u);
	append(temp, p);
	while (p != G->source && p != NIL) {
		p = getParent(G, p);
		append(temp, p);
	}
	if(p == NIL) {
		append(L, NIL);
	} else {
		moveBack(temp);
		while (index(temp) != -1) {
			append(L, get(temp));
			movePrev(temp);
		}
	}
	freeList(&temp);	
}

/*** Manipulation produces ***/
void makeNull(Graph G) {
    for (int x = 1; x < G->order; x++) {
        clear(G->neighbor[x]);
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if (u == v) {
        return;
    }
    moveFront(G->neighbor[u]);
    moveFront(G->neighbor[v]);
    if (index(G->neighbor[u]) == -1) {
    	append(G->neighbor[u], v);
    } else {
	    while (index(G->neighbor[u]) != -1) {
		
    		if (get(G->neighbor[u]) > v) {
			insertBefore(G->neighbor[u], v);
			break;
		}
		moveNext(G->neighbor[u]);
		if (index(G->neighbor[u]) == -1) {
			append(G->neighbor[u], v);
			break;
		}
   	 } 
    }
    if (index(G->neighbor[v]) == -1) {
    	append(G->neighbor[v], u);
    } else {
	    while (index(G->neighbor[v]) != -1) {
    		if (get(G->neighbor[v]) > u) {	
			insertBefore(G->neighbor[v], u);
			break;
		}
		moveNext(G->neighbor[v]);
		if (index(G->neighbor[v]) == -1) {
			append(G->neighbor[v], u);
		}
	    }
    }


    G->size += 1;
}

void addArc(Graph G, int u, int v) {
    if (u == v) 
        return;

    append(G->neighbor[u], v);
    G->size += 1;
}



void BFS(Graph G, int s) {
    G->source = s;
    for (int x = 1; x <= G->order; x++) {
        G->color[x] = INF;
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    G->distance[s] = 0;
    List path = newList();
    append(path, s);
    while (length(path) > 0) {
        int x = front(path);
        deleteFront(path);
    moveFront(G->neighbor[x]);
        while (index(G->neighbor[x]) >= 0) {
            int y = get(G->neighbor[x]);
            if (G->color[y] == INF) {
                G->color[y] = 0;	
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(path, y);
            }
            moveNext(G->neighbor[x]);
        }
    G->color[x] = 1;
    }
    freeList(&path);
}

/*** Other operations  ***/
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
	

    }
}
