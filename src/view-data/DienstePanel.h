/* 
 * File:   DienstePanel.h
 * Author: Yannik
 *
 * Created on August 19, 2015, 11:37 AM
 */

#ifndef DIENSTEPANEL_H
#define	DIENSTEPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
class App;

class DienstePanel : public wxPanel {
public:
	DienstePanel(wxWindow* parent, App* _app);
	void notifyDienste(int index = -1);
private:
	App* app;
	wxListView* lc_dienste;
	wxButton* bt_add;
	wxButton* bt_edt;
	wxButton* bt_del;
	DECLARE_EVENT_TABLE();
	void onBtAdd(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
};

#endif	/* DIENSTEPANEL_H */

