//----------------------------------------------
// Matrix.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------

#include "List.h"
#include "Matrix.h"

// Additional Functions

Entry newEntry(int col, double value) {
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->value = value;
	return E;
}

void freeEntry(Entry* pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
//		pE = NULL;
	}
}

// Matrix
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->NNZ = 0;
	M->rows = calloc(n + 1, sizeof(List));
	for (int x = 1; x <=n; x++) {
		M->rows[x] = newList();
	}
	return M;
}

void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) {
		makeZero(*pM);
		for (int x = 1; x <= (*pM)->size; x++) {
			freeList(&((*pM)->rows[x]));
		}
		free((*pM)->rows);
		free(*pM);
		*pM = NULL;
	}
}

int size(Matrix M) {
	return M->size;
}

int NNZ(Matrix M) {
	return M->NNZ;
}

int equals(Matrix A, Matrix B) {
	if (A->size != B->size) {
		return 0;
	}

	for (int x = 1; x<= A->size; x++) {
		List Arow = A->rows[x];
		List Brow = B->rows[x];
		
		if(length(Arow) != length(Brow)) {
			return 0;
		}
		moveFront(Arow);
		moveFront(Brow);
		while (index(Arow) != -1 && index(Brow) != -1) {
			Entry aE = get(Arow);
			Entry bE = get(Brow);
			if (aE->column != bE->column) {
				return 0;
			}
			if (aE->value != bE ->value) {
				return 0;
			}
			moveNext(Arow);
			moveNext(Brow);		
		}
	
	}
	return 1;
}

void makeZero(Matrix M) {
	for (int x = 1; x <= M->size; x++) {
		List row = M->rows[x];
		moveFront(row);
		while(index(row) != -1) {
			Entry rowS = (Entry)get(row);
			freeEntry(&rowS);
			moveNext(row);
		}
		clear(row);
	}	
	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
	List row = M->rows[i];
	moveFront(row);
	if (index(row) == -1) {
		if (x != 0) {
			Entry E = newEntry(j, x);
			append(row, E);
			M->NNZ++;
		}
		return;
	}
	while (index(row) != -1) {
		Entry E = get(row);
		if (E->column == j) {
			if (x == 0) {
				delete(row);
				freeEntry(&E);
				M->NNZ--;
				return;
			} else {
				E = get(row);
				E->value = x;
				return;
			}
		}
		if (E->column > j) {
			if (x != 0) {
				E = newEntry(j, x);
				insertBefore(M->rows[i], E);
				M->NNZ++;
			}
			return;
		}
		moveNext(row);
	}
	if (index(row) == -1) {
		if (x != 0) {
			Entry E = newEntry(j, x);
			append(M->rows[i], E);
			M->NNZ++;
		}
		return;
	}
}

Matrix copy(Matrix A) {
	Matrix B = newMatrix(A->size);
	for (int x = 1; x <= A->size; x++) {
		List row = A->rows[x];
		moveFront(row);
		while (index(row) != -1) {
			Entry E = get(row);
			changeEntry(B, x, E->column, E->value);
			moveNext(row);
		}
	}
	return B;
}

Matrix transpose(Matrix A) {
	Matrix T = newMatrix(A->size);
	for (int x = 1; x <= A->size; x++) {
		List row = A->rows[x];
		moveFront(row);
		while (index(row) != -1) {
			Entry E = get(row);
			changeEntry(T, E->column, x, E->value);
			moveNext(row);
		}
	}
	return T;
}

Matrix scalarMult(double x, Matrix A) {
	Matrix B = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		List row = A->rows[i];
		moveFront(row);	
		while (index(row) != -1) {
			Entry E = get(row);
			changeEntry(B, i, E->column, (E->value) * x);
			moveNext(row);
			
		}
	}
	A = copy(B);
	freeMatrix(&B);
	return A;
}

