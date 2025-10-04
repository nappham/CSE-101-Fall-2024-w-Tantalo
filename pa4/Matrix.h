//----------------------------------------------
// Matrix.h
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------
#include "List.h"

typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

typedef struct MatrixObj {
	int size;
	int NNZ;
	List* rows;
} MatrixObj;

typedef struct EntryObj* Entry;

typedef struct MatrixObj* Matrix;

Entry newEntry(int col, double value);

void freeEntry(Entry* pE);

Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix X);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE* out, Matrix M);

void print(Matrix M);
