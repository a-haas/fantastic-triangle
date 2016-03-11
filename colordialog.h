#ifndef __COLORDIALOG_H__
#define __COLORDIALOG_H__

#include "wx/wx.h"

class ColorDialog: public wxDialog{
	public:
		ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title);
		wxRadioBox* GetColorRadiobox();
	private:
		wxRadioBox *color_radiobox;
		void OnColorChange(wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif