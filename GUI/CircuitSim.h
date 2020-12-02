///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CIRCUITSIM_H__
#define __CIRCUITSIM_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CircuitSim
///////////////////////////////////////////////////////////////////////////////
class CircuitSim : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* circuitFileText;
		wxButton* circuitBrowseButton;
		wxStaticText* m_staticText2;
		wxTextCtrl* vectorFileText;
		wxButton* vectorBrowseButton;
		wxButton* simulateButton;
		wxTextCtrl* resultTextArea;
		wxMenuBar* menuBar;
		wxMenu* fileSubMenu;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void browseCircuitClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void browseVectorClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void simulateClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void aboutClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void exitClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CircuitSim( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Circuit Simulator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 741,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~CircuitSim();
	
};

#endif //__CIRCUITSIM_H__
