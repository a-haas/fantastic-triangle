#ifndef __VERSIONDIALOG_H__
#define __VERSIONDIALOG_H__

#include "wx/wx.h"

class VersionDialog: public wxDialog{
	public:
		VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
	private:
		DECLARE_EVENT_TABLE()
};

#endif