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
	else if (flag == 1) {
		string list = ""; // list for path
		stringstream out; // stringstream for converting int to string
		int countLength = 0; // count length of string

		while (sp[destinationIndex]->getPi() != 0) { // while the pi field is a valid vertex
			out << sp[destinationIndex]->getVertex(); // store vertex into string stream
			list += out.str() + " "; // append string version of vertex int to list string
			out.str(""); // clear string stream
			
			destinationIndex = sp[destinationIndex]->getPi()-1; // to next index
			countLength+=2; // increment string length counter
		}

		out << sp[destinationIndex]->getVertex(); // add last vertex
		list += out.str() + " ";
		countLength++; // increment string length counter

		// reverse the list string
		string reverseList = "";
		for (int i = countLength-1; i >= 0; i--) {
			reverseList += list.at(i);
		}
		cout << "PATH: " << reverseList << endl;
	}
	else {
		throw "Error: invalid flag argument.";
	}
}

/**
 * Prints the inputGraph.
 * @param inputGraph, the graph to print
 */
void Util::printGraph(Graph* inputGraph) {
	inputGraph->print();
}