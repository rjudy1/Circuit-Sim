// Author:	Rachael Judy
// Date:	3/3/2020
// Purpose: Provide implementation for Event objects
// Modifications:
//					- added counter to serve as secondary key
//					-

#include "Event.h"

// set attributes for event and increase counter for secondary key
Event::Event(int inWireNum, char futureState, int time) : 
	wireNum(inWireNum), state(futureState), eventTime(time) {
	count = counter;
	counter++;
}

int Event::getEventTime() {
	return eventTime;
}

char Event::getState() {
	return state;
}

int Event::getWireNum() {
	return wireNum;
}

// if event should occur sooner, is ranked higher
bool operator<(const Event& e1, const Event& e2) {
	if (e1.eventTime == e2.eventTime) {
		return e1.count > e2.count;
	}
	return (e1.eventTime > e2.eventTime);
}

int Event::counter = 0; // initialize counter to zero