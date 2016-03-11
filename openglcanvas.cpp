#include <stdio.h>
#include <stdlib.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <vector>

#include "openglcanvas.h"
#include "mainframe.h"
#include "triangle.h"
#include "dialogs.h"
#include "propertiesdialog.h"

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
	EVT_PAINT(OpenGLCanvas::OnPaint)
	EVT_SIZE(OpenGLCanvas::OnSize)
	EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)

	//MOUSE EVENT
	EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
	EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
	EVT_MOTION(OpenGLCanvas::OnMouseMove)
	EVT_RIGHT_DOWN(OpenGLCanvas::OnRightDown)
	
	//MENU EVENT
	
	//not working, event won't trigger
	// EVT_MENU(POPUP_PROPERTIES, OpenGLCanvas::OnContextPptes)
	// EVT_MENU(POPUP_DELETE, OpenGLCanvas::OnContextSuppr)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxGLCanvas(parent, id, pos, size, style, name){
	this->ResetConstructTri();
}
OpenGLCanvas::~OpenGLCanvas(void){

}

void OpenGLCanvas::Refresh(){
	this->Draw();
	SwapBuffers();
}

void OpenGLCanvas::ResetConstructTri(){
	this->construct_tri = new Triangle();
	step = 0;
}

Triangle* OpenGLCanvas::CopyConstructTri(){
	Triangle* copy = new Triangle();
	//copie des points
	copy->p1.x = this->construct_tri->p1.x;
	copy->p1.y = this->construct_tri->p1.y;
	copy->p2.x = this->construct_tri->p2.x;
	copy->p2.y = this->construct_tri->p2.y;
	copy->p3.x = this->construct_tri->p3.x;
	copy->p3.y = this->construct_tri->p3.y;

	//copie de la couleur
	copy->colour = new wxColour(this->construct_tri->colour->Red(), 
		this->construct_tri->colour->Green(),
		this->construct_tri->colour->Blue());

	//copie de l'épaisseur
	copy->thickness = this->construct_tri->thickness;

	return copy;
}

float OpenGLCanvas::ScreenToGLX(int x){
	int w;
	int h;
	GetClientSize(&w, &h);
	return -(w/2.) + x;
}

float OpenGLCanvas::ScreenToGLY(int y){
	int w;
	int h;
	GetClientSize(&w, &h);
	return h/2. - y;
}

