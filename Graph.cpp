#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <limits.h>
#include "Heap.h"
#include "Util.h"
#include "Graph.h"

Graph::Graph() {
	this->adjList = NULL;
	this->vertexArray = NULL;
	this->verticies = 0;
	this->edges = 0;
}

Graph::~Graph() {
	for (int i = 0; i < verticies; i++) {
		if (this->adjList[i] != NULL) delete this->adjList[i];
		if (this->vertexArray[i] != NULL) delete this->vertexArray[i];
	}
	if (this->adjList != NULL) delete this->adjList;
	if (this->vertexArray != NULL) delete this->vertexArray;
}

/**
 * Runs dijkstra's shortest path algorithm on the 
 * vertexArray and adjacency list. Initializes the source
 * to the input source vertex.
 * @param source, the source vertex
 * @param destination, the destination vertex
 * @return vertexArray, the array of verticies
 */
Element** Graph::dijkstra(int source, int destination) {
	if (source > this->verticies || destination > this->verticies || source < 1 || destination < 1) {
		throw "Error: one or more nodes are invalid.";
	}

	// Initialize single source
	for (int i = 0; i < this->verticies; i++) {
		this->vertexArray[i]->setDistance(INT32_MAX/2);
		this->vertexArray[i]->setPi(0);
	}
	this->vertexArray[source-1]->setDistance(0);

	// Find Shortest Path
	Heap* queue = Util::initializeHeap(this->verticies);
	Util::buildHeap(queue, this->vertexArray, this->verticies);
	while (queue->getSize() > 0) {
		Element* u = Util::deleteMin(queue, 1); // fixes violated heap property from relax automatically
		LinkedList* uAdj = adjList[u->getVertex()-1]; // adjacency list for vertex u
		
		// relax each vertex in adjacency list
		Node* head = uAdj->getHead();
		while (head != NULL) {
			this->relax(u->getVertex()-1, head->getVertex()-1, head->getWeight()); 
			head = head->getNext();
		}
	}
	delete queue;
	return this->vertexArray;
}

/**
 * Relaxes the node at v from node u with weight w.
 * @param u, vertex u
 * @param v, vertex v
 * @param w, the weight along u-v
 */
void Graph::relax(int u, int v, int w) {
	if (vertexArray[v]->getDistance() > vertexArray[u]->getDistance() + w) {
		vertexArray[v]->setDistance(vertexArray[u]->getDistance() + w);
		vertexArray[v]->setPi(vertexArray[u]->getVertex());
	}
}

/**
 * Attempts to load graph "Ginput.txt".
 */
void Graph::loadGraph() {
	// check if graph has already been loaded
	if (vertexArray != NULL || adjList != NULL) {
		throw "Error: graph must be recreated to load.";
	}

	// attempt to open file
	ifstream inFile;
	inFile.open("Ginput.txt");
	if (!inFile) {
		throw "Error: file \"Ginput.txt\" was not found.";
	}

	string line; // for reading lines

	// get n and m
	inFile >> line;
	int n = atoi(line.c_str());
	inFile >> line;
	int m = atoi(line.c_str());
	this->verticies = n;
	this->edges = m;

	if (n <= 0 || m < 0) {
		throw "Error: the number of vertices must be greater than 0 and the number of edges must be non-negative.";
	}

	// create new vertex array and adjacency list
	this->vertexArray = new Element*[n];
	this->adjList = new LinkedList*[n];

	// create objects
	for (int i = 0; i < n; i++) {
		this->vertexArray[i] = new Element();
		this->adjList[i] = new LinkedList();
		this->vertexArray[i]->setVertex(i + 1);
	}

	// iterate through u v w's
	int u, v, w, iterate = 0, mCount = 0;
	while (inFile >> line && mCount < m) {
		if (iterate == 0) {
			u = atoi(line.c_str());
			if (u > n || u < 1) throw "Error: A node in the adjacency list does not exist.";
		}
		else if (iterate == 1) {
			v = atoi(line.c_str());
			if (v > n || v < 1) throw "Error: A node in the adjacency list does not exist.";
		}
		else if (iterate == 2) {
			w = atoi(line.c_str());
			if (w < 0 || w > INT16_MAX)
				throw "Error: A node in the adjacency list has a negative edge weight or the weight is too large.";
		}
		iterate++;

		if (iterate == 3) {
			// add (v w) to vertex u
			this->adjList[u - 1]->add(v, w);
			mCount++;
			iterate = 0;
		}
	}
	if (mCount < m) {
		throw "Error: the number of edges is less than specified at line 0 in \"Ginput.txt\"";
	}
}

/**
 * Returns the number of verticies in the graph
 * @return verticies, the number of verticies in the graph
 */
int Graph::getVerticies() {
	return this->verticies;
}

/**
 * Prints the vertices and their adjacency lists
 */
void Graph::print() {
	cout << this->verticies << " " << this->edges << endl;
	for (int i = 0; i < this->verticies; i++) {
		cout << vertexArray[i]->getVertex() << " : ";
		adjList[i]->print();
		cout << endl;
	}
}