/* 
 * File:   EinzelterminDialog.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 6:44 PM
 */

#include "EinzelterminDialog.h"
#include <algorithm>
#include "../App.h"
#include "../R.h"
#include "../Util.h"
#include "TerminDienstDialog.h"

EinzelterminDialog::EinzelterminDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::EINZELTERMIN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

EinzelterminDialog::EinzelterminDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::EINZELTERMIN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void EinzelterminDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* gridsizer = new wxFlexGridSizer(R::TEINZEL_NUM, 2, 0, 0);

	st_name = new wxStaticText(this, R::ID_ANY, R::NAME);
	gridsizer->Add(st_name, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_name = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_name, 1, wxEXPAND | wxALL, 2);

	st_ort = new wxStaticText(this, R::ID_ANY, R::ORT);
	gridsizer->Add(st_ort, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num_orte =app->list_ort.size();
	wxString arr_orte[num_orte];
	for(int i = 0; i < num_orte; i++) {
		arr_orte[i] = app->list_ort.at(i);
	}
	tc_ort = new wxComboBox(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, num_orte, arr_orte);
	gridsizer->Add(tc_ort, 1, wxEXPAND | wxALL, 2);

	st_datum = new wxStaticText(this, R::ID_ANY, R::DATUM);
	gridsizer->Add(st_datum, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum = new wxBoxSizer(wxHORIZONTAL);
	dc_datum = new wxDatePickerCtrl(this, R::ID_CH, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	sizer_datum->Add(dc_datum, 1, wxEXPAND | wxALL, 2);
	st_datum_wday = new wxStaticText(this, R::ID_ANY, wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum->Add(st_datum_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum, 1, wxEXPAND | wxALL, 2);

	st_zeit_beginn = new wxStaticText(this, R::ID_ANY, R::ZEIT);
	gridsizer->Add(st_zeit_beginn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_zeit_beginn = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	tc_zeit_beginn->SetHint(wxT("hh:mm"));
	gridsizer->Add(tc_zeit_beginn, 1, wxEXPAND | wxALL, 2);

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
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizer(sizer);
	Fit();
	if (GetSize().GetWidth() < 260) {
		SetSize(260, -1);
	}

	if (edt) {
		Einzeltermin termin = *(app->list_einzeltermin.at(index));
		tc_name->SetValue(termin.name);
		dienste = termin.dienste;
		notifyDienste();
		tc_ort->SetValue(termin.ort);
		dc_datum->SetValue(Util::wxString_to_wxDateTime(termin.datum));
		st_datum_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"));
		tc_zeit_beginn->SetValue(termin.zeit_beginn);
		tc_bem->SetValue(termin.bem);
	}
}

void EinzelterminDialog::notifyDienste() {
	lv_dienste->DeleteAllItems();
	int num_dienste = dienste.size();
	for (int i = 0; i < num_dienste; i++) {
		wxListItem item;
		item.SetId(i);
		lv_dienste->InsertItem(item);
		lv_dienste->SetItem(i, 0, dienste.at(i).first->name);
		lv_dienste->SetItem(i, 1, wxString::Format(wxT("%i"), dienste.at(i).second));
	}
	lv_dienste->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_dienste->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(EinzelterminDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, EinzelterminDialog::onBtAddDienst)
EVT_BUTTON(R::ID_BT_EDT, EinzelterminDialog::onBtEdtDienst)
EVT_BUTTON(R::ID_BT_DEL, EinzelterminDialog::onBtDelDienst)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, EinzelterminDialog::onLIDienstActivated)
EVT_BUTTON(R::ID_BT_OK, EinzelterminDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, EinzelterminDialog::onBtCancel)
EVT_DATE_CHANGED(R::ID_CH, EinzelterminDialog::onDateChanged)
END_EVENT_TABLE()

void EinzelterminDialog::onBtAddDienst(wxCommandEvent&) {
	std::vector<Dienst*> missing_dienste;
	for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste);
	dialog->ShowModal();
	delete dialog;
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void EinzelterminDialog::onBtEdtDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		std::vector<Dienst*> missing_dienste;
		missing_dienste.insert(missing_dienste.begin(), dienste.at(i).first);
		for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
			bool contains = false;
			for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
				if (*iter == iter_t->first) {
					contains = true;
					break;
				}
			}
			if (!contains) {
				missing_dienste.push_back(*iter);
			}
		}
		TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void EinzelterminDialog::onBtDelDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		dienste.erase(dienste.begin() + i);
		break;
	}
	notifyDienste();
}

void EinzelterminDialog::onLIDienstActivated(wxListEvent& evt) {
	std::vector<Dienst*> missing_dienste;
	missing_dienste.insert(missing_dienste.begin(), dienste.at(evt.GetItem().GetId()).first);
	for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste, evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void EinzelterminDialog::onBtOK(wxCommandEvent&) {
	wxString t_zeit_beginn;
	if (!Util::formatTime(tc_zeit_beginn->GetValue(), &t_zeit_beginn)) {
		wxMessageDialog dialog(this, R::MSG_TIME_ERR);
		dialog.ShowModal();
		return;
	}
	Einzeltermin* t = new Einzeltermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
			Util::wxDateTime_to_wxString(dc_datum->GetValue()), t_zeit_beginn, dienste, Util::rmD(tc_bem->GetValue()));
	if (edt) {
		if (!app->edtEinzeltermin(index, t)) {
			delete t;
			wxMessageDialog dialog(this, R::MSG_EINZEL_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			delete t;
			Close(true);
		}
	} else {
		if (!app->addEinzeltermin(t)) {
			delete t;
			wxMessageDialog dialog(this, R::MSG_EINZEL_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			Close(true);
		}
	}
}

void EinzelterminDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void EinzelterminDialog::onDateChanged(wxDateEvent&) {
	st_datum_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum->GetValue().GetWeekDay()] + wxT(")"));
}