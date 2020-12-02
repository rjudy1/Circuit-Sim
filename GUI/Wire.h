// Author:	Rachael Judy
// Date:	3/3/2020
// Purpose: Provide specification for Wire objects
// Modifications:
//					- 
//					-
// 

#ifndef WIRE_H
#define WIRE_H

#include <cstdlib>
#include <string>
#include <vector>

#include "Gate.h" // needed for gate vector usage in cpp file

using namespace std;

class Gate;

class Wire {
public:
	Wire(int wireNum, string inName = "", char inStatus = 'X');
	~Wire();
	// copy constructor and assignment operator unnecessary for design

	int getWireNum() const;
	string getName() const;
	char getStatus() const;
	void setStatus(char inState);
	vector<Gate*> getGates() const;
	void setGates(Gate* gate); // will add a Gate* to the wire's associated gate vector
	string getHistory(); // adaptable to GUI for output
	void addState(char state); // add state to history


private:
	vector <Gate*> gates; // vector of gates that take input from this wire
	int wireNum;
	string name;
	char status; // 1, 0, or X unknown
	vector <char> history;
};

#endif