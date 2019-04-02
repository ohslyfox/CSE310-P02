#ifndef Element_H
#define Element_H

class Element {
private:
	int key;
	int vertex;
	int pi;
	int referenceIndex;
public:
	Element();
	~Element();
	int getKey();
	int getVertex();
	int getPi();
	int getReferenceIndex();
	void setKey(int inputKey);
	void setVertex(int vertex);
	void setPi(int pi);
	void setReferenceIndex(int referenceIndex);
};
#endif