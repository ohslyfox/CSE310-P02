#ifndef Util_H
#define Util_H

#include <string>
#include "Heap.h"
#include "Graph.h"

class Util {
public:
	// heap methods
	static Heap* initializeHeap(int n);
	static void buildHeap(Heap* inputHeap, Element** inputArray, int n);
	static Element* deleteMin(Heap* inputHeap, int flag);

	// graph methods
	static Graph* initializeGraph();
	static void loadGraph(Graph* inputGraph);
	static void dijkstra(Graph* inputGraph, int source, int destination, int flag);
	static void printGraph(Graph* inputGraph);
};
#endif