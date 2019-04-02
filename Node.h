#ifndef Node_H
#define Node_H

class Node {
private:
	Node* next;
	int vertex;
	int referenceIndex;
	int weight;
public:
	Node();
	Node* getNext();
	int getVertex();
	int getReferenceIndex();
	int getWeight();
	void setNext(Node* next);
	void setVertex(int data);
	void setReferenceIndex(int referenceIndex);
	void setWeight(int weight);
};
#endif