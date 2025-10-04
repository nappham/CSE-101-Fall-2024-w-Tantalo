List.h
- The helper file that allows the List.c files to function properly

List.cpp
- An ADT, that contains a list of Nodes that contain an int data type as well as the pointers to the file before and after it. This file also contains a series of functions to modify and change the list ADT. 

ListTest.cpp
- A testing file to make sure all List.cpp functions work in their intended function as well as a way to debug edge cases. This also helps
detect, debug and fix memory leaks.
 
MakeFile
- A script that compiles all the files listed above and turns them into binaries that can be run in the terminal. The MakeFile has not been modified.

Shuffle.cpp
- The main file that takes in one textfile that contains one integer, the deck size. The file will take the deck size and, starting from 1 
to the deck size, shuffle the amount of cards again and again until it reaches the original. It would then print out the size of the deck as well as how many shuffles it took to loop back to the original deck order.
