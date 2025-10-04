//----------------------------------------------
// Sparse.c
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 4
//----------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

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
	int n, a, b;
	fscanf(in, "%d %d %d\n\n", &n, &a, &b);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	for (int x = 0; x < a; x++) {
		double data;
		int row, column;
		fscanf(in, "%d %d %lf\n", &row, &column, &data);
		
		changeEntry(A, row, column, data);
	}
	printf("Matrix A created\n");
	
	for (int x = 0; x < b; x++) {
		double data;
		int row, column;
		fscanf(in,"%d %d %lf\n", &row, &column, &data);
		changeEntry(B, row, column, data);
	}
	printf("Matrix B created\n");

	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);
	printf("\n");
	print(A);
	fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);
	printf("\n");
	print(B);

	fprintf(out,"(1.5)*A =\n");
	//printf("\nTesting Scalar:\n");
	Matrix C = scalarMult(1.5, A);
	printMatrix(out, C);
	//print(C);
	printf("\n");
	
	printf("\nTesting A+B:\n");
	fprintf(out, "A+B =\n");
	Matrix D = sum(A, B);
	printMatrix(out, D);
	print(D);

	fprintf(out, "A+A =\n");	
	Matrix E = sum(A, A);
	printf("\nTesting A+A:\n");
	print(E);
	printMatrix(out, E);

	fprintf(out, "B-A =\n");
	Matrix F = diff(B,A);
	printf("\nTesting B-A:\n");
	print(F);
	printMatrix(out, F);
	fprintf(out, "A-A = \n\n");
	
	Matrix G = transpose(A);
	fprintf(out, "Transpose(A) =\n");
	printf("\nTesting Transpose(A)\n");
	print(G);
	printMatrix(out, G);
	
	fprintf(out,"A*B =\n");
	printf("\nTesting A*B:\n");
	Matrix H = product(A, B);
	print(H);
	printMatrix(out, H);
	
	fprintf(out, "B*B =\n");
	printf("\nTesting B*B:\n");
	Matrix I = product(B, B);
	printMatrix(out, I);
	print(I);

	fclose(in);
	fclose(out);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);

}
