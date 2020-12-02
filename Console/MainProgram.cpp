// Name:	Rachael Judy
// Date:	3/30/2020
// Purpose:	Reads input circuit and vector files, creates necessary objects and produces waveform
//
// LEAKING AT INVALID LINE ENTRIES

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


int main(int argc, char** argv) {
	// get circuit file opened
	bool fileOpen = false;
	string filename;
	ifstream inputCircuitFile;
	while (fileOpen == false) {
		cout << "Enter circuit file name (base only): ";		
		cin >> filename;

		inputCircuitFile.open(filename + ".txt");
		if (inputCircuitFile.is_open()) {
			fileOpen = true;
		}
		else {
			cout << "Enter a valid circuit file name this time. " << endl;
		}
	}

	// parse circuit file
	string line;
	std::getline(inputCircuitFile, line); // skip first line with title
	vector<Wire*> wires; // create vector of wires
	while (!inputCircuitFile.eof()) {
		std::getline(inputCircuitFile, line);
		stringstream ss(line);

		try {		
			// if type is not one of the available types, line will be skipped
			string type;
			ss >> type;

			if (type == "INPUT" || type == "OUTPUT") { // need to create a new wire, 
													   // will ignore anything on line past the needed info
				string name;
				ss >> name;
				int wireNum = -1; // if missing a wire num
				ss >> wireNum;

				if (wireNum < 0) {
					continue;
				}

				// if the vector isn't large enough to hold the wire number, resize it
				if (wires.size() <= wireNum) {
					wires.resize(wireNum + 1);
				}
				wires.at(wireNum) = new Wire(wireNum, name, 'X');
				
			}
			else if (type == "NOT") {
				int delay;
				ss >> delay;
				string ns; // get rid of "ns"
				ss >> ns;

				int inputWire1 = -1; // will cause exception if new data not on line
				ss >> inputWire1;
				int outputWire = -1;
				ss >> outputWire;

				if (inputWire1 == -1 || outputWire == -1) {
					continue;
				}

				// resize to hold necessary wires
				if (wires.size() <= inputWire1 || wires.size() <= outputWire) {
					wires.resize(max(inputWire1, outputWire)+1);
				}

				// check if wires are in existence already
				if (wires.at(inputWire1) == nullptr) {
					wires.at(inputWire1) = new Wire(inputWire1, to_string(inputWire1), 'X');
				}
				if (wires.at(outputWire) == nullptr) {
					wires.at(outputWire) = new Wire(outputWire, to_string(outputWire), 'X');
				}
				
				// adds gate to wire's vector of gates
				wires.at(inputWire1)->setGates(new Gate(type, delay, 
					wires.at(inputWire1), wires.at(inputWire1), wires.at(outputWire)));				
			}
			else if (type == "AND" || type == "OR" || type == "NAND" ||
				type == "NOR" || type == "XOR" || type == "XNOR") {
				int delay;
				ss >> delay;
				string ns;
				ss >> ns;

				// get wire numbers
				int inputWire1 = -1;
				ss >> inputWire1;
				int inputWire2 = -1;
				ss >> inputWire2;
				int outputWire = -1;
				ss >> outputWire;

				// if valid data didn't come in
				if (inputWire1 == -1 || inputWire2 == -1 || outputWire == -1) {
					continue;
				}

				// resize vector if needed for creation of wires
				if (wires.size() <= inputWire1 || wires.size() <= outputWire || wires.size() <= inputWire2) {
					wires.resize(max(max(inputWire1, inputWire2), outputWire) + 1);
				}

				// check if all three needed wires exist, and creates them if not with wireNum as name
				if (wires.at(inputWire1) == nullptr) {
					wires.at(inputWire1) = new Wire(inputWire1, to_string(inputWire1), 'X');
				}
				if (wires.at(inputWire2) == nullptr) {
					wires.at(inputWire2) = new Wire(inputWire2, to_string(inputWire2), 'X');
				}
				if (wires.at(outputWire) == nullptr) {
					wires.at(outputWire) = new Wire(outputWire, to_string(outputWire), 'X');
				}
				// adds gate to Wire vector of gates
				wires.at(inputWire1)->setGates(new Gate(type, delay, wires.at(inputWire1),
					wires.at(inputWire2), wires.at(outputWire)));
				wires.at(inputWire2)->setGates(new Gate(type, delay, wires.at(inputWire1),
					wires.at(inputWire2), wires.at(outputWire)));
			}
		}
		catch (exception e) {
			continue; // if anything goes wrong with input that causes an exception, skip line
		}
	}
	inputCircuitFile.close();

	////////////////////////////////////// VECTOR FILE /////////////////////////////////////////////////

	// get and parse vector file
	priority_queue<Event> eventQ; // will hold wire change events
	fileOpen = false;
	ifstream inputVectorFile;
	filename += "_v"; // on first attempt, assumes entered filename is correct with _v
	while (fileOpen == false) {
		inputVectorFile.open(filename + ".txt"); 
		if (inputVectorFile.is_open()) {
			fileOpen = true;
		}
		else { // if anticipated file doesn't exist, get other file base name
			cout << "Enter vector file name (full name without extension): ";
			cin >> filename;
		}
	}

	std::getline(inputVectorFile, line); // skip first line with title
	while (!inputVectorFile.eof()) {
		std::getline(inputVectorFile, line); // read each input pad definition
		stringstream ss(line);

		try { // any input failure will cause line to be skipped
			string input;
			ss >> input;
			if (input != input) {
				break;
			}

			string name;
			ss >> name;

			int time; // time of event (local)
			ss >> time;

			char value; // value wire should take on
			ss >> value;
			
			// loop through wires
			for (int i = 0; i < wires.size(); i++) {
				if (wires.at(i) != nullptr) {
					if (wires.at(i)->getName() == name && 
						(value == 'X' || value == '0' || value == '1')) { // make sure valid value change
						Event e(i, value, time); // creates event for wire of focus
						eventQ.push(e); // add to event queue
						break; // if wire found and event added, doesn't need to check for more definitions
					}
				}
			}
		}
		catch (exception e) {
			continue;
		}
	}
	inputVectorFile.close();
	

	/////////////////////////////////////// AT EVENT QUEUE /////////////////////////////////////////

	// go through event queue until out of events or reach 60 time seconds
	int time = 0;
	int historySize = 0;
	while (!eventQ.empty() && time <= 60) { // while event queue has values up to 60 time steps
		Event e = eventQ.top();
		if (time < e.getEventTime()) { // propogate history up to time point of change
			for (Wire* w : wires) {
				if (w != nullptr)
					for (int i = 0; i < e.getEventTime() - time; i++) {
						w->addState(w->getStatus()); // adds to history vector for each wire
					}
			}
		}

		// set time to current event time and state to event requested state
		time = e.getEventTime();
		wires.at(e.getWireNum())->setStatus(e.getState());

		wires.at(e.getWireNum());
		// check for any wires that should be modified through a gate after any change
		for (int i = 0; i < wires.at(e.getWireNum())->getGates().size(); i++) {
			// creates event for any output wire from input to gate of event
			Event newEvent(wires.at(e.getWireNum())->getGates().at(i)->getOut()->getWireNum(),
				(wires.at(e.getWireNum())->getGates().at(i))->propogateOut(), // get future state 
				(wires.at(e.getWireNum())->getGates().at(i))->getDelay() + time);
			eventQ.push(newEvent);
		}
		eventQ.pop();

		// if queue is empty, write last history, up to nearest time of ten + final timestamp
		if (eventQ.empty()) {
			for (Wire* w : wires) {
				if (w != nullptr) {
					for (int i = 0; (i + time) % 10 != 1; i++) {
						w->addState(w->getStatus()); // write state to history
						historySize = time + i;
					}
				}
			}
		}
	}
	
	///////////////////// Display Results ///////////////////////////////

	// time labels at intervals of 5ns
	cout << "Time:\t";
	for (int i = 0; i <= historySize; i++) {
		if (i % 10 == 0) {
			cout << "0";
		}
		else if (i % 5 == 0) {
			cout << "5";
		}
		else {
			cout << "-";
		}
	}
	cout << endl;

	// print histories for every existing wire and clean memory
	for (Wire* w : wires) {
		if (w != nullptr) {
			cout << w->getName() << ":\t" << w->getHistory() << endl;
			delete w;
		}
	}
	cout << endl;
}