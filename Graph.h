#ifndef Graph_H
#define Graph_H
#include "Element.h"
#include "LinkedList.h"

class Graph {
private:
	// private variables
	Element** vertexArray;
	LinkedList** adjList;
	int verticies;
	int edges;

	// private methods
	void relax(int u, int v, int w);
public:
	// public methods
	Graph();
	~Graph();
	Element** dijkstra(int source, int destination);
	int getVerticies();
	void loadGraph();
	void print();
};

#endif