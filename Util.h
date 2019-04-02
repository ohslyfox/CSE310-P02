#ifndef Util_H
#define Util_H

#include <string>
#include "Heap.h"
#include "Graph.h"

class Util {
public:
	static Heap* initializeHeap(int n);
	static void buildHeap(Heap* inputHeap, Element** inputArray, int n);
	static void insert(Heap* inputHeap, int flag, int k);
	static Element* deleteMin(Heap* inputHeap, int flag);
	static void decreaseKey(Heap* inputHeap, int flag, int index, int value);
	static void printHeap(Heap* inputHeap);

	static Graph* initializeGraph();
	static void loadGraph(Graph* inputGraph);
	static void dijkstra(Graph* inputGraph, int source, int destination, int flag);
	static void printGraph(Graph* inputGraph);
};
#endif