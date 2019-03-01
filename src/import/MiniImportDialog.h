/* 
 * File:   MiniImportDialog.h
 * Author: Yannik
 *
 * Created on October 8, 2015, 6:28 PM
 */

#ifndef MINIIMPORTDIALOG_H
#define	MINIIMPORTDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "../model-data/Messdiener.h"

class MiniImportDialog : public wxDialog {
public:
	MiniImportDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini, bool* _edt);
private:
	std::vector<Messdiener*>* list_mini;
	bool* edt;

	std::vector<Messdiener> tmp_list;

	wxButton* bt_file;
	wxRadioButton* rb_semicolon;
	wxRadioButton* rb_comma;
	wxRadioButton* rb_tab;
	wxRadioButton* rb_space;
	wxRadioButton* rb_other;
	wxTextCtrl* tc_sep;
	wxListCtrl* lc_minis;
	wxButton* bt_del;
	wxButton* bt_ok;
	wxButton* bt_cancel;

	void notifyMinis();
	DECLARE_EVENT_TABLE();
	void onBtFile(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* MINIIMPORTDIALOG_H */

