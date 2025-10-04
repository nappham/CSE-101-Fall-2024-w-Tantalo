#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Graph.h"

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
	int total;
	fscanf(in, "%d", &total);
	Graph G = newGraph(total);

	int x, y;
	fscanf(in, "%d %d\n", &x, &y);
	while(x != 0 || y != 0) {
		addEdge(G, x, y);
		fscanf(in,"%d %d\n", &x, &y);
	}
	printGraph(out, G);
	fprintf(out, "\n");
	List L = newList();	
	
	while (fscanf(in, "%d %d", &x, &y) && (x != 0 && y != 0)) {
		BFS(G, x);
		if (getDist(G, y) != INF) {	
			fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			getPath(L, G, y);
			printList(out, L);
			fprintf(out, "\n");
		} else {
			fprintf(out, "The distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists\n", x, y);
		}
		clear(L);
	}
	freeList(&L);
	freeGraph(&G);
	fclose(in);
	fclose(out);

}
