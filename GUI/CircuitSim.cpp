///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CircuitSim.h"

///////////////////////////////////////////////////////////////////////////

CircuitSim::CircuitSim( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* fileSelect;
	fileSelect = new wxGridSizer( 2, 7, 0, 0 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Circuit file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Tahoma") ) );
	
	fileSelect->Add( m_staticText1, 0, wxALL, 5 );
	
	circuitFileText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fileSelect->Add( circuitFileText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	circuitBrowseButton = new wxButton( this, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	fileSelect->Add( circuitBrowseButton, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	fileSelect->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Vector file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Tahoma") ) );
	
	fileSelect->Add( m_staticText2, 0, wxALL, 5 );
	
	vectorFileText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fileSelect->Add( vectorFileText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	vectorBrowseButton = new wxButton( this, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	fileSelect->Add( vectorBrowseButton, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	fileSelect->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fileSelect->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fileSelect->Add( 0, 0, 1, wxEXPAND, 5 );
	
	simulateButton = new wxButton( this, wxID_ANY, wxT("Simulate Circuit"), wxDefaultPosition, wxDefaultSize, 0 );
	simulateButton->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Tahoma") ) );
	
	fileSelect->Add( simulateButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer1->Add( fileSelect, 1, wxEXPAND, 5 );
	
	wxGridSizer* results;
	results = new wxGridSizer( 2, 1, 0, 0 );
	
	resultTextArea = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	resultTextArea->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Courier") ) );
	
	results->Add( resultTextArea, 0, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( results, 2, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	menuBar = new wxMenuBar( 0 );
	fileSubMenu = new wxMenu();
	wxMenuItem* aboutMenuOption;
	aboutMenuOption = new wxMenuItem( fileSubMenu, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	fileSubMenu->Append( aboutMenuOption );
	
	wxMenuItem* exitMenuButton;
	exitMenuButton = new wxMenuItem( fileSubMenu, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	fileSubMenu->Append( exitMenuButton );
	
	menuBar->Append( fileSubMenu, wxT("File") ); 
	
	this->SetMenuBar( menuBar );
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	circuitBrowseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::browseCircuitClicked ), NULL, this );
	vectorBrowseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::browseVectorClicked ), NULL, this );
	simulateButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::simulateClicked ), NULL, this );
	this->Connect( aboutMenuOption->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CircuitSim::aboutClicked ) );
	this->Connect( exitMenuButton->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CircuitSim::exitClicked ) );
}

CircuitSim::~CircuitSim()
{
	// Disconnect Events
	circuitBrowseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::browseCircuitClicked ), NULL, this );
	vectorBrowseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::browseVectorClicked ), NULL, this );
	simulateButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CircuitSim::simulateClicked ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CircuitSim::aboutClicked ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CircuitSim::exitClicked ) );
	
}
