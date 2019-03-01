/* 
 * File:   MiniDialog.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 7:36 PM
 */

#ifndef MINIDIALOG_H
#define	MINIDIALOG_H

#include <wx/wx.h>
#include <wx/checklst.h>
#include <wx/datectrl.h>
#include <wx/checkbox.h>
#include "../model-data/Messdiener.h"
class App;

class MiniDialog : public wxDialog {
public:
	MiniDialog(wxWindow* parent, App* _app);
	MiniDialog(wxWindow* parent, App* _app, int _index);
private:
	App* app;
	bool edt;
	int index;

	wxStaticText* st_name;
	wxStaticText* st_vorname;
	wxStaticText* st_geburtstag;
	wxStaticText* st_dienste;
	wxStaticText* st_strasse_nr;
	wxStaticText* st_plz_ort;
	wxStaticText* st_tel;
	wxStaticText* st_mobil;
	wxStaticText* st_email;
	wxStaticText* st_bem;

	wxTextCtrl* tc_name;
	wxTextCtrl* tc_vorname;
	wxCheckListBox* lb_dienste;
	wxCheckBox* cb_geburtstag;
	wxDatePickerCtrl* dc_geburtstag;
	wxTextCtrl* tc_strasse_nr;
	wxComboBox* tc_plz_ort;
	wxTextCtrl* tc_tel;
	wxTextCtrl* tc_mobil;
	wxTextCtrl* tc_email;
	wxTextCtrl* tc_bem;

	wxButton* bt_ok;
	wxButton* bt_cancel;
	void initComponents();
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onCbGeburtstag(wxCommandEvent& event);
};

#endif	/* MINIDIALOG_H */