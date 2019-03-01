/* 
 * File:   MGruppeDialog.h
 * Author: Yannik
 *
 * Created on August 13, 2015, 7:08 PM
 */

#ifndef MGRUPPEDIALOG_H
#define	MGRUPPEDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../model-data/Messdiener.h"
#include "../model-data/MGruppe.h"
#include <vector>
#include <utility>
class App;

class MGruppeDialog : public wxDialog {
public:
	MGruppeDialog(wxWindow* parent, App* _app);
	MGruppeDialog(wxWindow* parent, App* _app, int _index);
private:
	App* app;
	bool edt;
	int index;
	std::vector<Messdiener*> list_gruppe;
	std::vector<Messdiener*> list_rest;
	wxStaticText* st_modus;
	wxChoice* ch_modus;
	wxStaticText* st_gruppe;
	wxStaticText* st_rest;
	wxListView* lv_gruppe;
	wxListView* lv_rest;
	wxButton* bt_togroup;
	wxButton* bt_torest;
	wxButton* bt_ok;
	wxButton* bt_cancel;
	void initComponents();
	void initGruppe();
	void initRest();
	void drawGruppe();
	void drawRest();
	DECLARE_EVENT_TABLE();
	void onBtToGruppe(wxCommandEvent&);
	void onBtToRest(wxCommandEvent&);
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* MGRUPPEDIALOG_H */

