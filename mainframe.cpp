#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/html/helpctrl.h>

#include "mainframe.h"
#include "thicknessdialog.h"
#include "propertiesdialog.h"
#include "colordialog.h"
#include "versiondialog.h"
#include "triangledialog.h"
#include "dialogs.h"
#include "openglcanvas.h"


BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_MENU(MENU_NEW, CMainFrame::OnNew)
	EVT_MENU(MENU_QUIT, CMainFrame::OnClose)
	EVT_MENU(MENU_OPEN, CMainFrame::OnOpen)
	EVT_MENU(MENU_SAVE, CMainFrame::OnSave)

	EVT_MENU(MENU_TOOLBAR, CMainFrame::OnToolbar)
	EVT_MENU(MENU_OPEN_HELP, CMainFrame::OnHelp)
	EVT_MENU(MENU_VERSION, CMainFrame::OnVersion)
	EVT_MENU(MENU_THICKNESS, CMainFrame::OnThickness)
	EVT_MENU(MENU_COLOR, CMainFrame::OnColor)
	EVT_MENU(MENU_TRIANGLE, CMainFrame::OnTriangle)
	EVT_MENU(TOOLBAR_DRAW, CMainFrame::OnDraw)
	
	EVT_MENU(POPUP_PROPERTIES, CMainFrame::OnContextProperties)
	EVT_MENU(POPUP_DELETE, CMainFrame::OnContextSuppr)
END_EVENT_TABLE()



CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) {
	//init
	this->help = new wxHtmlHelpController();
	this->num_tri = 0;
	this->couleurcourante = new wxColour("green");
	this->epaisseurtraitcourante = 1;
	//create canvas
	this->canvas = new OpenGLCanvas(this, MAINFRAME_CANVAS);
} //constructor

void CMainFrame::RefreshCanvas(){
	canvas->Refresh();
}

void CMainFrame::CreateMyToolbar(){
	//Create toolbar (with some styles)
	m_toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_FLAT,TOOLBAR_TOOLS);

	//Add pics
	wxBitmap toolBarBitmaps[4];
	toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);

	m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));
	m_toolbar->AddTool(MENU_NEW, wxT("Nouveau"), toolBarBitmaps[0], "Nouveau dessin");
	m_toolbar->AddTool(MENU_OPEN, wxT("Ouvrir"), toolBarBitmaps[1], "Ouvrir un fichier");
	m_toolbar->AddTool(MENU_SAVE, wxT("Sauvegarder"), toolBarBitmaps[2], "Sauvegarder");

	//Add separator
	m_toolbar->AddSeparator();

	m_toolbar->AddCheckTool(TOOLBAR_DRAW, wxT("Dessiner"), toolBarBitmaps[3]);
	
	//Draw toolbar
	m_toolbar->Realize();
	SetToolBar(m_toolbar);
}

void CMainFrame::AddTriangle(Triangle* t){
	this->tab_tri.push_back(t);
	this->num_tri++;
	this->GetMenuBar()->Enable(MENU_TRIANGLE, true);
}

void CMainFrame::DeleteTriangle(int n){
	if(this->num_tri < 1)
		return;
	
	this->tab_tri.erase(this->tab_tri.begin() + this->num_tri - 1);
	this->num_tri -= 1;

	if(this->num_tri < 1)
		this->GetMenuBar()->Enable(MENU_TRIANGLE, false);
}

int CMainFrame::GetEpaisseurTraitCourante(){
	return this->epaisseurtraitcourante;
}

void CMainFrame::SetEpaisseurTraitCourante(int val){
	this->epaisseurtraitcourante = val;
}

wxColour* CMainFrame::GetCouleurCourante(){
	return this->couleurcourante;
}
void CMainFrame::SetCouleurCourante(wxColour* colour){
	this->couleurcourante = colour;
}

bool CMainFrame::IsDrawing(){
	return this->is_drawing;
}

int CMainFrame::GetNumTri(){
	return this->num_tri;
}
void CMainFrame::SetNumTri(int n){
	this->num_tri = n;
}

std::vector<Triangle *> CMainFrame::GetTabTri(){
	return this->tab_tri;
}

wxHtmlHelpController* CMainFrame::GetHelp(){
	return this->help;
}

