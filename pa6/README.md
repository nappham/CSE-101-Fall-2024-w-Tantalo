List.h
- The helper file that allows the List.c files to function properly

List.cpp
- An ADT, that contains a list of Nodes that contain an int data type as well as the pointers to the file before and after it. This file also contains a series of functions to modify and change the list ADT. 

ListTest.cpp
- A testing file to make sure all List.cpp functions work in their intended function as well as a way to debug edge cases. This also helps
detect, debug and fix memory leaks.
 
MakeFile
- A script that compiles all the files listed above and turns them into binaries that can be run in the terminal. The MakeFile has not been modified.

Arithmetic.cpp
- The main file that takes in one textfile which represents two Big Integers. After creating the two Big Integers, it will do a series of 
arithmetic commands, like adding, subtracting and multiplying, and write them to another file.

BigInteger.cpp
- An ADT that uses the List ADT to pretend to be an integer. It uses its ability to have Nodes as a a way to represent numbers at certain 
indexs.

BigInteger.h
- The helper file that allows the BigInteger.cpp file to function properly

BigIntegerTest.cpp
- A testing file to debug nad make sure all BigInterger.cpp files work properly.
