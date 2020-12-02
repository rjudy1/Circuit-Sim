// Author:	Rachael Judy
// Date:	3/30/2020
// Purpose: Provide implementation for Gate objects
// Modifications:
//					- 
//					-
// 

#include "Gate.h"

Gate::Gate(string inType, int inDelay, Wire* iin1, Wire* iin2, Wire* iout) {
	type = inType;
	delay = inDelay;
	in1 = iin1;
	in2 = iin2;
	out = iout;
}

// destroy wires associated with gate
// don't need to destroy pointers because pointers associated with wires 
// are all in the wires vector and will be deleted
Gate::~Gate() {
	if (in1 != NULL) {
//		delete in1;
//		in1 = NULL;
	}
	if (in2 != NULL) {
//		delete in2;
//		in2 = NULL;
	}
	if (out != NULL) {
//		delete out;
//		out = NULL;
	}
}

Wire* Gate::getIn1() const {
	return in1;
}
void Gate::setIn1(Wire* i1) {
	in1 = i1;
}

Wire* Gate::getIn2() const {
	return in2;
}
void Gate::setIn2(Wire* i2) {
	in2 = i2;
}

Wire* Gate::getOut() const {
	return out;
}
void Gate::setOut(Wire* iout) {
	out = iout;
}

int Gate::getDelay() const {
	return delay;
}

// returns what the future value after gate is propogated should be
char Gate::propogateOut() {
	char futureVal = 'X';
	if (type == "AND") {
		if (in1->getStatus() == '0' || in2->getStatus() == '0') {
			futureVal = '0';
		}
		else if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else {
			futureVal = '1';
		}
	}
	else if (type == "OR") {
		if (in1->getStatus() == '1' || in2->getStatus() == '1') {
			futureVal = '1';
		}
		else if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else {
			futureVal = '0';
		}
	}
	// assumes NOT gates have same in1 and in2
	else if (type == "NOT") {
		if (in1->getStatus() == '0') {
			futureVal = '1';
		}
		else if (in1->getStatus() == 'X') {
			futureVal = 'X';
		}
		else {
			futureVal = '0';
		}
	}
	else if (type == "XOR") {
		if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else if (in1->getStatus() == in2->getStatus()) {
			futureVal = '0';
		}
		else {
			futureVal = '1';
		}
	}
	else if (type == "NAND") {
		if (in1->getStatus() == '0' || in2->getStatus() == '0') {
			futureVal = '1';
		}
		else if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else {
			futureVal = '0';
		}
	}
	else if (type == "NOR") {
		if (in1->getStatus() == '1' || in2->getStatus() == '1') {
			futureVal = '0';
		}
		else if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else {
			futureVal = '1';
		}
	}
	else if (type == "XNOR") {
		if (in1->getStatus() == 'X' || in2->getStatus() == 'X') {
			futureVal = 'X';
		}
		else if (in1->getStatus() == in2->getStatus()) {
			futureVal = '1';
		}
		else {
			futureVal = '0';
		}
	}

	return futureVal;
}