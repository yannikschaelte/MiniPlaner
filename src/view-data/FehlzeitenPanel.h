/* 
 * File:   FehlzeitenPanel.h
 * Author: Yannik
 *
 * Created on August 23, 2015, 12:59 PM
 */

#ifndef FEHLZEITENPANEL_H
#define	FEHLZEITENPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
class App;

class FehlzeitenPanel : public wxPanel {
public:
	FehlzeitenPanel(wxWindow* parent, App* _app);
	void notifyFehlzeiten(int index = -1);
private:
	App* app;
	wxListView* lv_fehlzeiten;
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

#endif	/* FEHLZEITENPANEL_H */