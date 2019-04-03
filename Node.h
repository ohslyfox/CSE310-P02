#ifndef Node_H
#define Node_H

class Node {
private:
	Node* next;
	int vertex;
	int weight;
public:
	Node();
	Node* getNext();
	int getVertex();
	int getWeight();
	void setNext(Node* next);
	void setVertex(int data);
	void setWeight(int weight);
};
#endif