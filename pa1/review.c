#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include"List.h"

int main() {

}

bool isPalindrome(List L) {
	List A = newList();
	A = copyList(L);
	moveFront(L);
	moveBack(A);
	for (int x = 0; x < length(L); x++) {
		if(!(get(A) == get(L))) {
			freeList(&A);
			return false;
		}
		moveNext(L);
		movePrev(A);
	}
	freeList(&A);
	return true;
}
