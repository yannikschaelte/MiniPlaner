/* 
 * File:   TGruppeDialog.cpp
 * Author: Yannik
 * 
 * Created on August 16, 2015, 1:48 PM
 */

#include "TGruppeDialog.h"
#include <algorithm>
#include "../R.h"
#include "../App.h"
#include "../Util.h"
#include "../model-data/TGruppe.h"

TGruppeDialog::TGruppeDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::TGRUPPE_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

TGruppeDialog::TGruppeDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::TGRUPPE_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void TGruppeDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizer_w = new wxBoxSizer(wxHORIZONTAL);
	st_wochentag = new wxStaticText(this, R::ID_ANY, R::PERIODISCH);
	sizer_w->Add(st_wochentag, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 2);
	ch_wochentag = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 7, R::WOCHENTAGE);
	ch_wochentag->SetSelection(0);
	sizer_w->Add(ch_wochentag, 0, wxEXPAND | wxLEFT, 2);
	sizer->Add(sizer_w, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* sizer_t = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_tgruppe = new wxBoxSizer(wxVERTICAL);
	st_tgruppe = new wxStaticText(this, R::ID_ANY, R::TGRUPPE);
	sizer_tgruppe->Add(st_tgruppe, 0, 0, 0);
	lv_tgruppe = new wxListView(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_NO_HEADER);
	wxListItem col_tgruppe;
	lv_tgruppe->InsertColumn(0, col_tgruppe);
	sizer_tgruppe->Add(lv_tgruppe, 1, wxEXPAND, 0);
	sizer_t->Add(sizer_tgruppe, 1, wxEXPAND, 0);

	wxBoxSizer* inout_sizer = new wxBoxSizer(wxVERTICAL);
	bt_togroup = new wxButton(this, R::ID_BT_ADD, wxT("\x2190"));
	inout_sizer->Add(bt_togroup, 1, wxALL, 5);
	bt_torest = new wxButton(this, R::ID_BT_DEL, wxT("\x2192"));
	inout_sizer->Add(bt_torest, 1, wxALL, 5);
	sizer_t->Add(inout_sizer, 0, wxALIGN_CENTER_VERTICAL, 0);

	wxBoxSizer* sizer_rest = new wxBoxSizer(wxVERTICAL);
	st_rest = new wxStaticText(this, R::ID_ANY, R::RESTTERMINE);
	sizer_rest->Add(st_rest, 0, 0, 0);
	lv_rest = new wxListView(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_NO_HEADER);
	wxListItem col_rest;
	lv_rest->InsertColumn(0, col_rest);
	sizer_rest->Add(lv_rest, 1, wxEXPAND, 0);
	sizer_t->Add(sizer_rest, 1, wxEXPAND, 0);

	sizer->Add(sizer_t, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);
	//delete items from rest lists
	list_einzel_rest = app->list_einzeltermin;
	list_serie_rest = app->list_serientermin;
	std::vector<Einzeltermin*>::iterator iter = list_einzel_rest.begin();
	while (iter != list_einzel_rest.end()) {
		bool inSomeGroup = false;
		for (std::vector<TGruppe*>::iterator iter_tg = app->list_tgruppe.begin(); iter_tg != app->list_tgruppe.end() && !inSomeGroup; iter_tg++) {
			for (std::vector<Einzeltermin*>::iterator iter_t = (**iter_tg).list_einzel.begin(); iter_t != (**iter_tg).list_einzel.end(); iter_t++) {
				if (*iter == *iter_t) {
					inSomeGroup = true;
					break;
				}
			}
		}

		if (inSomeGroup) {
			iter = list_einzel_rest.erase(iter);
		} else {
			iter++;
		}
	}
	std::vector<Serientermin*>::iterator iter2 = list_serie_rest.begin();
	while (iter2 != list_serie_rest.end()) {
		bool inSomeGroup = false;
		for (std::vector<TGruppe*>::iterator iter_tg = app->list_tgruppe.begin(); iter_tg != app->list_tgruppe.end() && !inSomeGroup; iter_tg++) {
			for (std::vector<Serientermin*>::iterator iter_t = (**iter_tg).list_serie.begin(); iter_t != (**iter_tg).list_serie.end(); iter_t++) {
				if (*iter2 == *iter_t) {
					inSomeGroup = true;
					break;
				}
			}
		}
		if (inSomeGroup) {
			iter2 = list_serie_rest.erase(iter2);
		} else {
			iter2++;
		}
	}
	if (edt) {
		TGruppe tgruppe = *(app->list_tgruppe.at(index));
		list_einzel_tgruppe = tgruppe.list_einzel;
		list_serie_tgruppe = tgruppe.list_serie;
		if (tgruppe.list_serie.size() > 0) {
			ch_wochentag->SetSelection(tgruppe.wochentag);
			setModePeriodic();
		} else {
			setModeNonPeriodic();
		}
	} else {
		setModeNonPeriodic();
	}
	drawGruppe();
	drawRest();
	lv_tgruppe->Fit();
	lv_rest->Fit();
	SetSizerAndFit(sizer);
	if (GetSize().GetHeight() < 300) {
		SetSize(-1, 300);
	}
}

