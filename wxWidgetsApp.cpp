// Purpose:  Template wxWidgets application class header file.  Modify as directed below
// Author:   Dr. Keith A. Shomper
// Date:     24 March 2014
//
// Modify the source code in this file by:
// 1.  Defining FILENAME to be the file name of the header file which was automatically
//     built using the Tools ... Generate Inherited Class (F6)
// 2.  Define CLASSNAME to be the name of the class defined in FILENAME

// Modified 4/4/2020 - Rachael Judy - CS 1220 - HW 6
// Purpose: To be used with circuit simulator GUI

#define FILENAME  "subCircuitSim.h"
#define CLASSNAME  subCircuitSim

#include "wxWidgetsApp.h"
#include FILENAME

IMPLEMENT_APP(wxWidgetsApp)

wxWidgetsApp::wxWidgetsApp()  {
}

wxWidgetsApp::~wxWidgetsApp() {
}

bool wxWidgetsApp::OnInit() {
    CLASSNAME* frame = new CLASSNAME( (wxWindow*)NULL );
    frame ->Show();
    SetTopWindow( frame );
    return true;
}
