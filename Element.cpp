#include <limits>
#include <stdlib.h>
#include <stdint.h>
#include "Element.h"

Element::Element() {
	/*this->key = new int();
	this->pi = new int();
	this->vertex = new int();
	this->referenceIndex = new int();*/
	this->setKey(0);
	this->setVertex(0);
	this->setPi(0);
	this->setReferenceIndex(0);
}

Element::~Element() {
	/*delete this->key;
	delete this->vertex;
	delete this->pi;
	delete this->referenceIndex;*/
}

int Element::getKey() {
	return this->key;
}

int Element::getVertex() {
	return this->vertex;
}

int Element::getPi() {
	return this->pi;
}

int Element::getReferenceIndex() {
	return this->referenceIndex;
}

void Element::setKey(int inputKey) {
	this->key = inputKey;
}

void Element::setVertex(int vertex) {
	this->vertex = vertex;
}

void Element::setPi(int pi) {
	this->pi = pi;
}

void Element::setReferenceIndex(int referenceIndex) {
	this->referenceIndex = referenceIndex;
}


