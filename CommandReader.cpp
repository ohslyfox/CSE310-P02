#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "CommandReader.h"

CommandReader::CommandReader() {
	this->currentGraph = NULL;
}

CommandReader::~CommandReader() {
	if (this->currentGraph != NULL) {
		delete this->currentGraph;
	}
}
/** 
 * breaks inputString into tokens and executes
 * valid commands (documented below), using the util
 * module, on the currentHeap stored in the CommandReader.
 * @param inputString, the string to read
 * @return int, 0 or 1 where 0 is accepted input
 * and 1 is stop code
 */
int CommandReader::executeStringCommand(string inputString) {
	string tokens[4] = { "", "", "", "" };
	// fetch tokens from input
	// -----------------------
	for (int i = 0; i < 4; i++) {
		tokens[i] = inputString.substr(0, inputString.find(' '));
		// if token is not first token
		if (i > 0) {
			// check if it is a valid integer
			bool valid = checkStringContainsDigits(tokens[i]);

			// if invalid entry or empty entry set token to '~' to represent invalid token
			if (!valid || tokens[i] == "") {
				tokens[i] = "~";
			}
		}
		// if token is first token
		else {
			// if first token is larger than one character or is not alphabetic
			if (tokens[i].length() != 1 || !isalpha(tolower(tokens[i].at(0)))) {
				// set token to '~' to represent invalid token
				tokens[i] = "~";
			}
		}

		// check if last node has been found
		if (inputString.find(' ') == -1) {
			inputString = "";
		}
		// update input string
		inputString.erase(0, inputString.find(' ') + 1);
	}

	
	// translate tokens into commands
	// ------------------------------

	// first token represents command to be executed
	const char cmd = tokens[0].at(0); 

	/* s command stops the program
	 * expected input for token[0] .. token[3]:
	 * s ~ ~ ~
	 */
	if (cmd == 'e' || cmd == 'E') {
		return 1; // stop code
	}
	/* c command initializes a new heap to replace 
	 * the current heap. 
	 * expected input for token[0] .. token[3]:
	 * c int:capacity ~ ~
	 */
	if (cmd == 'i' || cmd == 'I') {
		try {
			Graph* temp = Util::initializeGraph();
			if (currentGraph != NULL) {
				delete this->currentGraph;
			}
			this->currentGraph = temp;
			
			Util::loadGraph(this->currentGraph);
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
		catch (exception e) {
			cout << "Error: " << e.what() << endl;
		}
	}
	// if the command is not 'c' or 's' check if heap has been initalized before 
	// allowing other commands... if it is not initialized print an initilization error
	else if (this->currentGraph != NULL) {
		/* w command prints the current heap to the console
		 * expected input for token[0] .. token[3]:
		 * w ~ ~ ~
		 */
		if (cmd == 'w' || cmd == 'W') {
			Util::printGraph(this->currentGraph);
		}
		/* r command attempts to read the file 'HEAPinput.txt'
		 * and build the corresponding min heap.
		 * expected input for token[0] .. token[3]:
		 * r ~ ~ ~
		 */
		else if (cmd == 'c' || cmd == 'C') {
			try {
				Util::dijkstra(this->currentGraph, atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));
			}
			catch (const char* msg) {
				cout << msg << endl;
			}
			catch (exception e) {
				cout << "Error: " << e.what() << endl;
			}
		}
		
		// command is unrecognized
		else {
			cout << "Error: invalid input." << endl;
			return 0;
		}
	}
	else {
		// heap is not initalized
		cout << "Error: graph must be initalized with \"i\"." << endl;
		return 0;
	}

	return 0;
}

/**
 * parses a string to verify all characters are
 * digits. Allows the first character to be + or -
 * @param inputString, the string to parse
 * @return valid, the boolean result
 */
bool CommandReader::checkStringContainsDigits(string inputString) {
	bool valid = true;
	for (unsigned int k = 0; k < inputString.length(); k++) {
		// if the current char is not a digit
		if (!isdigit(inputString.at(k))) {
			// if current char is not first char or the char is not a '+' or '-'
			if (k != 0 || (inputString.at(k) != '+' && inputString.at(k) != '-')) {
				valid = false;
			}
		}
	}
	return valid;
}