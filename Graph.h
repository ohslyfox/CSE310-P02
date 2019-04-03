#ifndef Graph_H
#define Graph_H
#include "Element.h"
#include "LinkedList.h"

class Graph {
private:
	// private variables
	Element** vertexArray;
	LinkedList** adjList;
	int size;

	// private methods
	void relax(int u, int v, int w);
public:
	// public methods
	Graph();
	~Graph();
	Element** dijkstra(int source, int destination);
	void loadGraph();
	void print();
	int getSize();
};

#endif