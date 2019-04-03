#ifndef Node_H
#define Node_H

class Node {
private:
	// private variables
	Node* next;
	int vertex;
	int weight;
public:
	//public methods
	Node();
	Node* getNext();
	int getVertex();
	int getWeight();
	void setNext(Node* next);
	void setVertex(int data);
	void setWeight(int weight);
};
#endif