Matrix sum(Matrix A, Matrix B) {
	if (equals(A, B)) {	
		return scalarMult(2.0, A);
	}
	if (A->size != B->size) {
		exit(1);
	}
	Matrix sum = newMatrix(A->size);
	for (int x = 1; x <= A->size; x++) {
		int lever = 0;
		List Arow = A->rows[x];
		List Brow = B->rows[x];
		moveFront(Arow);
		moveFront(Brow);
		while ((index(Arow) != -1) || (index(Brow) != -1)) {
			while (index(Brow) == -1 && index(Arow) != -1) {
				Entry Aentry = get(Arow);
				changeEntry(sum, x, Aentry->column, Aentry->value);
				moveNext(Arow);	
				lever = 1;
			}
			while (index(Arow) == -1 && index(Brow) != -1) {
				Entry Bentry = get(Brow);
				changeEntry(sum, x, Bentry->column, Bentry->value);
				moveNext(Brow);
				lever = 1;
			}
			if (lever == 0) {
				Entry Bentry = get(Brow);
				Entry Aentry = get(Arow);
				while ((Aentry->column) > (Bentry->column)) {
					changeEntry(sum, x, Bentry->column, Bentry->value);
					moveNext(Brow);	
					if (index(Brow) == -1) {
						break;
					}
					Bentry = get(Brow);
				}

				while ((Aentry->column) < (Bentry->column)) {
					changeEntry(sum,x, Aentry->column, Aentry->value);
					moveNext(Arow);
					if (index(Arow) == -1) {
						break;
					}
					Aentry = get(Arow);
				}
	
				if ((Aentry->column) == (Bentry->column)) {
					changeEntry(sum, x, Aentry->column, (Bentry->value) + (Aentry->value));
					moveNext(Arow);
					moveNext(Brow);
				}
			}
		}
	}
	return sum;
}

Matrix diff(Matrix A, Matrix B) {
	Matrix C = scalarMult(-1, B);
	Matrix diff = sum(A, C);
	freeMatrix(&C);
	return diff;
}

double dotProduct(List A, List B) {
	moveFront(A);
	moveFront(B);
	double value = 0.0;
	while (index(A) != -1 && index(B) != -1) {
		Entry aE = get(A);
		Entry bE = get(B);

		while (aE->column > bE->column) {
			moveNext(B);
			if (index(B) == -1) {
				break;
			}
			bE = get(B);
		}

		while (aE->column < bE->column) {
			moveNext(A);
			if (index(A) == -1) {
				break;
			}
			aE = get(A);
		}
		if (aE->column == bE->column) {
			value += aE->value * bE->value;
			moveNext(A);
			moveNext(B);
		}
	}
	return value;
}

Matrix product(Matrix A, Matrix B) {
	Matrix T = transpose(B);
	Matrix P = newMatrix(A->size);
	for (int x = 1; x <= A->size; x++) {
		List Arow = A->rows[x];
		for (int y = 1; y <= A->size; y++) {
			List Brow = T->rows[y];
			double product = dotProduct(Arow, Brow);
			changeEntry(P, x, y, product);
		}
	}
	freeMatrix(&T);
	return P;
}

void printMatrix(FILE* out, Matrix M)  {
	for (int x = 1; x <= M->size; x++) {
		List row = M->rows[x];
		moveFront(row);
		if (length(row) > 0) {
			fprintf(out, "%d: ", x);
			while (index(row) != -1) {
				Entry E = get(row);
				fprintf(out, "(%d, %.1f) ", E->column, E->value);
				moveNext(row);
			}
			fprintf(out, "\n");
		}
	}
	fprintf(out, "\n");
}

void print(Matrix M) {
		for (int x = 1; x <= M->size; x++) {
		List row = M->rows[x];
		moveFront(row);
		if (length(row) > 0) {
			while (index(row) != -1) {
				Entry E = get(row);
				printf("(%d, %.1f) ", E->column, E->value);
				moveNext(row);
			}
			printf("\n");
		}
	}
}
