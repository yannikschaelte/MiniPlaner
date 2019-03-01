/* 
 * File:   SettingsDialog.h
 * Author: Yannik
 *
 * Created on September 30, 2015, 4:14 PM
 */

#ifndef EXPORTLAYOUTDIALOG_H
#define	EXPORTLAYOUTDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "ExportLayout.h"

class ExportLayoutDialog : public wxDialog {
public:
	ExportLayoutDialog(wxWindow* parent, ExportLayout* _layout);
private:
	ExportLayout* layout;
	
	wxFlexGridSizer* sizer_config;
	wxTextCtrl* tc_title;
	wxCheckBox* cb_showDienste;
	wxChoice* ch_minis;
	wxSpinCtrl* sp_minis;
	wxChoice* ch_basics;
	wxChoice* ch_namen;
	
	wxButton* bt_ok;
	wxButton* bt_cancel;
	
	DECLARE_EVENT_TABLE();
	void onMinis(wxCommandEvent&);
	void onOk(wxCommandEvent&);
	void onCancel(wxCommandEvent&);
};

#endif	/* EXPORTLAYOUTDIALOG_H */

