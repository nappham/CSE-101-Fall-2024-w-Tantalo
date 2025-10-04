List.h
- The helper file that allows the List.c files to function properly

List.c
- An ADT, that contains a list of Nodes that contain an int data type as well as the pointers to the file before and after it. This file also contains a series of functions to modify and change the list ADT. My computer has been giving me an error where the index function has already been built in and interfering with the index function in this file. I have ignored it and it has not been an issue but I am still unclear about why this is happening.

Graph.h
- The helper file that allows the the Graph.c, GraphTest.c and FindPath.c files to function properly

GraphTest.c
- A program used to help debug and test new functions added to the Graph.c file. This can also be used as a playground to test for caseedges and unique problems without having to compromise the FindPath.c file.

Graph.c
- A Graph ADT that has the ability to made Nodes and connect them, either directed or undirected. It comes with a BFS function which can allow the program the explain the entire graph.

FindPath.c
- A program that takes in a file, creates a Graph from the pairs then finds the shortest path of a set of pairs then puts that information   into a file

MakeFile
- A script that compiles all the files listed above and turns them into binaries that can be run in the terminal. The MakeFile has not been modified.


