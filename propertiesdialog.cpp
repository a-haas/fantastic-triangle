#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/spinctrl.h>

#include "dialogs.h"
#include "thicknessdialog.h"
#include "propertiesdialog.h"

BEGIN_EVENT_TABLE(PropertiesDialog, wxDialog)
	EVT_SPINCTRL(ID_SPINCTRL_PROPERTIES, PropertiesDialog::OnPropertiesThickness)
	EVT_RADIOBOX(ID_RADIOBOX_COLOR_PROPERTIES, PropertiesDialog::OnPropertiesColor)
END_EVENT_TABLE()

PropertiesDialog::PropertiesDialog( wxWindow *parent, wxWindowID id, const wxString &title, Triangle* t) 
: wxDialog( parent, id, title){
	this->triangle = t;
	//Same thing as before
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );

	//Sizer
	/**horizontal**/
	wxBoxSizer *horizontal = new wxBoxSizer( wxHORIZONTAL );

	//vertical
	wxBoxSizer *vertical = new wxBoxSizer( wxVERTICAL );
	//Spin control
	wxStaticText *text_thickness = new wxStaticText( this, ID_TEXT_THICKNESS_PROPERTIES, wxT("Epaisseur du trait"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	this->thickness_ctrl = new wxSpinCtrl( this, ID_SPINCTRL_PROPERTIES, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 1); 	

	//Text control
	wxStaticText * text_idTriangle = new wxStaticText( this, ID_TEXT_TRIANGLE_PROPERTIES, wxT("Identifiant du triangle"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	this->idTriangle_textctrl = new wxTextCtrl( this, ID_LISTBOX_TRIANGLE);

	vertical->Add(text_idTriangle, 0, wxALIGN_CENTRE|wxALL, 5);
	vertical->Add(idTriangle_textctrl, 0, wxALIGN_CENTRE|wxALL, 5);

	vertical->Add(text_thickness, 0, wxALIGN_CENTRE|wxALL, 5);
	vertical->Add(thickness_ctrl, 0, wxALIGN_CENTRE|wxALL, 5);

	//Horizontal couleur
	wxString strs8[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	this->color_radiobox = new wxRadioBox( this, ID_RADIOBOX_COLOR_PROPERTIES, wxT("Couleur"), wxDefaultPosition, wxDefaultSize, 3, strs8, 0, wxRA_SPECIFY_ROWS);

	//add to horizontal box sizer
	horizontal->Add( vertical, 0, wxALIGN_CENTRE|wxALL, 5);
	horizontal->Add( color_radiobox, 0, wxALIGN_CENTRE|wxALL, 5);

	wxButton *ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	//alignement
	conteneur->Add( horizontal, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add( ok_button, 0, wxALIGN_CENTRE|wxALL, 5);

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
}
void PropertiesDialog::SetTextctrlIDTriangle(wxString str){
	this->idTriangle_textctrl->SetValue(str);
}

wxRadioBox* PropertiesDialog::GetColorRadiobox(){
	return this->color_radiobox;
}

wxSpinCtrl* PropertiesDialog::GetThicknessTextctrl(){
	return this->thickness_ctrl;
}

void PropertiesDialog::OnPropertiesThickness(wxSpinEvent& event){
	this->triangle->thickness = this->thickness_ctrl->GetValue();
}
void PropertiesDialog::OnPropertiesColor(wxCommandEvent& event){
	int n = this->color_radiobox->GetSelection();
	switch(n){
		case 0:
			this->triangle->colour = new wxColour("red");
			break;
		case 1:
			this->triangle->colour = new wxColour("green");
			break;
		case 2:
			this->triangle->colour = new wxColour("blue");			
			break;
		default:
			this->triangle->colour = new wxColour("green");
			break;
	}
}