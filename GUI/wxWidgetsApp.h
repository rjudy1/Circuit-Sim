// Purpose:  Template wxWidgets application class header file.  No modification to this file are required
// Author:   Dr. Keith A. Shomper
// Date:     17 March 
// MODIFICATIONS: Rachael Judy - 4/4/2020
// Purpose: For use with circuit simulator hw6


#ifndef __WXWIDGETSAPP_H
#define __WXWIDGETSAPP_H

#include <wx/wx.h>

class wxWidgetsApp : public wxApp {
  public:
    wxWidgetsApp();
    virtual ~wxWidgetsApp();
    virtual bool OnInit();
};

DECLARE_APP(wxWidgetsApp)

#endif
