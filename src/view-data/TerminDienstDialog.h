/* 
 * File:   TerminDienstDialog.h
 * Author: Yannik
 *
 * Created on August 21, 2015, 10:17 AM
 */

#ifndef TERMINDIENSTDIALOG_H
#define	TERMINDIENSTDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "../R.h"

/**
 * Pass list of missing services. Case edt: service to edit at(0).
 */
class TerminDienstDialog : public wxDialog {
public:
	TerminDienstDialog(wxWindow* parent, std::vector< std::pair<Dienst*, int> >* _dienste, std::vector<Dienst*>* _missing_dienste);
	TerminDienstDialog(wxWindow* parent, std::vector< std::pair<Dienst*, int> >* _dienste, std::vector<Dienst*>* _missing_dienste, int _index);
private:
	bool edt;
	int index;
	std::vector< std::pair<Dienst*, int> >* dienste;
	std::vector<Dienst*>* missing_dienste;
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


#endif	/* TERMINDIENSTDIALOG_H */

