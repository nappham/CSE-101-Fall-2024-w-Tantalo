//----------------------------------------------
// MatrixTest.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main() {
	Matrix A = newMatrix(3);
	Matrix B = newMatrix(3);
	for (int x = 1; x <= 3; x++) {
		for (int y = 1; y <= 3; y++) {
			changeMatrix(A, x, y, 1.0);
			changeMatrix(B, x, y, 1.0);
		}	
	}
	print(A);
	print(B);
	Matrix C = sum(A,B);
	print(C);
	changeMatrix(B, 1, 3, 1.0);
	print(B);
	transpose(B);
	print(B);
	Matrix D = sum(A, B);
	print(D);
	Matrix E = diff(A, B);
	print(E);
	Matrix F = scalarMult(2.0, A);
	print(F);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
}

