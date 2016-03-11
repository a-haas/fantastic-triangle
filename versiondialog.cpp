#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "versiondialog.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE()

VersionDialog::VersionDialog( wxWindow *parent, wxWindowID id, const wxString &title) 
: wxDialog( parent, id, title){
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );
	wxStaticText *text_version = new wxStaticText( this, ID_TEXT_VERSION, wxT("Version 1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxButton *ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	//alignement
	conteneur->Add( text_version, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add( ok_button, 0, wxALIGN_CENTRE|wxALL, 5);

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
}