void OpenGLCanvas::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);
	SetCurrent();
	this->Refresh();
}
void OpenGLCanvas::OnSize(wxSizeEvent &event){
	wxGLCanvas::OnSize(event);
	//get client size
	int w;
	int h;
	GetClientSize(&w, &h);
}
void OpenGLCanvas::OnEraseBackground(wxEraseEvent& event){

}
void OpenGLCanvas::Draw(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w;
	int h;
	GetClientSize(&w, &h);
	glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(.3f, .4f, .6f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//get mainframe
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	std::vector<Triangle *> triangles = frame->GetTabTri();

	//draw triangles
	for(int i=0; i < frame->GetNumTri(); i++)
		this->DrawTriangle(triangles[i]);

	//if draw button not pressed stop here
	if(!frame->IsDrawing())
		return;

	switch(this->step){
		case 1:
			glColor3f(0, 0, 0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(frame->GetEpaisseurTraitCourante());
			glBegin(GL_LINES);
				glVertex2f(construct_tri->p1.x, construct_tri->p1.y);
				glVertex2f(construct_tri->p2.x, construct_tri->p2.y);		
			glEnd();
			break;
		case 2:
			//set correct values
			this->construct_tri->thickness = frame->GetEpaisseurTraitCourante();
			this->construct_tri->colour = frame->GetCouleurCourante();
			this->DrawTriangle(this->construct_tri);
			break;
	}
}

void OpenGLCanvas::DrawTriangle(Triangle* triangle){
	glColor3f(triangle->colour->Red()/255., 
		triangle->colour->Green()/255.,
		triangle->colour->Blue()/255.);
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
		glVertex2f(triangle->p1.x, triangle->p1.y);
		glVertex2f(triangle->p2.x, triangle->p2.y);
		glVertex2f(triangle->p3.x, triangle->p3.y);
	glEnd();

	//Draw borders
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(triangle->thickness);
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(triangle->p1.x, triangle->p1.y);
		glVertex2f(triangle->p2.x, triangle->p2.y);
		glVertex2f(triangle->p3.x, triangle->p3.y);
	glEnd();
}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& event){
	//get mainframe
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	//if draw button not pressed stop here
	if(!frame->IsDrawing()){
		return;
	}

	switch(this->step){
		case 1:
			this->construct_tri->p2.x = this->ScreenToGLX(event.GetX());
			this->construct_tri->p2.y = this->ScreenToGLY(event.GetY());
			break;
		case 2:
			this->construct_tri->p3.x = this->ScreenToGLX(event.GetX());
			this->construct_tri->p3.y = this->ScreenToGLY(event.GetY());
			break;
	}

	this->Refresh();
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& event){
	//get mainframe
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	//if draw button not pressed stop here
	if(!frame->IsDrawing()){
		return;
	}

	switch(this->step){
		case 0:
			//set point 1
			this->construct_tri->p1.x = this->ScreenToGLX(event.GetX());
			this->construct_tri->p1.y = this->ScreenToGLY(event.GetY());
			step++;
			break;
		case 1:
			// //set point 2
			this->construct_tri->p2.x = this->ScreenToGLX(event.GetX());
			this->construct_tri->p2.y = this->ScreenToGLY(event.GetY());
			step++;
			break;
		case 2:
			this->construct_tri->p3.x = this->ScreenToGLX(event.GetX());
			this->construct_tri->p3.y = this->ScreenToGLY(event.GetY());
			Triangle* copy;
			copy = this->CopyConstructTri();
			frame->AddTriangle(copy);
			this->ResetConstructTri();
			break;
		case 3:
			break;
	}
	this->Refresh();
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& event){

}

void OpenGLCanvas::OnRightDown(wxMouseEvent& event){
	int x = event.GetX();
	int y = event.GetY();
	this->selected_tri = IsInATriangle(ScreenToGLX(x), ScreenToGLY(y));
	if(this->selected_tri > -1)
		this->CreateInTriangleMenu(x, y);
	else
		this->CreateDefaultMenu(x, y);
}

int OpenGLCanvas::IsInATriangle(int x, int y){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	std::vector<Triangle *> triangles = frame->GetTabTri();

	for(int i=frame->GetNumTri()-1; i >= 0; i--)
		if(triangles[i]->IsPointInTriangle(x, y))
			return i;
	return -1;
}

void OpenGLCanvas::CreateInTriangleMenu(int x, int y){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	wxMenu* popup = new wxMenu();
	popup->Append(POPUP_PROPERTIES, wxT("Propriétés de ce triangle"));
	popup->Append(POPUP_DELETE, wxT("Supprimer ce triangle"));
	frame->PopupMenu(popup, x, y);
}

void OpenGLCanvas::CreateDefaultMenu(int x, int y){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());

	wxMenu* popup = new wxMenu();
	
	//menu de premier ordre
	wxMenu* file_popup = new wxMenu();
	wxMenu* triangle_popup = new wxMenu();
	wxMenu* val_courante_popup = new wxMenu();

	//menu de deuxieme ordre
	//fichier
	file_popup->Append(MENU_OPEN, wxT("Ouvrir fichier"));
	file_popup->Append(MENU_SAVE, wxT("Sauvegarder fichier"));
	//triangle gestion
	triangle_popup->Append(MENU_TRIANGLE, "Gestion des triangles");
	//Griser si necessaire
	if(frame->GetNumTri() < 1)
		triangle_popup->Enable(MENU_TRIANGLE, false);
	//valeurs courantes
	val_courante_popup->Append(MENU_COLOR, "Couleurs courantes");
	val_courante_popup->Append(MENU_THICKNESS, "Epaisseur courante");

	popup->Append(POPUP_SUB_FILE, wxT("Fichier"), file_popup);
	popup->Append(POPUP_SUB_TRIANGLE, wxT("Gestion"), triangle_popup);
	popup->Append(POPUP_SUB_VAL_COURANTE, wxT("Valeurs courantes"), val_courante_popup);

	frame->PopupMenu(popup, x, y);
}

void OpenGLCanvas::OnContextPptes(wxCommandEvent& event){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	Triangle* tri = frame->GetTabTri()[this->selected_tri];
	PropertiesDialog pdlg(this, -1, wxT("Proprietes"), tri);
	//set name
	wxString str;
	str << "triangle" << this->selected_tri+1;
	pdlg.SetTextctrlIDTriangle(str);
	//set thickness
	pdlg.GetThicknessTextctrl()->SetValue(tri->thickness);
	//set color
	if(tri->colour->Red() == 255)
		pdlg.GetColorRadiobox()->SetSelection(0);
	else if(tri->colour->Blue() == 255)
		pdlg.GetColorRadiobox()->SetSelection(2);
	//default color is green
	else
		pdlg.GetColorRadiobox()->SetSelection(1);
	pdlg.ShowModal();
}

void OpenGLCanvas::OnContextSuppr(wxCommandEvent& event){
	CMainFrame* frame = dynamic_cast<CMainFrame*>(this->GetParent());
	frame->DeleteTriangle(this->selected_tri);

	frame->RefreshCanvas();
}