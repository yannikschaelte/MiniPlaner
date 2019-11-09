/* 
 * File:   PTerminDialog.cpp
 * Author: Yannik
 * 
 * Created on September 7, 2015, 4:34 PM
 */

#include "PTerminDialog.h"
#include <algorithm>
#include "../R.h"
#include "../Util.h"
#include "../model-plan/PTermin.h"
#include "../view-plan/PTerminDienstDialog.h"
#include "../controller-plan/PlanerController.h"

PTerminDialog::PTerminDialog(wxWindow* parent,
		PTermin* _termin,
		std::vector<PTermin*>* _global_termine,
		std::vector<Dienst*>* _global_dienste,
		std::vector<PMessdiener*>* _global_minis,
		bool* _edt)
: wxDialog(parent, R::ID_ANY, R::TERMIN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	termin = _termin;
	global_termine = _global_termine;
	global_dienste = _global_dienste;
	global_minis = _global_minis;
	edt = _edt;

	list_dienst_minis = termin->list_dienst_minis;
	list_dienst_num = termin->list_dienst_num;
	list_dienst_minis_possible = termin->list_dienst_minis_possible;

	initComponents();
}

void PTerminDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* gridsizer = new wxFlexGridSizer(R::TEINZEL_NUM, 2, 0, 0);

	st_name = new wxStaticText(this, R::ID_ANY, R::NAME);
	gridsizer->Add(st_name, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_name = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_name, 1, wxEXPAND | wxALL, 2);

	st_ort = new wxStaticText(this, R::ID_ANY, R::ORT);
	gridsizer->Add(st_ort, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_ort = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_ort, 1, wxEXPAND | wxALL, 2);

	st_datum = new wxStaticText(this, R::ID_ANY, R::DATUM);
	gridsizer->Add(st_datum, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum = new wxBoxSizer(wxHORIZONTAL);
	dc_datum = new wxDatePickerCtrl(this, R::ID_CH, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	sizer_datum->Add(dc_datum, 1, wxEXPAND | wxALL, 2);
	st_datum_wday = new wxStaticText(this, R::ID_ANY, wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum->Add(st_datum_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum, 1, wxEXPAND | wxALL, 2);

	st_zeit = new wxStaticText(this, R::ID_ANY, R::ZEIT);
	gridsizer->Add(st_zeit, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_zeit = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	tc_zeit->SetHint(wxT("hh:mm"));
	gridsizer->Add(tc_zeit, 1, wxEXPAND | wxALL, 2);

	st_dienste = new wxStaticText(this, R::ID_ANY, R::DIENSTE);
	gridsizer->Add(st_dienste, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_dienste = new wxBoxSizer(wxHORIZONTAL);
	lv_dienste = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[2];
	cols[0].SetText(R::DIENST);
	lv_dienste->InsertColumn(0, cols[0]);
	cols[1].SetText(R::ANZAHL);
	lv_dienste->InsertColumn(1, cols[1]);
	sizer_dienste->Add(lv_dienste, 1, wxEXPAND, 0);
	wxBoxSizer* sizer_dienste_r = new wxBoxSizer(wxVERTICAL);
	bt_add_dienst = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_dienste_r->Add(bt_add_dienst, 0, 0, 0);
	bt_edt_dienst = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_dienste_r->Add(bt_edt_dienst, 0, 0, 0);
	bt_del_dienst = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_dienste_r->Add(bt_del_dienst, 0, 0, 0);
	sizer_dienste->Add(sizer_dienste_r, 0, 0, 0);
	gridsizer->Add(sizer_dienste, 1, wxEXPAND | wxALL, 2);

	st_bem = new wxStaticText(this, R::ID_ANY, R::BEM);
	gridsizer->Add(st_bem, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_bem = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_bem, 1, wxEXPAND | wxALL, 2);

	gridsizer->AddGrowableCol(1, 1);
	gridsizer->AddGrowableRow(4, 1);
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
	if (GetSize().GetWidth() < 260) {
		SetSize(260, -1);
	}

	//always edit
	tc_name->SetValue(termin->name);
	notifyDienste();
	tc_ort->SetValue(termin->ort);
	dc_datum->SetValue(termin->datum);
	tc_zeit->SetValue(termin->zeit_beginn);
	tc_bem->SetValue(termin->bem);
	st_datum_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"));
}

void PTerminDialog::notifyDienste() {
	lv_dienste->DeleteAllItems();
	for (int i = 0; i < (int) list_dienst_num.size(); i++) {
		wxListItem item;
		item.SetId(i);
		lv_dienste->InsertItem(item);
		lv_dienste->SetItem(i, 0, list_dienst_num.at(i).first->name);
		lv_dienste->SetItem(i, 1, wxString::Format(wxT("%i"), list_dienst_num.at(i).second));
	}
	lv_dienste->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_dienste->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(PTerminDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, PTerminDialog::onBtAddDienst)
EVT_BUTTON(R::ID_BT_EDT, PTerminDialog::onBtEdtDienst)
EVT_BUTTON(R::ID_BT_DEL, PTerminDialog::onBtDelDienst)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, PTerminDialog::onLIDienstActivated)
EVT_BUTTON(R::ID_BT_OK, PTerminDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, PTerminDialog::onBtCancel)
EVT_DATE_CHANGED(R::ID_CH, PTerminDialog::onDateChanged)
END_EVENT_TABLE()

void PTerminDialog::onBtAddDienst(wxCommandEvent&) {
	std::vector<Dienst*> missing_dienste;
	for (std::vector<Dienst*>::iterator iter = global_dienste->begin(); iter != global_dienste->end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = list_dienst_num.begin(); iter_t != list_dienst_num.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	PTerminDienstDialog* dialog = new PTerminDienstDialog(this, &list_dienst_minis, &list_dienst_num, &list_dienst_minis_possible, &missing_dienste, global_minis);
	dialog->ShowModal();
	delete dialog;
	notifyDienste();
}

void PTerminDialog::onBtEdtDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		PTerminDienstDialog* dialog = new PTerminDienstDialog(this, &list_dienst_minis, &list_dienst_num, &list_dienst_minis_possible, i, global_minis);
		dialog->ShowModal();
		delete dialog;
	}
	notifyDienste();
}

void PTerminDialog::onBtDelDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		list_dienst_minis.erase(list_dienst_minis.begin() + i);
		list_dienst_num.erase(list_dienst_num.begin() + i);
		list_dienst_minis_possible.erase(list_dienst_minis_possible.begin() + i);
	}
	notifyDienste();
}

void PTerminDialog::onLIDienstActivated(wxListEvent& evt) {
	std::vector<Dienst*> missing_dienste;
	missing_dienste.insert(missing_dienste.begin(), list_dienst_num.at(evt.GetItem().GetId()).first);
	for (std::vector<Dienst*>::iterator iter = global_dienste->begin(); iter != global_dienste->end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = list_dienst_num.begin(); iter_t != list_dienst_num.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	PTerminDienstDialog* dialog = new PTerminDienstDialog(this, &list_dienst_minis, &list_dienst_num, &list_dienst_minis_possible, evt.GetItem().GetId(), global_minis);
	dialog->ShowModal();
	delete dialog;
	notifyDienste();
}

void PTerminDialog::onBtOK(wxCommandEvent&) {
	wxString t_zeit_beginn;
	if (!Util::formatTime(tc_zeit->GetValue(), &t_zeit_beginn)) {
		wxMessageDialog dialog(this, R::MSG_TIME_ERR);
		dialog.ShowModal();
		return;
	}
	//directly change object, controlling view has to update
	termin->name = Util::rmD(tc_name->GetValue());
	termin->ort = Util::rmD(tc_ort->GetValue());
	termin->datum = dc_datum->GetValue();
	termin->zeit_beginn = t_zeit_beginn;

	termin->list_dienst_minis = list_dienst_minis;
	termin->list_dienst_num = list_dienst_num;
	termin->list_dienst_minis_possible = list_dienst_minis_possible;

	//handle connections and reset available lists in tgruppe!!!!
	PlanerController::recalculateAvailableListsInTGruppe(termin);
	//put correct mini nums!!
	Util::setMiniNums(global_minis, global_termine);
	//sort termine (by date))
	std::sort(global_termine->begin(), global_termine->end(), PTermin::cmp);
	//put correct termin indices
	int counter = 0;
	for (std::vector<PTermin*>::iterator iter = global_termine->begin(); iter != global_termine->end(); iter++) {
		(**iter)._id = counter++;
	}
	
	termin->bem = Util::rmD(tc_bem->GetValue());
	//sort own tgruppe
	PTermin::sortGruppe(termin);
	*edt = true;
	Close(true);
}

void PTerminDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void PTerminDialog::onDateChanged(wxDateEvent&) {
	st_datum_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"));
}