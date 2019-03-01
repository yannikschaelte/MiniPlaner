/* 
 * File:   PTerminDialog.h
 * Author: Yannik
 *
 * Created on September 7, 2015, 4:34 PM
 */

#ifndef PTERMINDIALOG_H
#define	PTERMINDIALOG_H

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/listctrl.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "../model-plan/PTermin.h"

class PTerminDialog : public wxDialog {
public:
	PTerminDialog(wxWindow* parent, 
			PTermin* _termin, 
			std::vector<PTermin*>* _global_termine,//for correct mini nums
			std::vector<Dienst*>* _global_dienste, 
			std::vector<PMessdiener*>* _global_minis, 
			bool* _edt);
private:
	PTermin* termin;
	
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis;
	std::vector<std::pair<Dienst*, int> > list_dienst_num;
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis_possible; //in total
	
	std::vector<PTermin*>* global_termine;
	std::vector<Dienst*>* global_dienste;
	std::vector<PMessdiener*>* global_minis;
	bool* edt;

	wxStaticText* st_name;
	wxTextCtrl* tc_name;
	wxStaticText* st_ort;
	wxTextCtrl* tc_ort;
	wxStaticText* st_datum;
	wxDatePickerCtrl* dc_datum;
	wxStaticText* st_datum_wday;
	wxStaticText* st_zeit;
	wxTextCtrl* tc_zeit;
	wxStaticText* st_dienste;
	wxListView* lv_dienste;
	wxButton* bt_add_dienst;
	wxButton* bt_edt_dienst;
	wxButton* bt_del_dienst;
	wxStaticText* st_bem;
	wxTextCtrl* tc_bem;

	wxButton* bt_ok;
	wxButton* bt_cancel;

	void notifyDienste();
	void initComponents();
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onBtAddDienst(wxCommandEvent&);
	void onBtEdtDienst(wxCommandEvent&);
	void onBtDelDienst(wxCommandEvent&);
	void onLIDienstActivated(wxListEvent& evt);
	void onDateChanged(wxDateEvent&);
};

#endif	/* PTERMINDIALOG_H */

