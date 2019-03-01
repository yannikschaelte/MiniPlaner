/* 
 * File:   EinzelterminImportDialog.h
 * Author: Yannik
 *
 * Created on August 29, 2016, 9:42 PM
 */

#ifndef EINZELTERMINIMPORTDIALOG_H
#define	EINZELTERMINIMPORTDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <vector>
#include "../model-data/Einzeltermin.h"

class EinzelterminImportDialog : public wxDialog {
public:
	EinzelterminImportDialog(wxWindow* parent, std::vector<Einzeltermin*>* _list_einzel, bool* _edt, std::vector<Dienst*>* _list_dienst);
private:
	std::vector<Einzeltermin*>* list_einzel;
	bool* edt;
	std::vector<Dienst*>* list_dienst;

	std::vector<Einzeltermin> tmp_list;

	wxButton* bt_file;
	wxRadioButton* rb_semicolon;
	wxRadioButton* rb_comma;
	wxRadioButton* rb_tab;
	wxRadioButton* rb_space;
	wxRadioButton* rb_other;
	wxTextCtrl* tc_sep;
	wxChoice* ch_dienst;
	wxSpinCtrl* sp_anzahl;
	wxListCtrl* lc_termine;
	wxButton* bt_del;
	wxButton* bt_ok;
	wxButton* bt_cancel;

	void notifyTermine();
	DECLARE_EVENT_TABLE();
	void onBtFile(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* EINZELTERMINIMPORTDIALOG_H */

