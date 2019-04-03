#include <stdlib.h>
#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() {
	this->head = NULL;
	this->length = 0;
}

LinkedList::~LinkedList() {
	Node* copy = this->head;
	while (copy != NULL) {
		Node* next = copy->getNext();
		delete copy;
		copy = next;
	}
	this->head = NULL;
}

void LinkedList::add(int vertex, int weight) {
	Node* node = new Node();
	node->setVertex(vertex);
	node->setWeight(weight);
	node->setNext(this->head);
	this->head = node;
	this->length++;
}

Node* LinkedList::getHead() {
	return this->head;
}

int LinkedList::getLength() {
	return this->length;
}

void LinkedList::print() {
	Node* copy = this->head;
	while (copy != NULL) {
		cout << "(" << copy->getVertex() << ", " << copy->getWeight() << ")";
		copy = copy->getNext();
		if (copy != NULL) cout << "; ";
	}
}