/* 
 * File:   TerminePanel.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 5:37 PM
 */

#ifndef TERMINEPANEL_H
#define	TERMINEPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../R.h"
class App;

class TerminePanel : public wxPanel {
public:
	TerminePanel(wxWindow* parent, App* _app);
	void notifyEinzeltermine(int index = -1);
	void notifySerientermine(int index = -1);
private:
	App* app;
	
	wxStaticText* st_einzel;
	wxStaticText* st_serie;
	wxListView* lc_einzel;
	wxListView* lc_serie;
	wxButton* bt_einzel_add;
	wxButton* bt_einzel_del;
	wxButton* bt_einzel_edt;
	wxButton* bt_einzel_import;
	wxButton* bt_serie_add;
	wxButton* bt_serie_del;
	wxButton* bt_serie_edt;
	wxListItem lc_einzel_cols[R::TEINZEL_NUM + 1];
	wxListItem lc_serie_cols[R::TSERIE_NUM + 1];
	DECLARE_EVENT_TABLE();
	void onBtEinAdd(wxCommandEvent&);
	void onBtEinDel(wxCommandEvent&);
	void onBtEinEdt(wxCommandEvent&);
	void onBtEinImport(wxCommandEvent&);
	void onBtSerAdd(wxCommandEvent&);
	void onBtSerDel(wxCommandEvent&);
	void onBtSerEdt(wxCommandEvent&);
	void onLIEinActivated(wxListEvent& evt);
	void onLISerActivated(wxListEvent& evt);
	void onLIEinKey(wxListEvent& evt);
	void onLISerKey(wxListEvent& evt);
};

#endif	/* TERMINEPANEL_H */

