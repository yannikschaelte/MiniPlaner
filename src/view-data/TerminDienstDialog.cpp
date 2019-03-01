/* 
 * File:   TerminDienstDialog.cpp
 * Author: Yannik
 * 
 * Created on August 21, 2015, 10:17 AM
 */

#include "TerminDienstDialog.h"

TerminDienstDialog::TerminDienstDialog(wxWindow* parent, std::vector< std::pair<Dienst*, int> >* _dienste, std::vector<Dienst*>* _missing_dienste)
: wxDialog(parent, R::ID_ANY, R::TERMIN_DIENST_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	edt = false;
	dienste = _dienste;
	missing_dienste = _missing_dienste;
	initComponents();
}

TerminDienstDialog::TerminDienstDialog(wxWindow* parent, std::vector< std::pair<Dienst*, int> >* _dienste, std::vector<Dienst*>* _missing_dienste, int _index)
: wxDialog(parent, R::ID_ANY, R::TERMIN_DIENST_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	edt = true;
	index = _index;
	dienste = _dienste;
	missing_dienste = _missing_dienste;
	initComponents();
	sp_anzahl->SetValue(dienste->at(index).second);
}

void TerminDienstDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridsizer = new wxFlexGridSizer(2, 2, 0, 0);

	st_dienst = new wxStaticText(this, R::ID_ANY, R::DIENST);
	gridsizer->Add(st_dienst, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num = missing_dienste->size();
	wxString dienste_s[num];
	for (int i = 0; i < num; i++) {
		dienste_s[i] = missing_dienste->at(i)->name;
	}
	ch_dienst = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, num, dienste_s);
	ch_dienst->SetSelection(0);//seems to work with empty lists
	gridsizer->Add(ch_dienst, 1, wxEXPAND | wxALL, 2);
	st_anzahl = new wxStaticText(this, R::ID_ANY, R::ANZAHL);
	gridsizer->Add(st_anzahl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	sp_anzahl = new wxSpinCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000000000, 1);
	gridsizer->Add(sp_anzahl, 1, wxEXPAND | wxALL, 2);

	sizer->Add(gridsizer, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

BEGIN_EVENT_TABLE(TerminDienstDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, TerminDienstDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, TerminDienstDialog::onBtCancel)
END_EVENT_TABLE()

void TerminDienstDialog::onBtOK(wxCommandEvent&) {
	int dienst_i = ch_dienst->GetSelection();
	if (dienst_i == wxNOT_FOUND) {
		wxMessageDialog dialog(this, R::MSG_DIENST_SEL_ERR);
		dialog.ShowModal();
		return;
	}
	if (edt) {
		dienste->at(index).first = missing_dienste->at(dienst_i);
		dienste->at(index).second = sp_anzahl->GetValue();
		Close(true);
	} else {
		dienste->push_back(std::make_pair(missing_dienste->at(dienst_i), sp_anzahl->GetValue()));
		Close(true);
	}
}

void TerminDienstDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}