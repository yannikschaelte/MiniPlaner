/* 
 * File:   DeleteDialog.h
 * Author: Yannik
 *
 * Created on October 2, 2015, 4:13 PM
 */

#ifndef DELETEDIALOG_H
#define	DELETEDIALOG_H

#include <wx/wx.h>

class DeleteDialog : public wxDialog {
public:
	DeleteDialog(wxWindow* parent, bool* _del);
private:
	bool* del;

	wxButton* bt_yes;
	wxButton* bt_no;
	DECLARE_EVENT_TABLE();
	void onBtYes(wxCommandEvent&);
	void onBtNo(wxCommandEvent&);
};

#endif	/* DELETEDIALOG_H */

