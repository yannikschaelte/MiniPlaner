/* 
 * File:   TGruppePanel.cpp
 * Author: Yannik
 * 
 * Created on August 16, 2015, 10:30 AM
 */

#include "TGruppenPanel.h"
#include "../App.h"
#include "../model-data/TGruppe.h"
#include "TGruppeDialog.h"
#include "../Util.h"
#include "DeleteDialog.h"

TGruppenPanel::TGruppenPanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	lv_tgruppen = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[3];
	cols[0].SetText(wxT(""));
	lv_tgruppen->InsertColumn(0, cols[0]);
	cols[1].SetText(R::TGRUPPE);
	lv_tgruppen->InsertColumn(1, cols[1]);
	cols[2].SetText(R::TERMINE);
	lv_tgruppen->InsertColumn(2, cols[2]);
	notifyTGruppen();
	sizer->Add(lv_tgruppen, 1, wxEXPAND, 0);
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer->Add(sizer_r, 0, 0, 0);

	SetSizer(sizer);
}

void TGruppenPanel::notifyTGruppen(int index) {
	lv_tgruppen->DeleteAllItems();
	list_tgruppen_indices.clear();
	int counter = 0;
	int tgruppen_counter = 0;
	int num_tgruppen = app->list_tgruppe.size();
	for (int i = 0; i < num_tgruppen; i++) {
		TGruppe tg = *(app->list_tgruppe.at(i));
		wxListItem item;
		item.SetId(counter);
		lv_tgruppen->InsertItem(item);
		lv_tgruppen->SetItem(counter, 0, wxString::Format(wxT("%i"), tgruppen_counter + 1));
		lv_tgruppen->SetItem(counter, 1, TGruppe::printModus(&tg));
		list_tgruppen_indices.push_back(counter);
		counter++;
		tgruppen_counter++;
		for (int j = 0; j < (int) tg.list_einzel.size(); j++) {
			Einzeltermin* t = tg.list_einzel.at(j);
			wxListItem item_t;
			item_t.SetId(counter);
			lv_tgruppen->InsertItem(item_t);
			lv_tgruppen->SetItem(counter, 2, Einzeltermin::printShort(t));
			counter++;
		}
		for (int j = 0; j < (int) tg.list_serie.size(); j++) {
			Serientermin* t = tg.list_serie.at(j);
			wxListItem item_t;
			item_t.SetId(counter);
			lv_tgruppen->InsertItem(item_t);
			lv_tgruppen->SetItem(counter, 2, Serientermin::printShort(t));
			counter++;
		}
	}
	if (index != -1) lv_tgruppen->Select(list_tgruppen_indices.at(index), true);
	for (int i = 0; i < 3; i++) {
		lv_tgruppen->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(TGruppenPanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, TGruppenPanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, TGruppenPanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, TGruppenPanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, TGruppenPanel::onLIActivated)
EVT_LIST_ITEM_SELECTED(R::ID_LC, TGruppenPanel::onLISelected)
EVT_LIST_KEY_DOWN(R::ID_LC, TGruppenPanel::onLIKey)
END_EVENT_TABLE()

void TGruppenPanel::onBtAdd(wxCommandEvent&) {
	TGruppeDialog* dialog = new TGruppeDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void TGruppenPanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_tgruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		for (int j = 0; j < (int) list_tgruppen_indices.size(); j++) {
			if (i == list_tgruppen_indices.at(j)) {
				bool del = false;
				DeleteDialog dialog(this, &del);
				dialog.ShowModal();
				if (del) app->delTGruppe(j);
				break;
			}
		}
		break;
	}
}

void TGruppenPanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_tgruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		for (int j = 0; j < (int) list_tgruppen_indices.size(); j++) {
			if (i == list_tgruppen_indices.at(j)) {
				TGruppeDialog* dialog = new TGruppeDialog(this, app, j);
				dialog->ShowModal();
				delete dialog;
				break;
			}
		}
		break;
	}
}

void TGruppenPanel::onLIActivated(wxListEvent& evt) {
	int index = evt.GetItem().GetId();
	for (int i = 0; i < (int) list_tgruppen_indices.size(); i++) {
		if (index == list_tgruppen_indices.at(i)) {
			TGruppeDialog* dialog = new TGruppeDialog(this, app, i);
			dialog->ShowModal();
			delete dialog;
			break;
		}
	}
}

void TGruppenPanel::onLISelected(wxListEvent& evt) {
	int index = evt.GetItem().GetId();
	bool correctIndex = false;
	for (int i = 0; i < (int) list_tgruppen_indices.size(); i++) {
		if (index == list_tgruppen_indices.at(i)) {
			correctIndex = true;
			break;
		}
	}
	if (!correctIndex) {
		lv_tgruppen->Select(index, false);
	}
}

void TGruppenPanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lv_tgruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			for (int j = 0; j < (int) list_tgruppen_indices.size(); j++) {
				if (i == list_tgruppen_indices.at(j)) {
					bool del = false;
					DeleteDialog dialog(this, &del);
					dialog.ShowModal();
					if (del) app->delTGruppe(j);
					break;
				}
			}
			break;
		}
	}
}