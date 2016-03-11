#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "mainframe.h"
#include "colordialog.h"


BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
	EVT_RADIOBOX(ID_RADIOBOX_COLOR, ColorDialog::OnColorChange)
END_EVENT_TABLE()

ColorDialog::ColorDialog( wxWindow *parent, wxWindowID id, const wxString &title) 
: wxDialog( parent, id, title){
	//Same thing as before
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );
	wxStaticText *text_thickness = new wxStaticText( this, ID_TEXT_COLOR, wxT("Choisir la nouvelle couleur : "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	wxButton *ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);
	//RadioBox
	//Choix des couleurs
	wxString strs8[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	color_radiobox = new wxRadioBox( this, ID_RADIOBOX_COLOR, wxT("Couleur"), wxDefaultPosition, wxDefaultSize, 3, strs8, 0, wxRA_SPECIFY_ROWS);

	//alignement
	conteneur->Add( text_thickness, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add(color_radiobox, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add( ok_button, 0, wxALIGN_CENTRE|wxALL, 5);

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	// conteneur->SetSizeHints( this );
}

wxRadioBox* ColorDialog::GetColorRadiobox(){
	return this->color_radiobox;
}

void ColorDialog::OnColorChange(wxCommandEvent& event){
	CMainFrame* mainframe = dynamic_cast<CMainFrame*>(this->GetParent()); 
	int n = this->color_radiobox->GetSelection();
	switch(n){
		case 0:
			mainframe->SetCouleurCourante(new wxColour("red"));
			break;
		case 1:
			mainframe->SetCouleurCourante(new wxColour("green"));
			break;
		case 2:
			mainframe->SetCouleurCourante(new wxColour("blue"));			
			break;
		default:
			mainframe->SetCouleurCourante(new wxColour("green"));
			break;
	}
}