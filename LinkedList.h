#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"

using namespace std;

class LinkedList {
private:
	// private variables
	Node* head;
	int length;
public:
	// public methods
	LinkedList();
	~LinkedList();
	Node* getHead();
	int getLength();
	void add(int vertex, int weight);
	void print();
};
#endif