#include <stdlib.h>
#include "Node.h"

Node::Node() {
	this->vertex = 0;
	this->weight = 0;
	this->next = NULL;
}

Node* Node::getNext() {
	return this->next;
}

int Node::getVertex() {
	return this->vertex;
}

int Node::getWeight() {
	return this->weight;
}

void Node::setNext(Node* next) {
	this->next = next;
}

void Node::setVertex(int vertex) {
	this->vertex = vertex;
}

void Node::setWeight(int weight) {
	this->weight = weight;
}