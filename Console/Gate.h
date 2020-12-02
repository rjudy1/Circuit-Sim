// Author:	Rachael Judy
// Date:	3/30/2020
// Purpose: Provide specification for Gate objects
// Modifications:
//					- 
//					-


#ifndef GATE_H
#define GATE_H

#include <cstdlib>
#include <string>
#include <vector>

#include "Wire.h" // needs to be included for use in class

using namespace std;

class Wire;

class Gate {
public:
	Gate(string inType = "", int delay = 0, Wire * iin1=nullptr, Wire * iin2=nullptr, Wire* iout=nullptr);
	~Gate();

	Wire* getIn1() const;
	void setIn1(Wire* i1);
	Wire* getIn2() const;
	void setIn2(Wire* i2);
	Wire* getOut() const;
	void setOut(Wire* out);
	int getDelay() const;

	char propogateOut();

private:
	Wire* in1;
	Wire* in2;
	Wire* out;
	string type;
	int delay;
};

#endif