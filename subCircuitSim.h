// Author:	Rachael Judy
// Date:	4/4/2020
// Purpose: Perform Circuit simulation in GUI
// Modifications:
//
//
// NOTE - 

#ifndef __subCircuitSim__
#define __subCircuitSim__


//#include <vld.h>

#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <exception>
#include <cstdlib>

#include "Event.h"
#include "Wire.h"
#include "Gate.h"

#include "CircuitSim.h"


/** Implementing CircuitSim */
class subCircuitSim : public CircuitSim
{
	protected:
		// Handlers for CircuitSim events.
		void browseCircuitClicked( wxCommandEvent& event );
		void browseVectorClicked( wxCommandEvent& event );
		void simulateClicked( wxCommandEvent& event );
		void aboutClicked( wxCommandEvent& event );
		void exitClicked( wxCommandEvent& event );

	public:
		subCircuitSim( wxWindow* parent );

		// parse circuit to make wire and gates
		void parseCircuitFile(vector<Wire*>&); // parse circuit to make wires and gates
		// create Events for Wires and perform events
		void parseVectorFile(vector<Wire*>&, priority_queue<Event>&);
		void propogateEvents(vector<Wire*>&, priority_queue<Event>&);
		void printResults(vector<Wire*>&); // display wire histories

	private:
		ifstream inputCircuitFile;
		ifstream inputVectorFile;
		int historySize;
};

#endif // __subCircuitSim__
