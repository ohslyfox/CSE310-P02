#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <limits.h>
#include "Heap.h"

Heap::Heap(int capacity) {
	if (capacity < 1) {
		throw "Error: capacity must be greater than zero.";
	}

	this->size = 0;
	this->capacity = capacity;
	this->H = new Element*[capacity];
}

Heap::~Heap() {
	delete[] H;
}

/**
 * Extracts the min Element from the heap and
 * returns it.
 * @return Element, the extracted min Element
 */
Element* Heap::extractMin() {
	if (size <= 0) {
		throw "Error: heap is already empty.";
	}

	// get min, set first element to last,
	// decrease size, minHeapify the root to
	// maintain heap property, then return min
	Element* min = this->H[0];
	this->H[0] = this->H[this->size - 1];
	this->size--;
	this->minHeapify(0);
	return min;
}

/**
 * Rearranges the heap starting from index given
 * input index to verify heap propery.
 * @param index, the index to minHeapify
 */
void Heap::minHeapify(int index) {
	int l = left(index);
	int r = right(index);
	int smallest;

	if (l < size && H[l]->getDistance() < H[index]->getDistance()) {
		smallest = l;
	}
	else {
		smallest = index;
	}

	if (r < size && H[r]->getDistance() < H[smallest]->getDistance()) {
		smallest = r;
	}

	if (smallest != index) {
		exchange(index, smallest);
		minHeapify(smallest);
	}
}

/**
 * Rebuilds the heap to match the input given by
 * inputArray of size given by inputSize
 * @param inputArray, the array to build from
 * @param inputSize, the size of the inputArray
 */
void Heap::buildMinHeap(Element** inputArray, int inputSize) {
	if (capacity < inputSize) {
		throw "Error: the heap capacity must be increased to build from array.";
		// could expand array, however a given example test case throws an error
	}

	// load new values from inputArray
	int index = 0;
	while (index < inputSize) {
		this->H[index] = inputArray[index];
		//this->H[index].setKey(inputArray[index].getKey());
		index++;
	}
	this->size = index;
	
	// fix violated heap property
	for (int i = size/2; i >= 0; i--) {
		minHeapify(i);
	}
}

/**
 * Inserts key given by input key to the current heap.
 * If the heap is at capacity, the capacity will be expanded.
 * @param key, the key to insert
 */
void Heap::insertKey(int key) {
	if (size >= capacity) {
		try {
			this->expandArray(size + 1);
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	// increase size, set new key to infinity,
	// then decrease it to value of key arg
	this->size++;
	this->H[size - 1]->setDistance(INT32_MAX);
	this->decreaseKey(size - 1, key);
}

/**
 * Decreases the key at location given by index to value
 * given by newValue.
 * @param index, the index to decrease
 * @param newValue, the value to decrease the index to
 */
void Heap::decreaseKey(int index, int newValue) {
	if (index > capacity - 1) {
		throw "Error: specified index is out of bounds.";
	}
	if (newValue > this->H[index]->getDistance()) {
		throw "Error: the new key is larger than the key located at index.";
	}
	this->H[index]->setDistance(newValue);
	// fix violated heap property
	while (index > 0 && H[parent(index)]->getDistance() > H[index]->getDistance()) {
		exchange(index, parent(index));
		index = parent(index);
	}
}

/**
 * Expands the capacity of the heap to the nearest
 * power of 2 that suffices the target size given by input target.
 * @param target, the target size to expand to
 */
void Heap::expandArray(int target) {
	// find nearest power of 2 that is
	// greater than or equal to target size
	this->capacity = 1;
	while (this->capacity < target) {
		this->capacity = this->capacity * 2;
	}
	// attempt to reallocate array with new capacity
	Element** temp = new Element*[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		if (i < this->size) {
			temp[i] = H[i];
		}
		else {
			temp[i] = new Element();
		}
	}
	delete[] this->H;
	this->H = temp;
}

/**
 * Swaps the element given by input firstIndex with
 * the element given by input secondIndex.
 * @param firstIndex, the first index to swap from
 * @param secondIndexa, the second index to swap from
 */
void Heap::exchange(int firstIndex, int secondIndex) {
	Element* temp = H[firstIndex];
	H[firstIndex] = H[secondIndex];
	H[secondIndex] = temp;
}

/**
 * Returns the index that is the parent of the input index.
 * @param index, the index to find parent from
 * @return int, the index of the parent
 */
int Heap::parent(int index) {
	return ((index - 1) / 2);
}

/**
 * Returns the index that is left child of the input index.
 * @param index, the index to find left child from
 * @return int, the index of the left child
 */
int Heap::left(int index) {
	return ((2 * index) + 1);
}

/**
 * Returns the index that is right child of the input index.
 * @param index, the index to find right child from
 * @return int, the index of the right child
 */
int Heap::right(int index) {
	return ((2 * index) + 2);
}

/**
 * Returns the min key of the heap.
 * @return int, the min key of the heap
 */
int Heap::getMin() {
	return this->H[0]->getDistance();
}

/**
 * Returns the current size of the heap.
 * @return int, the size of the heap
 */
int Heap::getSize() {
	return this->size;
}

/**
 * Prints the size and capacity of the heap along
 * with the elements of the heap.
 */
void Heap::printHeap() {
	// print capacity and size
	cout << "The capacity is " << this->capacity << ".\n";
	cout << "Size is " << this->size << ".\n";
	// fetch key of each element and print it followed by a new line
	for (int i = 0; i < this->size; i++) {
		cout << this->H[i]->getDistance() << endl;
	}
}