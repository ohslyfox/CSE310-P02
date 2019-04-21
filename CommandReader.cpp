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
 * module, on the currentGraph stored in the CommandReader.
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

	/* e command stops the program
	 * expected input for token[0] .. token[3]:
	 * e ~ ~ ~
	 */
	if (cmd == 'e' || cmd == 'E') {
		return 1; // stop code
	}
	/* i command initializes a new graph to replace 
	 * the current graph.
	 * expected input for token[0] .. token[3]:
	 * i ~ ~ ~
	 */
	if (cmd == 'i' || cmd == 'I') {
		try {
			// recreate graph if it exists
			if (currentGraph != NULL) {
				delete this->currentGraph;
				this->currentGraph = NULL;
			}
			// load new graph
			Graph* temp = Util::initializeGraph();
			this->currentGraph = temp;
			Util::loadGraph(temp);
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
		catch (exception e) {
			cout << "Error: " << e.what() << endl;
		}
	}
	// if the command is not 'e' or 'i' check if graph has been initalized before 
	// allowing other commands... if it is not initialized print an initilization error
	else if (this->currentGraph != NULL) {
		/* w command prints the current graph to the console
		 * expected input for token[0] .. token[3]:
		 * w ~ ~ ~
		 */
		if (cmd == 'w' || cmd == 'W') {
			Util::printGraph(this->currentGraph);
		}
		/* c command runs Dijkstras shortest path
		 * algorithm on the current graph. If flag == 0
		 * the length of the path from source to
		 * destination will be printed. if flag == 1 
		 * the vertices of the path will be printed.
		 * c int:source int:destination int:flag
		 */
		else if (cmd == 'c' || cmd == 'C') {
			try {
				if (tokens[1] == "~" || tokens[2] == "~" || tokens[3] == "~") {
					throw "Error: invalid input.";
				}
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
		// graph is not initalized
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