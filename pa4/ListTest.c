//----------------------------------------------
// ListTest.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------

#include<stdio.h>
#include"List.h";

int main() {
List A = newList();
    append(A, 1);
    append(A, 2);
    append(A, 3);
    moveFront(A);
    delete (A);
    append(A, 3);
    append(A, 5);
    moveFront(A);
    insertAfter(A, 12);
    delete (A);
    if (length(A) != 4) {
      printf("Test One: Error\n");
    } else {
    	printf("Test One: Passed\n");
    }
    clear(A);
    append(A, 1);
    append(A, 1);
    append(A, 1);
    append(A, 1);
    append(A, 1);
    append(A, 1);
    append(A, 1);
    moveFront(A);
    if (index(A) != 0) {
    	printf("Test Two: Error\n");
    } else {
    	printf("Test Two: Passed\n");
    }
    moveNext(A);
    if(index(A) != 1) {
    	printf("Move Next Error\n");
    } else {
    	printf("Move Next Passed\n");
    }
    movePrev(A);
    if(index(A) != 0) {
   	printf("Move Prev Error\n");
    } else {
    	printf("Move Prev Passed\n");
    }
    if (length(A) != 7) {
	    printf("Test Three: Error\n");
    } else {
	    printf("Test Three: Passed\n");
    }
    moveBack(A);
    if (index(A) != 6) {
    	printf("Test Four: Error\n");
    } else {
	    printf("Test Four: Passed\n");
    }
    clear(A);
    if (index(A) != -1) {
    	printf("Test Five: Error\n");
    } else {
    	printf("Test Five: Passed\n");
    }
    if (length(A) != 0) {
    	printf("Test Six: Error\n");
    } else {
	    printf("Test Six: Passed\n");
    }
    insertBefore(L, 1);
    if (length(A) != 1) {
    	printf("Insert Before Failed\n");
    } else {
    	printf("Insert Before Failed\n");
    }
    insertAfter(L, 1);
    if (length(A) != 2) {
    	printf("Insert After Failed\n");
    } else {
    	printf("Insert After Failed\n");
    }
    deleteFront(L);
    if (length(A) != 1) {
    	printf("Delete Front Failed\n");
    } else {
    	printf("Delete Front Passed\n");
    }
    deleteBack(L);
    if (length(A) != 0) {
	    printf("Delete Back Failed\n");
    } else {
	    printf("Delete Back Passed\n");
    }
 
    freeList(&A);
}
