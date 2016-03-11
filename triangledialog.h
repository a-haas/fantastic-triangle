#ifndef __TRIANGLEDIALOG_H__
#define __TRIANGLEDIALOG_H__

#include "wx/wx.h"

class TriangleDialog: public wxDialog{
	public:
		TriangleDialog(wxWindow *parent, wxWindowID id, const wxString &title);
		wxListBox* GetListbox();
	private:
		void OnProperties(wxCommandEvent& event);
		void OnDelete(wxCommandEvent& event);
		wxListBox *triangle_listbox;
		DECLARE_EVENT_TABLE()
};

#endif