#include "Element.h"

Element::Element() {
	this->setDistance(0);
	this->setVertex(0);
	this->setPi(0);
}

int Element::getDistance() {
	return this->distance;
}

int Element::getVertex() {
	return this->vertex;
}

int Element::getPi() {
	return this->pi;
}

void Element::setDistance(int distance) {
	this->distance = distance;
}

void Element::setVertex(int vertex) {
	this->vertex = vertex;
}

void Element::setPi(int pi) {
	this->pi = pi;
}