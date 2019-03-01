/* 
 * File:   TGruppeDialog.h
 * Author: Yannik
 *
 * Created on August 16, 2015, 1:48 PM
 */

#ifndef TGRUPPEDIALOG_H
#define	TGRUPPEDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../model-data/TGruppe.h"
class App;

class TGruppeDialog : public wxDialog {
public:
	TGruppeDialog(wxWindow* parent, App* _app);
	TGruppeDialog(wxWindow* parent, App* _app, int _index);
private:
	App* app;
	bool edt;
	int index;
	std::vector<Serientermin*> list_serie_tgruppe;
	std::vector<Serientermin*> list_serie_rest;
	std::vector<Einzeltermin*> list_einzel_tgruppe;
	std::vector<Einzeltermin*> list_einzel_rest;

	wxStaticText* st_wochentag;
	wxChoice* ch_wochentag;
	wxStaticText* st_tgruppe;
	wxListView* lv_tgruppe;
	wxStaticText* st_rest;
	wxListView* lv_rest;
	wxButton* bt_togroup;
	wxButton* bt_torest;

	wxButton* bt_ok;
	wxButton* bt_cancel;

	void initComponents();
	void setModePeriodic();
	void setModeNonPeriodic();
	void drawGruppe();
	void drawRest();
	DECLARE_EVENT_TABLE();
	void onBtToGruppe(wxCommandEvent&);
	void onBtToRest(wxCommandEvent&);
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* TGRUPPEDIALOG_H */

