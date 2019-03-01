/* 
 * File:   FehlzeitDialog.h
 * Author: Yannik
 *
 * Created on August 23, 2015, 5:08 PM
 */

#ifndef FEHLZEITDIALOG_H
#define	FEHLZEITDIALOG_H

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
class App;

class FehlzeitDialog : public wxDialog {
public:
	FehlzeitDialog(wxWindow* parent, App* _app);
	FehlzeitDialog(wxWindow* parent, App* _app, int _index);
private:
	App* app;
	bool edt;
	int index;

	wxFlexGridSizer* gridsizer;
	wxStaticText* st_mini;
	wxChoice* ch_mini;
	wxStaticText* st_modus;
	wxChoice* ch_modus;
	wxStaticText* st_termin;
	wxChoice* ch_termin;
	wxStaticText* st_wochentag;
	wxChoice* ch_wochentag;
	wxStaticText* st_datum_beginn;
	wxDatePickerCtrl* dc_beginn;
	wxStaticText* st_beginn_wday;
	wxStaticText* st_datum_ende;
	wxDatePickerCtrl* dc_ende;
	wxStaticText* st_ende_wday;
	wxStaticText* st_zeit_beginn;
	wxTextCtrl* tc_beginn;
	wxStaticText* st_zeit_ende;
	wxTextCtrl* tc_ende;

	wxButton* bt_ok;
	wxButton* bt_cancel;

	void initComponents();
	void setModusZeitraum();
	void setModusWochentag();
	void setModusTermin();
	DECLARE_EVENT_TABLE();
	void onChModus(wxCommandEvent&);
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onDateBeginnChanged(wxDateEvent&);
	void onDateEndeChanged(wxDateEvent&);
};

#endif	/* FEHLZEITDIALOG_H */

