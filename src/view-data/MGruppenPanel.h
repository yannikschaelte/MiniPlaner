/* 
 * File:   MGruppenPanel.h
 * Author: Yannik
 *
 * Created on August 13, 2015, 11:44 AM
 */

#ifndef MGRUPPENPANEL_H
#define	MGRUPPENPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../model-data/MGruppe.h"
class App;

class MGruppenPanel : public wxPanel {
public:
	MGruppenPanel(wxWindow* parent, App* _app);
	void notifyMGruppen(int index = -1);
private:
	App* app;
	wxListView* lv_gruppen;
	wxButton* bt_add;
	wxButton* bt_del;
	wxButton* bt_edt;
	DECLARE_EVENT_TABLE();
	void onBtAdd(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
};

#endif	/* MGRUPPENPANEL_H */