//----------------------------------------------
// List.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------




#include <stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include<string.h>
#include "Matrix.h"

typedef struct NodeObj{
        void* data;
        struct NodeObj* prev;
        struct NodeObj* next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
        Node front;
        Node back;
        Node cursor;
        int length;
        int index;
} ListObj;


Node newNode(void* data) {
	Node N = malloc(sizeof(NodeObj));
	assert( N != NULL );
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}


double getValue(Entry data) {
	return data->value;
}

int getColumn(Entry data) {
	return data->column;
}
void freeNode(Node* pN){
	if (pN!=NULL && *pN!=NULL) {
		free(*pN);
		*pN = NULL;
	}
}

List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	assert( L!=NULL );
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	L->cursor = NULL;
	return (L);
}

void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
		pL = NULL;
	}
}

int length(List L) {
	return L->length;
}

int index(List L) {
	return L->index;
}

void* front(List L) {
	return L->front->data;
}

void* back(List L) {
	return L->back->data;
}

void* get(List L) {
	return L->cursor->data;
}

void clear(List L) {
	if(L->length == 0) {
		return;
	}
	Node temp;	
	Node current = L->front;
	while (current != L->back) {
		temp = current->next;
		freeNode(&current);
		current = temp;
	}
	free(L->back);
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

void set(List L, void* x) {
	if (L->length >= 0) {
		printf("Error");
		exit(-1);
	}
	if (L == NULL) {
		printf("Error");
		exit(-1);
	}
	L->cursor->data = x;
}

void moveFront(List L) {
	if (L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L) {

	if (L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L) {
	if (L->cursor != NULL) {
		if (L->cursor == L->front) {
			L->cursor = NULL;
			L->index = -1;
		} else {
			L->cursor = L->cursor->prev;
			L->index -= 1;
		}
	}
}

void moveNext(List L) {
	if (L->cursor != NULL) {
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		} else {
			L->cursor = L->cursor->next;
			L->index += 1;
		}
	}
}

void prepend(List L, void* x) {
	Node X = newNode(x);
	if (L->length > 0) {
		X->next = L->front;
		L->front->prev = X;
		L->front = X;
		L->index += 1;
		L->length += 1;
	} else {
		L->front = L->back = X;
		L->index = 0;
		L->length = 1;
	}
}

void append(List L, void* x) {
	Node X = newNode(x);
	if (L->length > 0) {
		L->back->next = X;
		X->prev = L->back;
		L->back = X;
		L->length += 1;
	} else {
		L->front = L->back = X;
		L->index = 0;
		L->length = 1;
	}

}

void insertBefore(List L, void* x) {
	if (L->cursor == L->front) {
		prepend(L, x);
		return;
	}

	Node X = newNode(x);
	Node Y = L->cursor->prev;
	X->prev = Y;
	L->cursor->prev = X;
	Y->next = X;
	X->next = L->cursor;
	L->length += 1;
	L->index += 1;
}

void insertAfter(List L, void* x) {
	if (L->length == 0) {
		prepend(L, x);
		return;
	}

	if (L->cursor == L->back) {
		append(L, x);
		return;
	}
	Node X = newNode(x);
	Node Y = L->cursor->next;
	X->next = Y;
	X->prev = L->cursor;
	L->cursor->next = X;
	Y->prev = X;
	L->length += 1;
}

void deleteFront(List L) {
	if (L->length > 0) {
		if (L->cursor == L->front) {
			L->index = -1;
		} else {
			L->index -= 1;
		}
		Node X = L->front;
		L->front = X->next;
		freeNode(&X);
		L->length -= 1;	
	}
}

void deleteBack(List L) {
	if (L->length > 0) {
		if (L->cursor == L->back) {
			L->index = -1;
		}
		Node X = L->back;
		L->back = X->prev;
		freeNode(&X);
		L->length -= 1;	
	}
}

void delete(List L) {
	if (L->length > 0) {
		if (L->cursor == L->front) {
			deleteFront(L);
			return;
		}	
		if (L->cursor == L->back) {
			deleteBack(L);
			return;
		}
		Node current = L->cursor;
		Node beforeCurrent = L->cursor->prev;
		Node afterCurrent = L->cursor->next;
		beforeCurrent->next = afterCurrent;
		afterCurrent->prev = beforeCurrent;
		freeNode(&current);
		L->length -= 1;
		L->cursor = NULL;
	}
}
