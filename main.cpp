#include "wx/wx.h" 

#include "mainframe.h"
#include "dialogs.h"

class MyApp: public wxApp 
{
	virtual bool OnInit();
	CMainFrame *m_MainFrame;
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit() 
{
	m_MainFrame = new CMainFrame( wxString("Application de dessin"), wxPoint(50,50), wxSize(450,340) );

	m_MainFrame->Show(TRUE);
	
	/*Declare*/
	wxMenuBar *menu_bar = new wxMenuBar();
	
	wxMenu *file_menu = new wxMenu();
	wxMenu *view_menu = new wxMenu();
	wxMenu *options_menu = new wxMenu();
	wxMenu *help_menu = new wxMenu();

	/*ajout des menus à la bar*/
	menu_bar->Append(file_menu, wxT("Fichier"));
	menu_bar->Append(view_menu, wxT("Affichage"));
	menu_bar->Append(options_menu, wxT("Options"));
	menu_bar->Append(help_menu, wxT("Aide"));

	/*Ajout des rubriques*/
	
	//file
	file_menu->Append(MENU_NEW, wxT("Nouveau\tCtrl-N"));
	//Ajout de séparateur (esthétique)
	file_menu->AppendSeparator();
	
	file_menu->Append(MENU_OPEN, wxT("Ouvrir\tCtrl-O"));
	//Ajout de séparateur (esthétique)
	file_menu->AppendSeparator();

	file_menu->Append(MENU_SAVE, wxT("Enregistrer\tCtrl-S"));
	//Ajout de séparateur (esthétique)
	file_menu->AppendSeparator();

	file_menu->Append(MENU_QUIT, wxT("Quitter\tCtrl-X"));
	//Ajout de séparateur (esthétique)
	file_menu->AppendSeparator();

	//options
	options_menu->Append(MENU_THICKNESS, wxT("Epaisseur trait\tCtrl-E"));
	options_menu->Append(MENU_COLOR, wxT("Couleur"));
	options_menu->Append(MENU_TRIANGLE, wxT("Gestion des triangles"));
	//help
	help_menu->Append(MENU_OPEN_HELP, wxT("Ouvrir l'aide\tCtrl-H"));
	help_menu->Append(MENU_VERSION, wxT("Version"));
	//view
	view_menu->AppendCheckItem(MENU_TOOLBAR, wxT("Barre d'outils\tCtrl-B"));
	view_menu->Check(MENU_TOOLBAR,TRUE);

	//Griser gestion des triangles
	menu_bar->Enable(MENU_TRIANGLE,false);

	//afficher la barre de menu
	m_MainFrame->SetMenuBar(menu_bar);

	//afficher toolbar
	m_MainFrame->CreateMyToolbar();

	//creer l'aide
	if( !m_MainFrame->GetHelp()->Initialize("HELP")){
		wxLogError(wxT("Cannot initialize the help system, aborting."));
		return false;
	}

	return TRUE;
} 


