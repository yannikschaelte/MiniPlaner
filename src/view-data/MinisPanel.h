/* 
 * File:   MinisPanel.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 5:37 PM
 */

#ifndef MINISPANEL_H
#define	MINISPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../R.h"
#include "../model-data/Messdiener.h"
#include <vector>
class App;

class MinisPanel : public wxPanel {
public:
	MinisPanel(wxWindow* parent, App* _app);
	void notifyMinis(int index = -1);
private:
	App* app;
	
	std::vector<Messdiener*> shownMinis;
	int selectedCol = -1;
	void sortByString(bool inc, wxString Messdiener::* var);
	
	wxBoxSizer* sizer;
	wxBoxSizer* sizer_r;
	wxListView* lc_minis;
	wxButton* bt_add;
	wxButton* bt_del;
	wxButton* bt_edt;
	wxButton* bt_import;
	wxButton* bt_export;
	wxButton* bt_extras;
	
	DECLARE_EVENT_TABLE();
	void drawMinis(int index = -1);
	void onBtAdd(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
	//void onColClick(wxListEvent& evt);
	void onBtExport(wxCommandEvent&);
	void onBtImport(wxCommandEvent&);
	void onBtExtras(wxCommandEvent&);
};

#endif	/* MINISPANEL_H */