void CMainFrame::OnNew(wxCommandEvent& event){
	this->tab_tri.clear();
	this->num_tri = 0;
	this->GetMenuBar()->Enable(MENU_TRIANGLE, false);
	canvas->ResetConstructTri();
	canvas->Refresh();
}
void CMainFrame::OnClose(wxCommandEvent& event){
	Close(TRUE);
}
void CMainFrame::OnOpen(wxCommandEvent &event){
	wxFileDialog filedialog(this, "Selectionner un fichier", wxEmptyString, wxEmptyString, "*.tri", wxFD_OPEN, wxDefaultPosition, wxDefaultSize);
	
	if (filedialog.ShowModal() == wxID_CANCEL)
		return;
	
	std::ifstream fo(filedialog.GetPath().fn_str(), std::ifstream::in);
	if (!fo){
      	wxString errormsg, caption;
      	errormsg.Printf(wxT("Unable to open file "));
      	errormsg.Append(filedialog.GetPath());
      	caption.Printf(wxT("Erreur"));
      	wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
      	msg.ShowModal();
      	return ;
	}
	//start reading the file
	fo >> this->num_tri;
	//get the number of iteration
	int i = 0;
	while(fo.good()){
		Triangle* current_triangle = new Triangle();
		
		//read the points in the first line
		fo >> current_triangle->p1.x;
		fo >> current_triangle->p1.y;
		fo >> current_triangle->p2.x;
		fo >> current_triangle->p2.y;
		fo >> current_triangle->p3.x; 
		fo >> current_triangle->p3.y;

		//read the color
		int red;
		int green;
		int blue;

		fo >> red;
		fo >> green;
		fo >> blue;

		current_triangle->colour = new wxColour(red, green, blue);

		//read epaisseur
		fo >> current_triangle->thickness;

		this->tab_tri.push_back(current_triangle);

		i++;
	}
	if(this->num_tri > 0)
		this->GetMenuBar()->Enable(MENU_TRIANGLE, true);
	fo.close();
	canvas->Refresh();
}

void CMainFrame::OnSave(wxCommandEvent &event){
	wxFileDialog filedialog(this, "Selectionner un fichier", wxEmptyString, wxEmptyString, "*.tri", wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize);

	if (filedialog.ShowModal() == wxID_CANCEL)
		return;

	std::ofstream fs(filedialog.GetPath().fn_str(), std::ofstream::out);
	if (!fs){
      	wxString errormsg, caption;
      	errormsg.Printf(wxT("Unable to save file "));
      	errormsg.Append(filedialog.GetPath());
      	caption.Printf(wxT("Erreur"));
      	wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
      	msg.ShowModal();
      	return ;
	}
	//start saving
	fs << this->num_tri;
	for(int i=0; i<this->num_tri; i++){
		Triangle* current_triangle = this->tab_tri[i];
		
		fs << std::endl << std::endl;

		//save the points
		fs << current_triangle->p1.x << " ";
		fs << current_triangle->p1.y << " ";

		fs << current_triangle->p2.x << " ";
		fs << current_triangle->p2.y << " ";

		fs << current_triangle->p3.x << " "; 
		fs << current_triangle->p3.y << " "; 

		fs << std::endl;

		// //save the color
		int r = current_triangle->colour->Red();
		int g = current_triangle->colour->Green();
		int b = current_triangle->colour->Blue();

		fs << r << " ";
		fs << g << " ";
		fs << b << " ";
	
		fs << std::endl;

		//save thickness
		fs << current_triangle->thickness;
	}
}

void CMainFrame::OnToolbar(wxCommandEvent& event){
	m_toolbar->Show(!m_toolbar->IsShown());
}

void CMainFrame::OnVersion(wxCommandEvent& event){
	VersionDialog vdlg(this, -1, wxT("Version"));
	vdlg.ShowModal();
}
void CMainFrame::OnThickness(wxCommandEvent& event){
	ThicknessDialog thdlg(this, -1, wxT("Epaisseur du trait"));
	thdlg.GetSlider()->SetValue(this->epaisseurtraitcourante);
	thdlg.ShowModal();
}
void CMainFrame::OnColor(wxCommandEvent& event){
	ColorDialog cdlg(this, -1, wxT("Couleur"));
	if(this->couleurcourante->Red() == 255)
		cdlg.GetColorRadiobox()->SetSelection(0);
	else if(this->couleurcourante->Blue() == 255)
		cdlg.GetColorRadiobox()->SetSelection(2);
	//default color is green
	else
		cdlg.GetColorRadiobox()->SetSelection(1);
	cdlg.ShowModal();
}
void CMainFrame::OnTriangle(wxCommandEvent& event){
	TriangleDialog tridlg(this, -1, wxT("Gestion des triangles"));
	wxListBox* tri_lb = tridlg.GetListbox();
	tri_lb->Clear();
	//basic string char
	for(int i = 1; i <= this->num_tri; i++){
		wxString str;
		str << "triangle" << i;
		tri_lb->Append(str);
	}
	tri_lb->SetSelection(0);
	tridlg.ShowModal();
}

void CMainFrame::OnDraw(wxCommandEvent& event){
	this->is_drawing = !this->is_drawing;	
	canvas->Refresh();
}

void CMainFrame::OnHelp(wxCommandEvent& event){
	help->DisplayContents();
}

void CMainFrame::OnContextProperties(wxCommandEvent& event){
	this->canvas->OnContextPptes(event);
}
void CMainFrame::OnContextSuppr(wxCommandEvent& event){
	this->canvas->OnContextSuppr(event);
}