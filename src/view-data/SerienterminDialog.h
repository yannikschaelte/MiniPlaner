/* 
 * File:   SerienterminDialog.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 6:44 PM
 */

#ifndef SERIENTERMINDIALOG_H
#define	SERIENTERMINDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <vector>
#include "../model-data/Serientermin.h"
class App;

class SerienterminDialog : public wxDialog {
public:
	SerienterminDialog(wxWindow* parent, App* _app);
	SerienterminDialog(wxWindow* parent, App* _app, int _index);
	std::vector< std::pair<Dienst*, int> > dienste;
private:
	App* app;
	bool edt;
	int index;
	int modus;

	wxFlexGridSizer* gridsizer;

	wxStaticText* st_name;
	wxStaticText* st_ort;
	wxStaticText* st_dienste;
	wxStaticText* st_zeit_beginn;
	wxStaticText* st_modus;
	wxStaticText* st_wochentag;
	wxStaticText* st_n;
	wxStaticText* st_woche;
	wxStaticText* st_monatstag;
	wxStaticText* st_datum_beginn;
	wxStaticText* st_datum_ende;
	wxStaticText* st_bem;

	wxTextCtrl* tc_name;
	wxComboBox* tc_ort;
	wxListView* lv_dienste;
	wxButton* bt_add_dienst;
	wxButton* bt_edt_dienst;
	wxButton* bt_del_dienst;
	wxTextCtrl* tc_zeit_beginn;
	wxChoice* ch_modus;
	wxChoice* ch_wochentag;
	wxTextCtrl* tc_n;
	wxChoice* ch_woche;
	wxChoice* ch_monatstag;
	wxCheckBox* cb_datum_beginn;
	wxDatePickerCtrl* dc_datum_beginn;
	wxStaticText* st_datum_beginn_wday;
	wxCheckBox* cb_datum_ende;
	wxDatePickerCtrl* dc_datum_ende;
	wxStaticText* st_datum_ende_wday;
	wxTextCtrl* tc_bem;

	wxButton* bt_ok;
	wxButton* bt_cancel;
	void notifyDienste();
	void initComponents();

	void setModusTaeglich();
	void setModusWoechentlich();
	void setModusKW();
	void setModusNWoechentlich();
	void setModusNWochentagImMonat();
	void setModusMonatlich();
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onBtAddDienst(wxCommandEvent&);
	void onBtEdtDienst(wxCommandEvent&);
	void onBtDelDienst(wxCommandEvent&);
	void onLIDienstActivated(wxListEvent& evt);
	void onChModus(wxCommandEvent&);
	void onCbDatumBeginn(wxCommandEvent&);
	void onCbDatumEnde(wxCommandEvent&);
	void onDateBeginnChanged(wxDateEvent&);
	void onDateEndeChanged(wxDateEvent&);
};

#endif	/* SERIENTERMINDIALOG_H */

