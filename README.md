# CSE310-P02

* Patrick Finger
* CSE310 T-TH 4:30-5:45PM
* Project 2
* Professor Xue

This project was written in C++. The targeted functionality was for C++98 for general.asu.edu. The program implements 
dijkstras algoritm along with a graph and heap data structure to support it. Graphs can be manipulated via the command line.

# Commands
* "e" - Stops the program.
* "i" - Attemps to load a graph from "Ginput.txt". (see file syntax below)
* "w" - Writes the current graph information to the console.
* "c int:source int:destination int:flag" - Runs dijkstras algorithm on the loaded graph. When flag == 0 the length
of the path from the source to destination vertex will be printed. When flag == 1 the path from the source to destination
vertex will be printed.

# File Syntax
A text file named "Ginput.txt" should be placed in the same directory as the executable. This file should contain two integers
n and m on the first line seperated by a space. n denotes the number of vertices in the graph while m denotes the number of edges
in the adjacency list. Each line after line 1 will create the adjacency list and should contain three integers u, v, and w seperated
by a space. u denotes the parent of the edge while v denotes the neighbor or child of the edge. w denotes the weight along the u-v edge.