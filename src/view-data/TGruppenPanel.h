/* 
 * File:   TGruppePanel.h
 * Author: Yannik
 *
 * Created on August 16, 2015, 10:30 AM
 */

#ifndef TGRUPPENPANEL_H
#define	TGRUPPENPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../model-data/TGruppe.h"
#include "../R.h"
class App;

class TGruppenPanel : public wxPanel {
public:
	TGruppenPanel(wxWindow* parent, App* _app);
	void notifyTGruppen(int index = -1);
private:
	App* app;
	wxListView* lv_tgruppen;
	std::vector<int> list_tgruppen_indices;
	wxButton* bt_add;
	wxButton* bt_del;
	wxButton* bt_edt;
	DECLARE_EVENT_TABLE();
	void onBtAdd(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLISelected(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
};

#endif	/* TGRUPPENPANEL_H */