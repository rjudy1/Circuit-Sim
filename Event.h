// Author:	Rachael Judy
// Date:	3/3/2020
// Purpose: Provide specification for Events
// Modifications:
//					- removed unneccessary functions
//					-

#include <cstdlib>

#include "Wire.h"

using namespace std;

class Event {
public:
	Event(int inwireNum, char futureState, int time);

	// need getters and setters
	int getEventTime();
	char getState();
	int getWireNum();

	// for priority queue
	friend bool operator<(const Event& e1, const Event& e2);

private:
	static int counter; // will be incremented to track which event should occur in queue
	int count; // secondary key

	int wireNum;
	char state;
	int eventTime; // time when event should occur
};