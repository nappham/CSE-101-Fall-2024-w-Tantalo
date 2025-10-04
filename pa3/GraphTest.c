//----------------------------------------------
// GraphTest.c
// Nathan Pham
// User ID: nappham
// Student ID: 2069891
// Assignment: 3
//----------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Graph.h"

int main() {
	Graph G = newGraph(10);
	if (getSize(G) != 10) {
		printf("getSize(G): Failed\n");
	} else {
		printf("getSize(G): Passed\n");
	}
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	addEdge(G, 6, 7);
	addEdge(G, 7, 8);
	addEdge(G, 8, 9);
	addEdge(G, 9, 10);
	if (getOrder(G) != 9) {
		printf("getOrder(G): Failed\n");
	} else {
		printf("getSize(G): Passed\n");
	}
	printGraph(stdout, G);
	freeGraph(&G);
}

