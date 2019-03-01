/* 
 * File:   CloseDialog.h
 * Author: Yannik
 *
 * Created on October 2, 2015, 3:31 PM
 */

#ifndef CLOSEDIALOG_H
#define	CLOSEDIALOG_H

#include <wx/wx.h>

class CloseDialog : public wxDialog {
public:
	CloseDialog(wxWindow* parent, bool* _save, bool* _close);
private:
	bool* save;
	bool* close;
	
	wxButton* bt_yes;
	wxButton* bt_no;
	
	DECLARE_EVENT_TABLE();
	void onBtYes(wxCommandEvent&);
	void onBtNo(wxCommandEvent&);
};

#endif	/* CLOSEDIALOG_H */