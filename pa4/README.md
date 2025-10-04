List.h
- The helper file that allows the List.c files to function properly

List.c
- An ADT, that contains a list of Nodes that contain an void data type as well as the pointers to the file before and after it. This file also contains a series of functions to modify and change the list ADT. My computer has been giving me an error where the index function has already been built in and interfering with the index function in this file. I have ignored it and it has not been an issue but I am still unclear about why this is happening.

ListTest.c
- Because we are modifying the List ADT to handle structures as a data rather than an integer, this program is meant to debug and make sure that the new functions are modified to work with holding a datatype.

Matrix.c
- An ADT that allows the creation of an (n * n) matrix that can be filled with double datatypes. It is a list of list where each row contains entry structs that contain a column index and a double value);

Matrix.h
- The header file that allows the Matrix.c file to function properly

MatrixTest.c
- A file that allows for testing of the Matrix.c and Matrix.h file for new functions. 
 
MakeFile
- A script that compiles all the files listed above and turns them into binaries that can be run in the terminal. The MakeFile has not been modified.

Sparse.c
- The main function that takes in an input file that creates two Matrixs and does a series of functions, like scalar muliplication, addition etc, and prints them out.

