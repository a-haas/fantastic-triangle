#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

#include <wx/glcanvas.h>

#include "triangle.h"

class OpenGLCanvas: public wxGLCanvas {
	public:
		OpenGLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,const wxSize& size = wxDefaultSize,long style = 0, const wxString& name = wxGLCanvasName);
		~OpenGLCanvas(void);
		void Refresh();
		void ResetConstructTri();
		void OnContextPptes(wxCommandEvent& event);
		void OnContextSuppr(wxCommandEvent& event);
	private:
		DECLARE_EVENT_TABLE();

		void OnPaint(wxPaintEvent& event);
		void OnSize(wxSizeEvent &event);
		void OnEraseBackground(wxEraseEvent& event);
		void Draw();
		void OnMouseMove(wxMouseEvent& event);
		void OnLeftUp(wxMouseEvent& event);
		void OnLeftDown(wxMouseEvent& event);
		void OnRightDown(wxMouseEvent& event);
		// void OnContextPptes(wxCommandEvent& event);
		// void OnContextSuppr(wxCommandEvent& event);

		void CreateDefaultMenu(int x, int y);
		void CreateInTriangleMenu(int x, int y);
		int IsInATriangle(int x, int y);

		Triangle* CopyConstructTri();
		void DrawTriangle(Triangle* triangle);
		float ScreenToGLX(int x);
		float ScreenToGLY(int y);

		Triangle* construct_tri;
		int step;
		int selected_tri;
};
#endif