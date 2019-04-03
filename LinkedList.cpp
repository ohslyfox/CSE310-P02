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

/**
 * Adds a directed edge to the linked list.
 * @param vertex, the vertex id to store
 * @param weight, the weight along th edge
 */
void LinkedList::add(int vertex, int weight) {
	Node* node = new Node();
	node->setVertex(vertex);
	node->setWeight(weight);
	node->setNext(this->head);
	this->head = node;
	this->length++;
}

/**
 * Returns the head of the list.
 * @return head, the head of the list
 */
Node* LinkedList::getHead() {
	return this->head;
}

/**
 * Returns the length of the list.
 * @return length, the length of the list
 */
int LinkedList::getLength() {
	return this->length;
}

/**
 * Prints the list.
 */
void LinkedList::print() {
	Node* copy = this->head;
	while (copy != NULL) {
		cout << "(" << copy->getVertex() << ", " << copy->getWeight() << ")";
		copy = copy->getNext();
		if (copy != NULL) cout << "; ";
	}
}