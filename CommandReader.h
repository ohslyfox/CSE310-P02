#ifndef CommandReader_H
#define CommandReader_H
#include "Util.h"
#include <string>

using namespace std;

class CommandReader {
public:
	// constructor and destructor
	CommandReader();
	~CommandReader();

	// public methods
	int executeStringCommand(string inputString);
private:
	// private variables
	Graph* currentGraph;

	// private methods
	//Element* loadFile(string fileName, int* n);
	bool checkStringContainsDigits(string inputString);
};
#endif