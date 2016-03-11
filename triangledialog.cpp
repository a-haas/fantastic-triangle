#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "propertiesdialog.h"
#include "triangledialog.h"
#include "mainframe.h"

BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
	EVT_BUTTON(ID_PROPERTIES_TRIANGLE, TriangleDialog::OnProperties)
	EVT_BUTTON(ID_DELETE_TRIANGLE, TriangleDialog::OnDelete)
END_EVENT_TABLE()

TriangleDialog::TriangleDialog( wxWindow *parent, wxWindowID id, const wxString &title) 
: wxDialog( parent, id, title){
	//Same thing as before
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );

	wxStaticText *text_triangle = new wxStaticText( this, ID_TEXT_TRIANGLE, wxT("Liste des triangles : "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);

	//Sizer
	/**horizontal**/
	wxBoxSizer *horizontal = new wxBoxSizer( wxHORIZONTAL );
	//ListBox
	//Choix de la liste 
	//default list to set size auto
	wxString choices[] = { wxT("triangle0") };
	this->triangle_listbox = new wxListBox( this, ID_LISTBOX_TRIANGLE, wxDefaultPosition, wxDefaultSize, 1, choices);	

	/**buttons**/
	wxBoxSizer *buttons = new wxBoxSizer( wxVERTICAL );
	wxButton *ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);
	wxButton *properties_button = new wxButton( this, ID_PROPERTIES_TRIANGLE, wxT("Propriétés"), wxDefaultPosition);
	wxButton *delete_button = new wxButton( this, ID_DELETE_TRIANGLE, wxT("Supprimer"), wxDefaultPosition);

	//add to buttons box sizer
	buttons->Add( properties_button, 0, wxALIGN_CENTRE|wxALL, 5);
	buttons->Add( delete_button, 0, wxALIGN_CENTRE|wxALL, 5);
	buttons->Add( ok_button, 0, wxALIGN_CENTRE|wxALL, 5);	

	//add to horizontal box sizer
	horizontal->Add(triangle_listbox, 0, wxALIGN_CENTRE|wxALL, 5);
	horizontal->Add( buttons, 0, wxALIGN_CENTRE|wxALL, 5);

	//alignement
	conteneur->Add( text_triangle, 0, wxALIGN_LEFT|wxALL, 5);
	conteneur->Add( horizontal, 0, wxALIGN_CENTRE|wxALL, 0);

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
}
wxListBox* TriangleDialog::GetListbox(){
	return this->triangle_listbox;
}
void TriangleDialog::OnProperties(wxCommandEvent& event){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	int n = this->triangle_listbox->GetSelection();
	Triangle* selected_tri = frame->GetTabTri()[n];
	PropertiesDialog pdlg(this, -1, wxT("Proprietes"), selected_tri);
	//set name
	pdlg.SetTextctrlIDTriangle(this->triangle_listbox->GetStringSelection());
	//set thickness
	pdlg.GetThicknessTextctrl()->SetValue(selected_tri->thickness);
	//set color
	if(selected_tri->colour->Red() == 255)
		pdlg.GetColorRadiobox()->SetSelection(0);
	else if(selected_tri->colour->Blue() == 255)
		pdlg.GetColorRadiobox()->SetSelection(2);
	//default color is green
	else
		pdlg.GetColorRadiobox()->SetSelection(1);
	pdlg.ShowModal();
}

void TriangleDialog::OnDelete(wxCommandEvent& event){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	int n = this->triangle_listbox->GetSelection();
	if(n != wxNOT_FOUND	)
		this->triangle_listbox->Delete(n);
	frame->DeleteTriangle(n);

	//reset names
	this->triangle_listbox->Clear();
	//basic string char
	for(int i = 1; i <= frame->GetNumTri(); i++){
		wxString str;
		str << "triangle" << i;
		this->triangle_listbox->Append(str);
	}

	frame->RefreshCanvas();
}