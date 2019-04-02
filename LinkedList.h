#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"

using namespace std;

class LinkedList {
private:
	Node* head;
	int length;
public:
	LinkedList();
	~LinkedList();
	Node* getHead();
	int getLength();
	void add(int referenceIndex, int vertex, int weight);
	void print();
};
#endif