#ifndef __PROPERTIESDIALOG_H__
#define __PROPERTIESDIALOG_H__

#include "wx/wx.h"
#include <wx/spinctrl.h>

#include "triangle.h"

class PropertiesDialog: public wxDialog{
public:
		PropertiesDialog(wxWindow *parent, wxWindowID id, const wxString &title, Triangle* t);
		void SetTextctrlIDTriangle(wxString str);
		wxRadioBox* GetColorRadiobox();
		wxSpinCtrl* GetThicknessTextctrl();
	private:
		void OnPropertiesThickness(wxSpinEvent& event);
		void OnPropertiesColor(wxCommandEvent& event);

		Triangle* triangle;

		wxTextCtrl *idTriangle_textctrl;
		wxRadioBox *color_radiobox;
		wxSpinCtrl *thickness_ctrl;
		DECLARE_EVENT_TABLE()
};

#endif