void TGruppeDialog::setModePeriodic() {
	st_wochentag->Show();
	ch_wochentag->Show();
	Layout();
}

void TGruppeDialog::setModeNonPeriodic() {
	st_wochentag->Hide();
	ch_wochentag->Hide();
	Layout();
}

void TGruppeDialog::drawGruppe() {
	lv_tgruppe->DeleteAllItems();
	int num = list_einzel_tgruppe.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		lv_tgruppe->InsertItem(item);
		lv_tgruppe->SetItem(i, 0, Einzeltermin::printShort(list_einzel_tgruppe.at(i)));
	}
	for (int i = 0; i < (int) list_serie_tgruppe.size(); i++) {
		wxListItem item;
		item.SetId(num + i);
		lv_tgruppe->InsertItem(item);
		lv_tgruppe->SetItem(num + i, 0, Serientermin::printShort(list_serie_tgruppe.at(i)));
	}
	lv_tgruppe->SetColumnWidth(0, wxLIST_AUTOSIZE);
}

void TGruppeDialog::drawRest() {
	lv_rest->DeleteAllItems();
	int num = list_einzel_rest.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		lv_rest->InsertItem(item);
		lv_rest->SetItem(i, 0, Einzeltermin::printShort(list_einzel_rest.at(i)));
	}
	for (int i = 0; i < (int) list_serie_rest.size(); i++) {
		wxListItem item;
		item.SetId(num + i);
		Serientermin t = *(list_serie_rest.at(i));
		lv_rest->InsertItem(item);
		lv_rest->SetItem(num + i, 0, Serientermin::printShort(list_serie_rest.at(i)));
	}
	lv_rest->SetColumnWidth(0, wxLIST_AUTOSIZE);
}

BEGIN_EVENT_TABLE(TGruppeDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, TGruppeDialog::onBtToGruppe)
EVT_BUTTON(R::ID_BT_DEL, TGruppeDialog::onBtToRest)
EVT_BUTTON(R::ID_BT_OK, TGruppeDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, TGruppeDialog::onBtCancel)
END_EVENT_TABLE()


void TGruppeDialog::onBtToGruppe(wxCommandEvent&) {
	int i = -1;
	int num = list_einzel_rest.size();
	for (;;) {
		i = lv_rest->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		if (i >= num) {
			list_serie_tgruppe.push_back(list_serie_rest.at(i - num));
			std::sort(list_serie_tgruppe.begin(), list_serie_tgruppe.end(), Serientermin::cmp);
			list_serie_rest.erase(list_serie_rest.begin() + i - num);
		} else {
			list_einzel_tgruppe.push_back(list_einzel_rest.at(i));
			std::sort(list_einzel_tgruppe.begin(), list_einzel_tgruppe.end(), Einzeltermin::cmp);
			list_einzel_rest.erase(list_einzel_rest.begin() + i);
		}
		break;
	}
	drawRest();
	drawGruppe();
	if (list_serie_tgruppe.size() > 0) {
		setModePeriodic();
	} else {
		setModeNonPeriodic();
	}
}

void TGruppeDialog::onBtToRest(wxCommandEvent&) {
	int i = -1;
	int num = list_einzel_tgruppe.size();
	for (;;) {
		i = lv_tgruppe->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		if (i >= num) {
			list_serie_rest.push_back(list_serie_tgruppe.at(i - num));
			std::sort(list_serie_rest.begin(), list_serie_rest.end(), Serientermin::cmp);
			list_serie_tgruppe.erase(list_serie_tgruppe.begin() + i - num);
		} else {
			list_einzel_rest.push_back(list_einzel_tgruppe.at(i));
			std::sort(list_einzel_rest.begin(), list_einzel_rest.end(), Einzeltermin::cmp);
			list_einzel_tgruppe.erase(list_einzel_tgruppe.begin() + i);
		}
		break;
	}
	drawGruppe();
	drawRest();
	if (list_serie_tgruppe.size() > 0) {
		setModePeriodic();
	} else {
		setModeNonPeriodic();
	}
}

void TGruppeDialog::onBtOk(wxCommandEvent&) {
	if (list_einzel_tgruppe.size() + list_serie_tgruppe.size() > 1) {
		TGruppe* tg;
		if (list_serie_tgruppe.size() > 0) {
			tg = new TGruppe(ch_wochentag->GetSelection(), list_einzel_tgruppe, list_serie_tgruppe);
		} else {
			tg = new TGruppe(0, list_einzel_tgruppe, list_serie_tgruppe);
		}
		if (edt) {
			app->edtTGruppe(index, tg);
			delete tg;
		} else {
			app->addTGruppe(tg);
		}
		Close(true);
	} else {
		wxMessageDialog dialog(this, R::MSG_TGROUP_NUM);
		dialog.ShowModal();
	}
}

void TGruppeDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}