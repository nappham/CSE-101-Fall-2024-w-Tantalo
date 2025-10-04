//----------------------------------------------
// FindComponenets.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 3
//----------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
        FILE *in, *out;
        if (argc != 3) {
                printf("Error");
                exit(1);
        }
        in = fopen(argv[1], "r");
        if (in == NULL) {
                printf("Error");
                exit(1);
        }

        out = fopen(argv[2], "w");
        if (out == NULL) {
                printf("Error");
                exit(1);
        }
	int total = 0;
	fscanf(in,"%d",&total);
	Graph G = newGraph(total);

	int x, y;
	fscanf(in,"%d %d\n", &x, &y);
	while (x != 0 || y != 0) {
		addArc(G, x, y);
		fscanf(in,"%d %d\n", &x, &y);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	
	Graph T = transpose(G);
	List L = newList();
	for (int x = 1; x <= total; x++) {
		append(L, x);
	}
	DFS(G, L);	
	DFS(T, L);	
	List parent = newList();
	int counter = 0;
	moveFront(L);
	while (index(L) != -1) {
		if(getParent(T, get(L)) == NIL) {
			counter++;
			prepend(parent, get(L));
		}
		moveNext(L);
	}
	
	fprintf(out, "\nG contains %d strongly connected components:\n", counter);
	moveFront(parent);
	moveBack(L);
	while (index(parent) != -1) {
		fprintf(out, "Component %d: ", (index(parent)+1));
		List components = newList();
		while(index(L) >= 0) {
			if(getParent(T, get(L)) == NIL) {
				prepend(components, get(L));
				movePrev(L);
				break;
			}
			prepend(components, get(L));
			movePrev(L);
		}
		printList(out, components);	
		freeList(&components);
		moveNext(parent);
	}
	freeList(&L);
	freeList(&parent);
	freeGraph(&G);
	freeGraph(&T);
	fclose(in);
	fclose(out);
}

