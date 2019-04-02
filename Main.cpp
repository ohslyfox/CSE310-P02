#include <iostream>
#include "CommandReader.h"

int main() {
	cout << "-----------------------" << endl;
	cout << "Patrick Finger" << endl;
	cout << "CSE310 T-TH 4:30-5:45PM" << endl;
	cout << "Project 2" << endl;
	cout << "Professor Xue" << endl;
	cout << "-----------------------" << endl << endl;

	CommandReader* cr = new CommandReader();
	string input;
	int f = 0;
	while (f == 0) {
		cout << "Enter a command: ";
		getline(cin, input);
		f = cr->executeStringCommand(input);
	}

	delete cr;
	return 0;
}