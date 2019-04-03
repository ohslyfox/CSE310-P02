#ifndef Element_H
#define Element_H

class Element {
private:
	int distance;
	int vertex;
	int pi;
public:
	Element();
	int getDistance();
	int getVertex();
	int getPi();
	void setDistance(int distance);
	void setVertex(int vertex);
	void setPi(int pi);
};
#endif