/* 
 * File:   PTerminDienstDialog.cpp
 * Author: Yannik
 * 
 * Created on March 22, 2016, 1:03 PM
 */

#include "PTerminDienstDialog.h"
#include <algorithm>

PTerminDienstDialog::PTerminDienstDialog(wxWindow* parent,
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis,
		std::vector<std::pair<Dienst*, int> >* _list_dienst_num,
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis_possible, //in total
		std::vector<Dienst*>* _missing_dienste,
		std::vector<PMessdiener*>* _global_minis)
: wxDialog(parent, R::ID_ANY, R::TERMIN_DIENST_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	edt = false;
	missing_dienste = *_missing_dienste;
	list_dienst_minis = _list_dienst_minis;
	list_dienst_num = _list_dienst_num;
	list_dienst_minis_possible = _list_dienst_minis_possible;
	global_minis = _global_minis;
	initComponents();
}

PTerminDienstDialog::PTerminDienstDialog(wxWindow* parent,
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis,
		std::vector<std::pair<Dienst*, int> >* _list_dienst_num,
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >* _list_dienst_minis_possible, //in total
		int _index,
		std::vector<PMessdiener*>* _global_minis)
: wxDialog(parent, R::ID_ANY, R::TERMIN_DIENST_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	edt = true;
	index = _index;
	missing_dienste.push_back(_list_dienst_num->at(index).first);
	list_dienst_minis = _list_dienst_minis;
	list_dienst_num = _list_dienst_num;
	list_dienst_minis_possible = _list_dienst_minis_possible;
	global_minis = _global_minis;
	initComponents();
	sp_anzahl->SetValue(list_dienst_num->at(index).second);
	ch_dienst->Enable(false);
}

void PTerminDienstDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridsizer = new wxFlexGridSizer(2, 2, 0, 0);

	st_dienst = new wxStaticText(this, R::ID_ANY, R::DIENST);
	gridsizer->Add(st_dienst, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num = missing_dienste.size();
	wxString dienste_s[num];
	for (int i = 0; i < num; i++) {
		dienste_s[i] = missing_dienste.at(i)->name;
	}
	ch_dienst = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, num, dienste_s);
	ch_dienst->SetSelection(0); //seems to work with empty lists
	gridsizer->Add(ch_dienst, 1, wxEXPAND | wxALL, 2);
	st_anzahl = new wxStaticText(this, R::ID_ANY, R::ANZAHL);
	gridsizer->Add(st_anzahl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	sp_anzahl = new wxSpinCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000000000, 1);
	gridsizer->Add(sp_anzahl, 1, wxEXPAND | wxALL, 2);

	sizer->Add(gridsizer, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

BEGIN_EVENT_TABLE(PTerminDienstDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, PTerminDienstDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, PTerminDienstDialog::onBtCancel)
END_EVENT_TABLE()

void PTerminDienstDialog::onBtOK(wxCommandEvent&) {
	int dienst_i = ch_dienst->GetSelection();
	if (dienst_i == wxNOT_FOUND) {
		wxMessageDialog dialog(this, R::MSG_DIENST_SEL_ERR);
		dialog.ShowModal();
		return;
	}
	int num_now = sp_anzahl->GetValue();
	if (edt) {
		int num_bef = list_dienst_num->at(index).second;
		list_dienst_num->at(index).second = num_now;
		std::vector<PMessdiener*>* list_minis = &list_dienst_minis->at(index).second;
		for (int i = 0; i < num_now - num_bef; i++) {
			list_minis->push_back(NULL);
		}
		for (int i = 0; i < num_bef - num_now; i++) {
			list_minis->erase(list_minis->begin() + num_bef - 1 - i);
		}
	} else {
		Dienst* dienst = missing_dienste.at(dienst_i);
		list_dienst_num->push_back(std::make_pair(dienst, num_now));
		std::vector<PMessdiener*> vec;
		for (int i = 0; i < num_now; i++) {
			vec.push_back(NULL);
		}
		list_dienst_minis->push_back(std::make_pair(dienst, vec));
		vec.clear();
		for (std::vector<PMessdiener*>::iterator iter_m = global_minis->begin(); iter_m != global_minis->end(); iter_m++) {
			if (std::find((**iter_m).dienste.begin(), (**iter_m).dienste.end(), dienst) != (**iter_m).dienste.end()) vec.push_back(*iter_m);
		}
		list_dienst_minis_possible->push_back(std::make_pair(dienst, vec));
	}
	Close(true);
}

void PTerminDienstDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}