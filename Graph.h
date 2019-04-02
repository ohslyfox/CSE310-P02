#ifndef Graph_H
#define Graph_H
#include "Element.h"
#include "LinkedList.h"

class Graph {
private:
	Element** heapArray;
	LinkedList** adjList;
	int size;

	void relax(Element* u, int v, int w);
public:
	Graph();
	~Graph();
	Element** dijkstra(int source, int destination);
	void loadGraph();
	void print();
	int getSize();
};

#endif