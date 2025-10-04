//----------------------------------------------
// Graph.h
// Nathan Pham
// User ID: nappham
// Student ID: 2069891
// Assignment: 3
//----------------------------------------------

#include "List.h"

#define INF -1
#define NIL 0
#define UNDEF -1
#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct GraphObj {
    List* neighbor;
    int* color;
    int* parent;
    int* finish;
    int* discover;
    int time;
    int order;
    int size;
} GraphObj;

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph *pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
void Visit(Graph G, List S, int x);


/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
