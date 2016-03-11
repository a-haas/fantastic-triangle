
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <vector>

#include "wx/wx.h"
#include <wx/html/helpctrl.h>

#include "openglcanvas.h"
#include "triangle.h"

enum wxEnum{
	MENU_NEW,
	MENU_OPEN,
	MENU_SAVE,
	MENU_QUIT,
	MENU_THICKNESS,
	MENU_COLOR,
	MENU_TRIANGLE,
	MENU_OPEN_HELP,
	MENU_VERSION,
	MENU_TOOLBAR,
	TOOLBAR_TOOLS,
	TOOLBAR_DRAW,
	MAINFRAME_CANVAS,
	POPUP_SUB_FILE,
	POPUP_SUB_TRIANGLE,
	POPUP_SUB_VAL_COURANTE,
	POPUP_PROPERTIES,
	POPUP_DELETE
};

class CMainFrame: public wxFrame {
	public:
		CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		//Getters/Setters
		CMainFrame* GetMainFrame();
		int GetEpaisseurTraitCourante();
		void SetEpaisseurTraitCourante(int val);
		wxColour* GetCouleurCourante();
		void SetCouleurCourante(wxColour* colour);
		bool IsDrawing();
		int GetNumTri();
		void SetNumTri(int n);
		std::vector<Triangle*> GetTabTri();
		void AddTriangle(Triangle* t);
		void DeleteTriangle(int n);
		void CreateMyToolbar();
		void RefreshCanvas();
		wxHtmlHelpController* GetHelp();

	private:
		CMainFrame* m_mainframe;
		wxToolBar *m_toolbar;
		int epaisseurtraitcourante;
		wxColour* couleurcourante;
		bool is_drawing;
		OpenGLCanvas *canvas;
		wxHtmlHelpController* help;
		int num_tri;
		std::vector<Triangle*> tab_tri;

		//Events
		void OnNew(wxCommandEvent& event); 
		void OnClose(wxCommandEvent& event); 
		void OnOpen(wxCommandEvent &event);
		void OnSave(wxCommandEvent &event);
		void OnToolbar(wxCommandEvent& event);
		void OnVersion(wxCommandEvent& event);
		void OnThickness(wxCommandEvent& event);
		void OnTriangle(wxCommandEvent& event);
		void OnColor(wxCommandEvent& event);
		void OnDraw(wxCommandEvent& event);
		void OnHelp(wxCommandEvent& event);

		void OnContextProperties(wxCommandEvent& event);
		void OnContextSuppr(wxCommandEvent& event);

		DECLARE_EVENT_TABLE();


}; //MyFrame

#endif
