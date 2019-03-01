/* 
 * File:   PTerminDienstDialog.h
 * Author: Yannik
 *
 * Created on March 22, 2016, 1:03 PM
 */

#ifndef PTERMINDIENSTDIALOG_H
#define	PTERMINDIENSTDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "../R.h"
#include "../model-plan/PMessdiener.h"

/**
 * Pass list of missing services. Case edt: service to edit at(0).
 */
class PTerminDienstDialog : public wxDialog {
public:
	PTerminDienstDialog(wxWindow* parent,
			std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis,
			std::vector<std::pair<Dienst*, int> >* _list_dienst_num,
			std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis_possible, //in total
			std::vector<Dienst*>* _missing_dienste,
			std::vector<PMessdiener*>* _global_minis);
	PTerminDienstDialog(wxWindow* parent,
			std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis,
			std::vector<std::pair<Dienst*, int> >* _list_dienst_num,
			std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis_possible, //in total
			int _index,
			std::vector<PMessdiener*>* _global_minis);
private:
	bool edt;
	int index;
	std::vector<Dienst*> missing_dienste;
	
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* list_dienst_minis;
	std::vector<std::pair<Dienst*, int> >* list_dienst_num;
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* list_dienst_minis_possible; //in total	

	std::vector<PMessdiener*>* global_minis;
	wxStaticText* st_dienst;
	wxStaticText* st_anzahl;
	wxChoice* ch_dienst;
	wxSpinCtrl* sp_anzahl;
	wxButton* bt_ok;
	wxButton* bt_cancel;
	void initComponents();
	DECLARE_EVENT_TABLE();
	void onBtOK(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* PTERMINDIENSTDIALOG_H */

