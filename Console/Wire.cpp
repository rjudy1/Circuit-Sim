// Author:	Rachael Judy
// Date:	3/30/2020
// Purpose: Provide implementation for Wire objects
// Modifications:
//					- 4/1/2020 - added history getters and setters
//					-

#include "Wire.h"

Wire::Wire(int inWireNum, string inName, char inStatus) : 
	wireNum(inWireNum), name(inName), status(inStatus) {}

// destroy vector of gates
Wire::~Wire() {
	for (Gate* g : gates) {
		delete g;
		g = NULL;
	}
}

// will be index in vector
int Wire::getWireNum() const {
	return wireNum;
}

string Wire::getName() const {
	return name;
}

// gets/sets current state of wire
char Wire::getStatus() const {
	return status;
}
void Wire::setStatus(char inState) {
	status = inState;
}

// gets the gate vector
vector<Gate*> Wire::getGates() const {
	return gates;
}
// adds new gate to vector
void Wire::setGates(Gate* gate) {
	gates.push_back(gate);
}

// returns a string representing the history
string Wire:: getHistory() {
	string historyStr;
	// goes through history vector, creating string based on characters
	for (int i = 0; i < history.size(); i++) {
		if (history.at(i) == '0') {
			historyStr += "_";
		}
		else if (history.at(i) == '1') {
			historyStr += '-';
		}
		else {
			historyStr += "x";
		}
	}

	return historyStr;
}

// adds new state to history vector
void Wire::addState(char state) {
	history.push_back(state);
}