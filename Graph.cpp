#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Heap.h"
#include "Util.h"
#include "Graph.h"

#define fileName "Ginput.txt"

Graph::Graph() {
	this->adjList = NULL;
	this->heapArray = NULL;
}

Graph::~Graph() {
	if (this->adjList != NULL) delete[] this->adjList;
	if (this->heapArray != NULL) delete this->heapArray;
}

Element** Graph::dijkstra(int source, int destination) {
	int sourceIndex = 0;
	for (int i = 0; i < this->size; i++) {
		if (this->heapArray[i]->getVertex() == source) {
			sourceIndex = i;
		}
		this->heapArray[i]->setKey(INT32_MAX);
		this->heapArray[i]->setPi(NULL);
	}
	this->heapArray[sourceIndex]->setKey(0);

	Heap* queue = Util::initializeHeap(this->size);
	Util::buildHeap(queue, this->heapArray, this->size);
	
	int count = 0;
	while (queue->getSize() > 0) {
		Element* u = Util::deleteMin(queue, 1);
		LinkedList* uAdj = adjList[u->getReferenceIndex()];
		Node* head = uAdj->getHead();
		while (head != NULL) {
			this->relax(u, head->getReferenceIndex(), head->getWeight());
			head = head->getNext();
		}
	}
	//print();
	return this->heapArray;
}

void Graph::relax(Element* u, int v, int w) {
	if (heapArray[v]->getKey() > u->getKey() + w) {
		heapArray[v]->setKey(u->getKey() + w);
		heapArray[v]->setPi(u->getVertex());
	}
	//print();
}


void Graph::loadGraph() {
	// attempt to open file
	ifstream inFile;
	string name = fileName;
	try {
		inFile.open(name.c_str());
		if (!inFile) {
			throw "Error: file \"Ginput.txt\" was not found.";
		}
	}
	catch (const char* msg) {
		cout << msg;
	}
	catch (exception e) {
		cout << e.what();
	}

	// read file into array
	string line;

	inFile >> line;
	int n = atoi(line.c_str());
	inFile >> line;
	int m = atoi(line.c_str());

	if (n <= 0 || m <= 0) {
		throw "Error:";
	}

	this->heapArray = new Element*[n];
	this->adjList = new LinkedList*[n];
	int count = 0;
	int* seen = new int[n];
	struct uvw {
		int u;
		int v;
		int w;
	};
	uvw* toAdd = new uvw[m];
	for (int i = 0; i < m; i++) { // iterate over the amount of edges
		//gather data from line (assumed input 'int:u int:v int:w')
		inFile >> line;
		int u = atoi(line.c_str());
		inFile >> line;
		int v = atoi(line.c_str());
		inFile >> line;
		int w = atoi(line.c_str());

		toAdd[i].u = u;
		toAdd[i].v = v;
		toAdd[i].w = w;
		// first build all unique vertex u's
		bool wasFound = false;
		for (int i = 0; i < n; i++) {
			if (u == seen[i]) {
				wasFound = true;
			}
		}
		if (!wasFound) {
			seen[count] = u;
			this->heapArray[count] = new Element();
			this->heapArray[count]->setVertex(u);
			this->heapArray[count]->setReferenceIndex(count);
			this->adjList[count] = new LinkedList();
			count++;
		}
		else {

		}
	}
	inFile.close();

	for (int i = 0; i < m; i++) {
		uvw current = toAdd[i];
		int foundU = -1, foundV = -1;
		for (int j = 0; j < n; j++) {
			if (current.u == heapArray[j]->getVertex()) {
				foundU = j;
			}
			if (current.v == heapArray[j]->getVertex()) {
				foundV = j;
			}
		}
		if (foundU != -1 && foundV != -1) {
			adjList[foundU]->add(foundV, current.v, current.w);
		}
	}

	this->size = n;
}

int Graph::getSize() {
	return this->size;
}

void Graph::print() {
	for (int i = 0; i < this->size; i++) {
		cout << heapArray[i]->getVertex() << ": ";
		adjList[i]->print();
		cout << endl;
	}
}