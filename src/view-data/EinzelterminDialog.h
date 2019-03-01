/* 
 * File:   EinzelterminDialog.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 6:44 PM
 */

#ifndef EINZELTERMINDIALOG_H
#define	EINZELTERMINDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <vector>
#include "../model-data/Einzeltermin.h"
class App;

class EinzelterminDialog : public wxDialog {
public:
	EinzelterminDialog(wxWindow* parent, App* _app);
	EinzelterminDialog(wxWindow* parent, App* _app, int _index);
	std::vector< std::pair<Dienst*, int> > dienste;
private:
	App* app;
	bool edt;
	int index;
	wxStaticText* st_name;
	wxStaticText* st_ort;
	wxStaticText* st_datum;
	wxStaticText* st_zeit_beginn;
	wxStaticText* st_dienste;
	wxStaticText* st_bem;
	
	wxTextCtrl* tc_name;
	wxComboBox* tc_ort;
	wxDatePickerCtrl* dc_datum;
	wxStaticText* st_datum_wday;
	wxTextCtrl* tc_zeit_beginn;
	wxListView* lv_dienste;
	wxButton* bt_add_dienst;
	wxButton* bt_edt_dienst;
	wxButton* bt_del_dienst;
	wxTextCtrl* tc_bem;
	
	wxButton* bt_ok;
	wxButton* bt_cancel;
	
	void notifyDienste();
	void initComponents();
	
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onBtAddDienst(wxCommandEvent&);
	void onBtEdtDienst(wxCommandEvent&);
	void onBtDelDienst(wxCommandEvent&);
	void onLIDienstActivated(wxListEvent& evt);
	void onDateChanged(wxDateEvent&);
};

#endif	/* EINZELTERMINDIALOG_H */