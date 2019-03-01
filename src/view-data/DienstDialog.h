/* 
 * File:   DienstDialog.h
 * Author: Yannik
 *
 * Created on August 19, 2015, 1:25 PM
 */

#ifndef DIENSTDIALOG_H
#define	DIENSTDIALOG_H

#include <wx/wx.h>
class App;

class DienstDialog : public wxDialog {
public:
	DienstDialog(wxWindow* parent, App* _app);
	DienstDialog(wxWindow* parent, App* _app, int _index);
private:
	App* app;
	bool edt;
	int index;
	wxStaticText* st_name;
	wxTextCtrl* tc_name;
	wxButton* bt_ok;
	wxButton* bt_cancel;
	void initComponents();
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* DIENSTDIALOG_H */

