// Author:	Rachael Judy
// Date:	3/3/2020
// Purpose: Provide specification for Gate objects
// Modifications:
//					- 4/6/2020 - Removed unneccessary methods
//					- 


#ifndef GATE_H
#define GATE_H

#include <cstdlib>
#include <string>
#include <vector>

#include "Wire.h" // needs to be included for use in class attributes

using namespace std;

class Wire;

class Gate {
public:
	Gate(string inType = "", int delay = 0, Wire * iin1=nullptr, Wire * iin2=nullptr, Wire* iout=nullptr);
	// no destructor needed because wires involved will all be deleted

	Wire* getIn1() const;
	Wire* getIn2() const;
	Wire* getOut() const;
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