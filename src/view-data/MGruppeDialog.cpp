/* 
 * File:   MGruppeDialog.cpp
 * Author: Yannik
 * 
 * Created on August 13, 2015, 7:08 PM
 */

#include "MGruppeDialog.h"
#include <wx/gbsizer.h>
#include "../App.h"
#include "../R.h"
#include "../Util.h"
#include <algorithm>

MGruppeDialog::MGruppeDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::MGRUPPE_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

MGruppeDialog::MGruppeDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::MGRUPPE_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void MGruppeDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizer_modus = new wxBoxSizer(wxHORIZONTAL);
	st_modus = new wxStaticText(this, R::ID_ANY, R::MODUS);
	sizer_modus->Add(st_modus, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
	wxString modi[2] = {R::BEV_GEM, R::NUR_GEM};
	ch_modus = new wxChoice(this, R::ID_CH, wxDefaultPosition, wxDefaultSize, 2, modi);
	ch_modus->SetSelection(0);
	sizer_modus->Add(ch_modus, 1, wxEXPAND, 0);
	sizer->Add(sizer_modus, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* sizer_t = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizer_gruppe = new wxBoxSizer(wxVERTICAL);
	st_gruppe = new wxStaticText(this, R::ID_ANY, R::GRUPPE);
	sizer_gruppe->Add(st_gruppe, 0, 0, 0);
	lv_gruppe = new wxListView(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL);
	wxListItem lv_gruppe_col;
	lv_gruppe->InsertColumn(0, lv_gruppe_col);
	sizer_gruppe->Add(lv_gruppe, 1, wxEXPAND, 0);
	sizer_t->Add(sizer_gruppe, 1, wxEXPAND, 0);

	wxBoxSizer* inout_sizer = new wxBoxSizer(wxVERTICAL);
	bt_togroup = new wxButton(this, R::ID_BT_ADD, wxT("\x2190"));
	inout_sizer->Add(bt_togroup, 1, wxALL, 5);
	bt_torest = new wxButton(this, R::ID_BT_DEL, wxT("\x2192"));
	inout_sizer->Add(bt_torest, 1, wxALL, 5);
	sizer_t->Add(inout_sizer, 0, wxALIGN_CENTER_VERTICAL, 0);

	wxBoxSizer* sizer_rest = new wxBoxSizer(wxVERTICAL);
	st_rest = new wxStaticText(this, R::ID_ANY, R::RESTLISTE);
	sizer_rest->Add(st_rest, 0, 0, 0);
	lv_rest = new wxListView(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL);
	wxListItem lv_rest_col;
	lv_rest->InsertColumn(0, lv_rest_col);
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

	initRest();
	drawRest();
	if (edt) {
		ch_modus->SetSelection(app->list_mgruppe.at(index)->modus);
		initGruppe();
		drawGruppe();
	}
	lv_gruppe->Fit();
	lv_rest->Fit();
	SetSizerAndFit(sizer);
	if (GetSize().GetHeight() < 300) {
		SetSize(-1, 300);
	}
}

void MGruppeDialog::initRest() {
	list_rest = app->list_mini;
	std::vector<Messdiener*>::iterator iter = list_rest.begin();
	while (iter != list_rest.end()) {
		bool inSomeGroup = false;
		for (std::vector<MGruppe*>::iterator iter_mg = app->list_mgruppe.begin(); iter_mg != app->list_mgruppe.end() && !inSomeGroup; iter_mg++) {
			for (std::vector<Messdiener*>::iterator iter_m = (**iter_mg).list.begin(); iter_m != (**iter_mg).list.end(); iter_m++) {
				if (*iter_m == *iter) {
					inSomeGroup = true;
					break;
				}
			}
		}
		if (inSomeGroup) {
			iter = list_rest.erase(iter);
		} else {
			iter++;
		}
	}
}

void MGruppeDialog::initGruppe() {
	list_gruppe = app->list_mgruppe.at(index)->list;
}

void MGruppeDialog::drawRest() {
	lv_rest->DeleteAllItems();
	int size = list_rest.size();
	for (int i = 0; i < size; i++) {
		wxListItem item;
		item.SetId(i);
		lv_rest->InsertItem(item);
		Messdiener* m = list_rest.at(i);
		lv_rest->SetItem(i, 0, m->vorname + wxT(" ") + m->name);
	}
	lv_rest->SetColumnWidth(0, wxLIST_AUTOSIZE);
}

void MGruppeDialog::drawGruppe() {
	lv_gruppe->DeleteAllItems();
	int size = list_gruppe.size();
	for (int i = 0; i < size; i++) {
		wxListItem item;
		item.SetId(i);
		lv_gruppe->InsertItem(item);
		Messdiener* m = list_gruppe.at(i);
		lv_gruppe->SetItem(i, 0, m->vorname + wxT(" ") + m->name);
	}
	lv_gruppe->SetColumnWidth(0, wxLIST_AUTOSIZE);
}

BEGIN_EVENT_TABLE(MGruppeDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, MGruppeDialog::onBtToGruppe)
EVT_BUTTON(R::ID_BT_DEL, MGruppeDialog::onBtToRest)
EVT_BUTTON(R::ID_BT_OK, MGruppeDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, MGruppeDialog::onBtCancel)
END_EVENT_TABLE()

void MGruppeDialog::onBtToGruppe(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_rest->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		list_gruppe.push_back(list_rest.at(i));
		std::sort(list_gruppe.begin(), list_gruppe.end(), Messdiener::cmp);
		list_rest.erase(list_rest.begin() + i);

		drawRest();
		drawGruppe();
		break;
	}
}

void MGruppeDialog::onBtToRest(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_gruppe->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		list_rest.push_back(list_gruppe.at(i));
		std::sort(list_rest.begin(), list_rest.end(), Messdiener::cmp);
		list_gruppe.erase(list_gruppe.begin() + i);

		drawGruppe();
		drawRest();
		break;
	}
}

void MGruppeDialog::onBtOk(wxCommandEvent&) {
	if (list_gruppe.size() > 1) {//group has min. 2 members
		MGruppe* mg = new MGruppe(ch_modus->GetSelection(), list_gruppe);
		if (edt) {
			app->edtMGruppe(index, mg);
			delete mg;
		} else {
			app->addMGruppe(mg);
		}
		Close(true);
	} else {
		wxMessageDialog dialog(this, R::MSG_GROUP_NUM);
		dialog.ShowModal();
	}
}

void MGruppeDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}