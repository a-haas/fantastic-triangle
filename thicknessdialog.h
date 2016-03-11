#ifndef __THICKNESSDIALOG_H__
#define __THICKNESSDIALOG_H__

#include "wx/wx.h"

class ThicknessDialog: public wxDialog{
	public:
		ThicknessDialog(wxWindow *parent, wxWindowID id, const wxString &title);
		wxSlider* GetSlider();
	private:
		wxSlider *slider;
		void OnChange(wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif