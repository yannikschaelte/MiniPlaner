/* 
 * File:   MiniDialog.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 7:36 PM
 */

#include "MiniDialog.h"
#include "../App.h"
#include "../R.h"
#include "../Util.h"

MiniDialog::MiniDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::MINI_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

MiniDialog::MiniDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::MINI_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void MiniDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* gridsizer = new wxFlexGridSizer(R::MINI_ATTS_NUM, 2, 0, 0);

	st_name = new wxStaticText(this, R::ID_ANY, R::NACHNAME, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_name, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_name = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_name, 1, wxEXPAND | wxALL, 2);

	st_vorname = new wxStaticText(this, R::ID_ANY, R::VORNAME, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_vorname, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_vorname = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_vorname, 1, wxEXPAND | wxALL, 2);

	st_dienste = new wxStaticText(this, R::ID_ANY, R::DIENSTE, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_dienste, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num_dienste = app->list_dienst.size();
	wxString dienste[num_dienste];
	for (int i = 0; i < num_dienste; i++) {
		dienste[i] = app->list_dienst.at(i)->name;
	}
	lb_dienste = new wxCheckListBox(this, R::ID_LC, wxDefaultPosition, wxDefaultSize, num_dienste, dienste, wxLB_SINGLE);
	gridsizer->Add(lb_dienste, 1, wxEXPAND | wxALL, 2);

	st_geburtstag = new wxStaticText(this, R::ID_ANY, R::GEBURTSTAG, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_geburtstag, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* gtagsizer = new wxBoxSizer(wxHORIZONTAL);
	cb_geburtstag = new wxCheckBox(this, R::ID_BT_ADD, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	cb_geburtstag->SetValue(false);
	gtagsizer->Add(cb_geburtstag, 0, wxALL | wxALIGN_CENTER, 0);
	dc_geburtstag = new wxDatePickerCtrl(this, R::ID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	dc_geburtstag->Enable(false);
	gtagsizer->Add(dc_geburtstag, 1, wxEXPAND | wxALL, 0);
	gridsizer->Add(gtagsizer, 1, wxEXPAND | wxALL, 2);

	st_strasse_nr = new wxStaticText(this, R::ID_ANY, R::STRASSE_NR, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_strasse_nr, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_strasse_nr = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_strasse_nr, 1, wxEXPAND | wxALL, 2);

	st_plz_ort = new wxStaticText(this, R::ID_ANY, R::PLZ_ORT, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_plz_ort, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num_plzorte = app->list_plzort.size();
	wxString arr_plzorte[num_plzorte];
	for (int i = 0; i < num_plzorte; i++) {
		arr_plzorte[i] = app->list_plzort.at(i);
	}
	tc_plz_ort = new wxComboBox(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, num_plzorte, arr_plzorte);
	gridsizer->Add(tc_plz_ort, 1, wxEXPAND | wxALL, 2);

	st_tel = new wxStaticText(this, R::ID_ANY, R::TEL, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_tel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_tel = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_tel, 1, wxEXPAND | wxALL, 2);

	st_mobil = new wxStaticText(this, R::ID_ANY, R::MOBILE, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_mobil, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_mobil = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_mobil, 1, wxEXPAND | wxALL, 2);

	st_email = new wxStaticText(this, R::ID_ANY, R::EMAIL, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_email, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_email = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_email, 1, wxEXPAND | wxALL, 2);

	st_bem = new wxStaticText(this, R::ID_ANY, R::BEM, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(st_bem, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_bem = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gridsizer->Add(tc_bem, 1, wxEXPAND | wxALL, 2);

	gridsizer->AddGrowableCol(1, 1);
	gridsizer->AddGrowableRow(2, 1);
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

	if (edt) {
		Messdiener* m = app->list_mini.at(index);
		tc_name->SetValue(m->name);
		tc_vorname->SetValue(m->vorname);
		int mnum_dienste = m->dienste.size();
		for (int i = 0; i < num_dienste; i++) {
			for (int j = 0; j < mnum_dienste; j++) {
				if (app->list_dienst.at(i) == m->dienste.at(j)) {
					lb_dienste->Check(i, true);
				}
			}
		}
		if (m->geburtstag != wxT("")) {
			dc_geburtstag->SetValue(Util::wxString_to_wxDateTime(m->geburtstag));
			cb_geburtstag->SetValue(true);
			dc_geburtstag->Enable(true);
		}
		tc_strasse_nr->SetValue(m->strasse_nr);
		tc_plz_ort->SetValue(m->plz_ort);
		tc_tel->SetValue(m->tel);
		tc_mobil->SetValue(m->mobile);
		tc_email->SetValue(m->email);
		tc_bem->SetValue(m->bem);
	} else {
		for (int i = 0; i < num_dienste; i++) {
			lb_dienste->Check(i, true);
		}
	}

	SetSizerAndFit(sizer);
	if (GetSize().GetWidth() < 260) {
		SetSize(260, -1);
	}
}

BEGIN_EVENT_TABLE(MiniDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, MiniDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, MiniDialog::onBtCancel)
EVT_CHECKBOX(R::ID_BT_ADD, MiniDialog::onCbGeburtstag)
END_EVENT_TABLE()

void MiniDialog::onBtOK(wxCommandEvent& event) {
	wxString date = cb_geburtstag->IsChecked() ? Util::wxDateTime_to_wxString(dc_geburtstag->GetValue()) : wxT("");
	std::vector<Dienst*> dienste;
	for (int i = 0; i < (int) app->list_dienst.size(); i++) {
		if (lb_dienste->IsChecked(i)) {
			dienste.push_back(app->list_dienst.at(i));
		}
	}
	Messdiener* m = new Messdiener(Util::rmD(tc_name->GetValue()), Util::rmD(tc_vorname->GetValue()), dienste, date,
			Util::rmD(tc_strasse_nr->GetValue()), Util::rmD(tc_plz_ort->GetValue()), Util::rmD(tc_tel->GetValue()),
			Util::rmD(tc_mobil->GetValue()), Util::rmD(tc_email->GetValue()), Util::rmD(tc_bem->GetValue()));
	if (edt) {
		if (!app->edtMini(index, m)) {
			delete m;
			wxMessageDialog dialog(this, R::MSG_MINI_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			delete m;
			Close(true);
		}
	} else {
		if (!app->addMini(m)) {
			delete m;
			wxMessageDialog dialog(this, R::MSG_MINI_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			Close(true);
		}
	}
}

void MiniDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void MiniDialog::onCbGeburtstag(wxCommandEvent&) {
	dc_geburtstag->Enable(!dc_geburtstag->IsEnabled());
}