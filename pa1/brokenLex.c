#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include"List.h"
#define _GNU_SOURCE

int main(int argc, char * argv[]) {
    printf("sf");
    FILE *in, *out;
    if(argc != 3) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t size = 0;
    int lines = 0;
    size_t len = 0;
    while (getline(&line, &size, in) >= 0) {
        lines++;
    }
    rewind(in);
    char** line_list = malloc(lines * sizeof(char*));
    len = 0;
    size_t index_= 0;
    while ((len = getline(&line, &size, in)) >= 0) {
        line_list[index_] = malloc(size * sizeof(char));
        strcpy(line_list[index_], line);
    index_++;
    }
    List L = newList(); 
    append(L, 0);
  for (int x = 1; x < lines; x++) { 
	    moveFront(L);
	    printf("test1\n");
    	while (indexs(L) >= 0) {
		printf("test2\n");
		if (strcmp(line_list[x],line_list[get(L)]) <= 0) {
			printf("test3\n");
			insertBefore(L, x);
			printf("test4\n");
			break;
		} else {
			printf("test5\n");
			moveNext(L);
		}
	}
	if (indexs(L) == -1) {
		printf("test6\n");
		append(L, x);
	}

    }
  moveFront(L);
  for (int z = 0; z < lines; z++) {
  	fprintf(out, "%s", line_list[get(L)]);
	moveNext(L);
  }
  clear(L);
  freeList(&L);
}
