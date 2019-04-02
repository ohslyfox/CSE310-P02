#ifndef Heap_H
#define Heap_H
#include "Element.h"

using namespace std;

class Heap {
private:
	// private variables
	int capacity, size;
	Element** H;
	
	// private methods
	int parent(int index);
	int left(int index);
	int right(int index);
	void expandArray(int targetCapacity);
	void exchange(int firstIndex, int secondIndex);
public:
	// public methods
	Heap(int capacity);
	~Heap();
	Element* extractMin();
	int getMin();
	int getSize();
	void decreaseKey(int index, int newValue);
	void insertKey(int key);
	void minHeapify(int index);
	void buildMinHeap(Element** inputArray, int inputSize);
	void printHeap();
};
#endif