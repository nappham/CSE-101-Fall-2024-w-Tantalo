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

FindComponent.c
- A program taht reads the inpt file, assemble a graph object G using newGraph() and addArc(), print the adjacency list representation of G to the output file. Run DFS on G and G(Transpose), processing the vertices in the second call by decreasing finish times from the first call. Determine the strong components of G. Print the strong components of G to the output file in topologically sorted order.

MakeFile
- A script that compiles all the files listed above and turns them into binaries that can be run in the terminal. The MakeFile has not been modified.


