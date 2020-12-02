// Author:	Rachael Judy
// Date:	4/4/2020
// Purpose: Perform Circuit simulation in GUI
// Modifications:
//
// NOTE - USERS MUST HAVE WXWIDGETS INCLUDED

#include "subCircuitSim.h"

subCircuitSim::subCircuitSim( wxWindow* parent )
:
CircuitSim( parent )
{
	// prevents user from typing into text boxes - for display of filenames only
	
	circuitFileText->SetEditable(false);
	vectorFileText->SetEditable(false);
	historySize = 0;
	statusBar->SetLabel("Browse a circuit and vector file and click simulate");
}

// browse for circuit file and get matching vector file by default
void subCircuitSim::browseCircuitClicked( wxCommandEvent& event )
{
	statusBar->SetLabel("Select both circuit and vector files.");
    wxFileDialog openFileDialog(this, _("Open circuit txt file"), "", "",
            "txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL) {
		return;     // user clicked cancel
	}

	// close both files if open
	inputCircuitFile.close();
	inputVectorFile.close();

    // proceed loading the circuit file and matching vector file
	string filePath = openFileDialog.GetPath();
    inputCircuitFile.open(filePath); // open browsed file
	inputVectorFile.open(filePath.substr(0, filePath.length() - 4) + "_v.txt");
	if (inputCircuitFile.fail() || inputVectorFile.fail()) {
		wxMessageBox("Error opening files. Try reselecting.", "File failure");
	}

	circuitFileText->SetLabel(openFileDialog.GetFilename()); // display filename
	vectorFileText->SetLabel(openFileDialog.GetFilename()
		.substr(0, openFileDialog.GetFilename().length() - 4) + "_v.txt");
}

// browse for vector file
void subCircuitSim::browseVectorClicked( wxCommandEvent& event )
{
	// check if user wants to use a different vector file
	int response = wxMessageBox("Would you like to reselect a non-matching file?",
		"Vector Selection Confirmation", wxYES_NO);
	if (response == wxNO) {
		return;
	}
	
    wxFileDialog openFileDialog(this, _("Open vector txt file"), "", "",
            "txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;     // the user clicked cancel
	}

	inputVectorFile.close(); // close file if user wants new one

    // proceed loading the file chosen by the user;
    inputVectorFile.open(openFileDialog.GetPath());
	if (inputVectorFile.fail()) {
		wxMessageBox("Error opening vector file. Try reselecting.", "Vector file failure");
	}
    vectorFileText->SetLabel(openFileDialog.GetFilename());
}

void subCircuitSim::simulateClicked( wxCommandEvent& event )
{
	historySize = 0; // resets any previous simulation history sizes
	if (!inputCircuitFile.is_open() || !inputVectorFile.is_open())
	{
		wxMessageBox("You must reselect both circuit and vector files.", "Error reading files");
	}

	// parse circuit file and create wires vector
	vector<Wire*> wires; // create vector of wires
	parseCircuitFile(wires); // will modify vector and create needed gates and wires

	// parse vector file and add preliminary events to queue
	priority_queue<Event> eventQ; // will hold wire change events
	parseVectorFile(wires, eventQ);

	// do events, creating new events as necessary
	propogateEvents(wires, eventQ);

	// display results
	printResults(wires);

	statusBar->SetLabel("Circuit Simulated");
	inputCircuitFile.close();
	inputVectorFile.close();
}

// display the about window
void subCircuitSim::aboutClicked( wxCommandEvent& event )
{
	wxMessageBox("Programmer: Rachael Judy\n CS 1220 - HW 6", "About");
}

// close window when exit clicked
void subCircuitSim::exitClicked( wxCommandEvent& event )
{
	int answer = wxMessageBox("Are you sure you want to exit?", "Confirm Exit", wxYES_NO, this);
	if (answer == wxYES) {
		Close();
	}
}

