/* 
 * File:   MiniExtrasDialog.h
 * Author: Yannik
 *
 * Created on February 11, 2016, 9:39 PM
 */

#ifndef MINIEXTRASDIALOG_H
#define	MINIEXTRASDIALOG_H

#include <wx/wx.h>
#include <vector>
#include "../model-data/Messdiener.h"

class MiniExtrasDialog : public wxDialog {
public:
	MiniExtrasDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini);
private:
	std::vector<Messdiener*>* list_mini;
	wxTextCtrl* textbox;
	wxString successString;
	wxString failureString;
	void createEmails();
	void createAddresses();
	DECLARE_EVENT_TABLE();
	void onBtEmail(wxCommandEvent&);
	void onBtAddresses(wxCommandEvent&);	
};

#endif	/* MINIEXTRASDIALOG_H */

