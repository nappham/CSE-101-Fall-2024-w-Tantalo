#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include"List.h"

int main(int argc, char * argv[]) {
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
    while (getline(&line, &size, in) >= 0) {
        lines++;
    }
    rewind(in);
    char** line_list = malloc(lines * sizeof(char*));
    ssize_t len = 0;
    size_t indexs = 0;
    while ((len = getline(&line, &size, in)) >= 0) {
        line_list[indexs] = malloc(size * sizeof(char));
        strcpy(line_list[indexs], line);
    indexs++;
    }
    List L = newList(); 
    append(L, 0);
  for (int x = 1; x < lines; x++) { 
	    moveFront(L);
    	while (index(L) >= 0) {
		if (strcmp(line_list[x],line_list[get(L)]) <= 0) {
			insertBefore(L, x);
			break;
		} else {
			moveNext(L);
		}
	}
	if (index(L) == -1) {
		append(L, x);
	}

    }
  moveFront(L);
  for (int z = 0; z < lines; z++) {
  	fprintf(out, "%s", line_list[get(L)]);
	moveNext(L);
  }
  for (int z = 0; z < lines; z++) {
	free(line_list[z]);
  }

  fclose(in);
  fclose(out);
 
free(line);
free(line_list);
freeList(&L);
}
