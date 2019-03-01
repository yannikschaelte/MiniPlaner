/* 
 * File:   PlaenePanel.h
 * Author: Yannik
 *
 * Created on August 25, 2015, 12:40 PM
 */

#ifndef PLAENEPANEL_H
#define	PLAENEPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
class App;

class PlaenePanel : public wxPanel {
public:
	PlaenePanel(wxWindow* parent, App* _app);
	void notifyPlaene(int index = -1);
private:
	App* app;
	wxBoxSizer* sizer;
	wxBoxSizer* sizer_r;
	wxListView* lv_plaene;
	wxButton* bt_add;
	wxButton* bt_edt;
	wxButton* bt_del;
	wxButton* bt_extras;
	DECLARE_EVENT_TABLE();
	void onBtAdd(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
	void onBtExtras(wxCommandEvent&);
};

#endif	/* PLAENEPANEL_H */