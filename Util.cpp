#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <limits.h>
#include "Util.h"

/**
 * Returns a pointer to a new heap of size n
 * @param n, the capacity of desired heap
 * @return Heap*, the pointer to the new heap
 */
Heap* Util::initializeHeap(int n) {
	return (new Heap(n));
}

/**
 * Builds element array given by inputArray into the heap
 * given by inputHeap of size n
 * @param inputHeap, the heap to build into
 * @param inputArray, the array of elements to build from
 * @param n, the length of inputArray
 */
void Util::buildHeap(Heap* inputHeap, Element** inputArray, int n) {
	inputHeap->buildMinHeap(inputArray, n);
}

/**
 * Extracts the min element from the heap given by inputHeap
 * The flag input can be 1 or 2, when
 * it is 2 the heap will be printed before and after deletion,
 * when the flag is 1 no additional actions will be perfomed
 * @param inputHeap, the heap to extract from
 * @param flag, the flag argument
 * @return Element, the element  that was removed
 */
Element* Util::deleteMin(Heap* inputHeap, int flag) {
	if (flag != 1) { //leave this here so flag error takes precedence
		throw "Error: invalid flag argument.";
	}
	if (inputHeap->getSize() == 0) {
		throw "Error: heap is already empty.";
	}
	// fix violated heap property
	for (int i = inputHeap->getSize() / 2; i >= 0; i--) {
		inputHeap->minHeapify(i);
	}

	return inputHeap->extractMin();
}

/**
 * Returns a pointer to a new graph
 * @return Graph*, the pointer to the new graph
 */
Graph* Util::initializeGraph() {
	return (new Graph());
}

/**
 * Attempts to load 'Ginput.txt' into the graph
 * @param inputGraph, the graph to load into
 */
void Util::loadGraph(Graph* inputGraph) {
	inputGraph->loadGraph();
}

/**
 * Runs dijkstras shortest path alogorithm on the
 * input graph from source to destination. If the
 * flag == 0 the length of the path will be printed.
 * if flag == 1 the vertices of the path will be printed.
 * @param inputGraph, the graph to run dsp on
 * @param source, the source vertex
 * @param destination, the destination vertex
 * @param flag, the flag value
 */
void Util::dijkstra(Graph* inputGraph, int source, int destination, int flag) {
	if (flag < 0 || flag > 1) {
		throw "Error: invalid flag argument.";
	}

	Element** sp = inputGraph->dijkstra(source, destination); // get shortest path
	int destinationIndex = destination - 1; // index of destination

	// check if path was found
	if (sp[destinationIndex]->getDistance() >= INT32_MAX / 2) {
		throw "Error: no path from source to destination.";
	}
	// print distance or path
	if (flag == 0) {
		cout << "LENGTH: " << sp[destinationIndex]->getDistance() << endl;
	}
	else {
		int n = inputGraph->getVerticies();
		int index = n - 1;
		int* path = new int[n]; // path can be at most n length
		while (sp[destinationIndex]->getPi() != 0) { // while the pi field is a valid vertex
			path[index] = sp[destinationIndex]->getVertex(); // store vertex
			destinationIndex = sp[destinationIndex]->getPi() - 1; // to pi vertex
			index--; // next index for path
		}
		path[index] = sp[destinationIndex]->getVertex(); // store last vertex

		string concat = ""; // string containing final path
		stringstream out; // stringstream for converting int to string
		for (int i = index; i < n; i++) {
			out << path[i]; // store int
			concat += out.str(); // append int to string
			if (i < n-1) concat += ", "; // add a comma if not last vertex
			out.str(""); // clear string stream
		}

		delete[] path;
		cout << "PATH: " << concat << endl;
	}
}

/**
 * Prints the inputGraph.
 * @param inputGraph, the graph to print
 */
void Util::printGraph(Graph* inputGraph) {
	inputGraph->print();
}