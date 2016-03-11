#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "mainframe.h"
#include "thicknessdialog.h"

BEGIN_EVENT_TABLE(ThicknessDialog, wxDialog)
	EVT_SLIDER(ID_SLIDER_THICKNESS, ThicknessDialog::OnChange)
END_EVENT_TABLE()

ThicknessDialog::ThicknessDialog( wxWindow *parent, wxWindowID id, const wxString &title) 
: wxDialog( parent, id, title){
	//Same thing as before
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );
	wxStaticText *text_thickness = new wxStaticText( this, ID_TEXT_THICKNESS, wxT("Choisir la nouvelle épaisseur du trait : "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	wxButton *ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);
	//Slider
	this->slider = new wxSlider( this, ID_SLIDER_THICKNESS, 1, 1, 10, wxDefaultPosition, wxSize(100, 50),wxSL_LABELS);

	//alignement
	conteneur->Add( text_thickness, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add(this->slider, 0, wxALIGN_CENTRE|wxALL, 5);
	conteneur->Add( ok_button, 0, wxALIGN_CENTRE|wxALL, 5);

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
}

void ThicknessDialog::OnChange(wxCommandEvent& event){
	dynamic_cast<CMainFrame*>(this->GetParent())->SetEpaisseurTraitCourante(this->slider->GetValue());	
}

wxSlider* ThicknessDialog::GetSlider(){
	return this->slider;
}