#include <string>
#include <sstream>
#include <iostream>
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
 * Inserts key given by k into the heap given
 * by inputHeap. The flag input can be 1 or 2, when
 * it is 2 the heap will be printed before and after insertion,
 * when the flag is 1 no additional actions will be perfomed
 * @param inputHeap, the heap to insert to
 * @param flag, the flag argument
 * @param k, the key value to insert
 */
void Util::insert(Heap* inputHeap, int flag, int k) {
	if (flag == 1) {
		inputHeap->insertKey(k);
	}
	else if (flag == 2){
		printHeap(inputHeap);
		inputHeap->insertKey(k);
		printHeap(inputHeap);
	}
	else {
		throw "Error: invalid flag argument.";
	}
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
	if (flag != 1 && flag != 2) { //leave this here so flag error takes precedence
		throw "Error: invalid flag argument.";
	}
	if (inputHeap->getSize() == 0) {
		throw "Error: heap is already empty.";
	}

	Element* min = NULL;
	if (flag == 1) {
		min = inputHeap->extractMin();
	}
	else if (flag == 2) {
		printHeap(inputHeap);
		min = inputHeap->extractMin();
		printHeap(inputHeap);
	}
	return min;
}

/**
 * Decreases the key located at given input index to given
 * input value from the heap given by inputHeap.
 * The flag input can be 1 or 2, when
 * it is 2 the heap will be printed before and after decreasing,
 * when the flag is 1 no additional actions will be perfomed
 * @param inputHeap, the heap to modify
 * @param flag, the flag argument
 * @param index, the index to decrease
 * @param value, the value to decrease the index to
 */
void Util::decreaseKey(Heap* inputHeap, int flag, int index, int value) {
	if (index < 0 || index >= inputHeap->getSize()) {
		throw "Error: specified index is out of bounds.";
	}
	if (flag == 1) {
		inputHeap->decreaseKey(index, value);
	}
	else if (flag == 2) {
		printHeap(inputHeap);
		inputHeap->decreaseKey(index, value);
		printHeap(inputHeap);
	}
	else {
		throw "Error: invalid flag argument.";
	}
}

/**
 * Prints the heap given by inputHeap.
 * @param inputHeap, the heap to print
 */
void Util::printHeap(Heap* inputHeap) {
	inputHeap->printHeap();
}

Graph* Util::initializeGraph() {
	return (new Graph());
}

void Util::loadGraph(Graph* inputGraph) {
	inputGraph->loadGraph();
}

void Util::dijkstra(Graph* inputGraph, int source, int destination, int flag) {
	Element** sp = inputGraph->dijkstra(source, destination);
	int destinationIndex = -1;
	for (int i = 0; i < inputGraph->getSize(); i++) {
		if (sp[i]->getVertex() == destination) {
			destinationIndex = i;
		}
	}
	if (flag == 0) {
		if (sp[destinationIndex]->getKey() >= INT16_MAX) {
			throw "Error: no path from source to destination.";
		}
		cout << "LENGTH: " << sp[destinationIndex]->getKey() << endl;
	}
	else if (flag == 1) {
		string list = "";
		stringstream out;
		int countLength = 0;
		while (sp[destinationIndex]->getPi() != 0) {
			int nextIndex = -1;
			for (int i = 0; i < inputGraph->getSize(); i++) {
				if (sp[i]->getVertex() == sp[destinationIndex]->getPi()) {
					nextIndex = i;
				}
			}
			out << sp[destinationIndex]->getVertex(); // store vertex into string stream
			list += out.str() + " "; // append string version of vertex int to list string
			out.str(""); // clear string stream
			
			destinationIndex = nextIndex; // to next index
			countLength+=2; // increment string length counter
		}
		out.str(""); // clear string stream
		out << sp[destinationIndex]->getVertex(); // add last vertex
		list += out.str() + " ";
		countLength++; // increment string length counter

		if (countLength == 1 && source != destination) {
			throw "Error: no path from source to destination.";
		}

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

void Util::printGraph(Graph* inputGraph) {
	inputGraph->print();
}