// parses the circuit file into the wire and gates objects, 
//	modifies the referenced Wire* vector
void subCircuitSim::parseCircuitFile(vector<Wire*>& wires) {
	string line;
	std::getline(inputCircuitFile, line); // skip first line with title
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
				string inStr;
				ss >> inStr;
				int wireNum = stoi(inStr);

				// if the vector isn't large enough to hold the wire number, resize it
				if (wires.size() <= wireNum) {
					wires.resize(wireNum + 1);
				}
				if (wires.at(wireNum) != nullptr) { // if wire already exists, replace it with the new one
					delete wires.at(wireNum);
				}
				wires.at(wireNum) = new Wire(wireNum, name, 'X');
			}
			else if (type == "NOT") {
				int delay;
				ss >> delay;
				string ns; // get rid of "ns"
				ss >> ns;

				string inStr;
				ss >> inStr;
				int inputWire1 = stoi(inStr); // will cause breakout of loop if issue
				ss >> inStr;
				int outputWire = stoi(inStr);

				if (ns != "ns") { // entry error
					continue;
				}

				// resize to hold necessary wires
				if (wires.size() <= inputWire1 || wires.size() <= outputWire) {
					wires.resize(max(inputWire1, outputWire) + 1);
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
				string inStr;
				ss >> inStr;
				int inputWire1 = stoi(inStr); // will cause breakout of loop
				ss >> inStr;
				int inputWire2 = stoi(inStr);
				ss >> inStr;
				int outputWire = stoi(inStr);

				// if valid data didn't come in
				if (ns != "ns") {
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
}

// get and parse vector file
void subCircuitSim::parseVectorFile(vector<Wire*>& wires, priority_queue<Event>& eventQ) {
	
	string line;
	std::getline(inputVectorFile, line); // skip first line with title

	while (!inputVectorFile.eof()) {
		std::getline(inputVectorFile, line); // read each input pad definition
		stringstream ss(line);

		try { // any input failure will cause line to be skipped
			string input;
			ss >> input;
			if (input != "INPUT") {
				continue;
			}

			string name;
			ss >> name;

			string inStr;
			ss >> inStr;
			int time = stoi(inStr); // time of event (local)

			char value = 'Z'; // value wire should take on
			ss >> value;

			if (time == -1 || value == 'Z') {
				continue; // skip line missing data
			}

			// loop through wires to look for match
			for (int i = 0; i < wires.size(); i++) {
				if (wires.at(i) != nullptr) {
					if (wires.at(i)->getName() == name && // find matching wire to name
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
}

// go through event queue until out of events or reach 60 time seconds
void subCircuitSim::propogateEvents(vector<Wire*>& wires, priority_queue<Event>& eventQ) {
	int time = 0;

	// while event queue has values up to 60 time steps with initial
	while (!eventQ.empty() && time <= 60) { 
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

		// check for any wires that should be modified through a gate after any change
		for (int i = 0; i < wires.at(e.getWireNum())->getGates().size(); i++) {
			// creates event for any output wire from input to gate of event
			Event newEvent(wires.at(e.getWireNum())->getGates().at(i)->getOut()->getWireNum(),
				(wires.at(e.getWireNum())->getGates().at(i))->propogateOut(), // get future state 
				(wires.at(e.getWireNum())->getGates().at(i))->getDelay() + time); // get time of event
			eventQ.push(newEvent);
		}
		eventQ.pop();

		// if queue is empty, write last status to history
		historySize = 61; // if queue never empties, history should be of size 60 + starting time
		if (eventQ.empty() && time < 60) {
			for (Wire* w : wires) {
				if (w != nullptr) {
					w->addState(w->getStatus());
					historySize = w->getHistory().size();
				}
			}
		}
	}
}

// display the results in the results text area
void subCircuitSim::printResults(vector<Wire*>& wires) {
	wxString outputString = "";

	// time labels at intervals of 5ns
	outputString += "Time:\t";
	for (int i = 0; i < historySize; i++) {
		if (i % 10 == 0) {
			outputString += "0";
		}
		else if (i % 5 == 0) {
			outputString += "5";
		}
		else {
			outputString += "-";
		}
	}
	outputString += "\r\n";//newline

	// print histories for every existing wire and clean memory
	for (Wire* w : wires) {
		if (w != nullptr) {
			outputString += (w->getName() + ":\t" + w->getHistory() + "\r\n");
			delete w;
		}
	}
	outputString += "\r\n";

	// set text area to display output
	resultTextArea->SetLabel(outputString);
}