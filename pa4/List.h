//----------------------------------------------
// List.h
// Nathan Pham
// User ID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------


#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>


typedef struct ListObj* List;

// structs ---------

// private Node type
typedef struct NodeObj* Node;


List newList(void);

void freeList(List* pL);

int length(List L);

int index(List L);

void* front(List L);

void* back(List L);

void* get(List L);

void clear(List L);

void set(List L, void* x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void* x);

void append(List L, void* x);

void insertBefore(List, void* x);

void insertAfter(List L, void* x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

List concatList(List A, List B);
