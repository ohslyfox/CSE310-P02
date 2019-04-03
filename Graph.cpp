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
	if (this->heapArray != NULL) delete[] this->heapArray;
}

Element** Graph::dijkstra(int source, int destination) {
	if (source > this->size || destination > this->size) {
		throw "Error: one or more nodes are invalid.";
	}

	int sourceIndex = 0;
	for (int i = 0; i < this->size; i++) {
		if (this->heapArray[i]->getVertex() == source) {
			sourceIndex = i;
		}
		this->heapArray[i]->setKey(INT16_MAX);
		this->heapArray[i]->setPi(0);
	}
	this->heapArray[sourceIndex]->setKey(0);

	Heap* queue = Util::initializeHeap(this->size);
	Util::buildHeap(queue, this->heapArray, this->size);
	int count = 0;
	while (queue->getSize() > 0) {
		Element* u = Util::deleteMin(queue, 1);
		LinkedList* uAdj = adjList[u->getVertex()-1];
		Node* head = uAdj->getHead();
		while (head != NULL) {
			this->relax(u, head->getVertex()-1, head->getWeight());
			head = head->getNext();
		}
	}

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
	inFile.open(name.c_str());
	if (!inFile) {
		throw "Error: file \"Ginput.txt\" was not found.";
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

	for (int i = 0; i < n; i++) {
		this->heapArray[i] = new Element();
		this->adjList[i] = new LinkedList();
		this->heapArray[i]->setVertex(i + 1);
	}

	int u, v, w, iterate = 0, mCount = 0;
	while (inFile >> line && mCount < m) {
		if (iterate == 0) {
			u = atoi(line.c_str());
		}
		else if (iterate == 1) {
			v = atoi(line.c_str());
		}
		else if (iterate == 2) {
			w = atoi(line.c_str());
		}
		iterate++;

		if (iterate == 3) {
			this->adjList[u - 1]->add(v, w);
			mCount++;
			iterate = 0;
		}
	}
	if (mCount < m) {
		throw "Error: the number of edges is less than specified at line 0 in \"Ginput.txt\"";
	}

	this->size = n;
}

int Graph::getSize() {
	return this->size;
}

void Graph::print() {
	for (int i = 0; i < this->size; i++) {
		cout << heapArray[i]->getVertex() << " : ";
		adjList[i]->print();
		cout << endl;
	}
}