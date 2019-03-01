/* 
 * File:   FehlzeitenPanel.cpp
 * Author: Yannik
 * 
 * Created on August 23, 2015, 12:59 PM
 */

#include "FehlzeitenPanel.h"
#include "../App.h"
#include "../R.h"
#include "FehlzeitDialog.h"
#include "DeleteDialog.h"

FehlzeitenPanel::FehlzeitenPanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	app = _app;
	lv_fehlzeiten = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[3];
	wxString cols_texts[3] = {wxT(""), R::NAME, R::FEHLZEIT};
	for (int i = 0; i < 3; i++) {
		cols[i].SetText(cols_texts[i]);
		lv_fehlzeiten->InsertColumn(i, cols[i]);
	}
	notifyFehlzeiten();
	sizer->Add(lv_fehlzeiten, 1, wxEXPAND, 0);

	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer->Add(sizer_r, 0, 0, 0);

	SetSizer(sizer);
}

void FehlzeitenPanel::notifyFehlzeiten(int index) {
	lv_fehlzeiten->DeleteAllItems();
	const int num = app->list_fehlzeit.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		Fehlzeit f = *(app->list_fehlzeit.at(i));
		lv_fehlzeiten->InsertItem(item);
		lv_fehlzeiten->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_fehlzeiten->SetItem(i, 1, f.mini->vorname + wxT(" ") + f.mini->name);
		lv_fehlzeiten->SetItem(i, 2, Fehlzeit::printModus(&f));
	}
	if (index != -1) lv_fehlzeiten->Select(index, true);
	lv_fehlzeiten->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_fehlzeiten->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
	lv_fehlzeiten->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(FehlzeitenPanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, FehlzeitenPanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, FehlzeitenPanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, FehlzeitenPanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, FehlzeitenPanel::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, FehlzeitenPanel::onLIKey)
END_EVENT_TABLE()

void FehlzeitenPanel::onBtAdd(wxCommandEvent&) {
	FehlzeitDialog* dialog = new FehlzeitDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void FehlzeitenPanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_fehlzeiten->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delFehlzeit(i);
		break;
	}
}

void FehlzeitenPanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_fehlzeiten->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		FehlzeitDialog* dialog = new FehlzeitDialog(this, app, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
}

void FehlzeitenPanel::onLIActivated(wxListEvent& evt) {
	FehlzeitDialog* dialog = new FehlzeitDialog(this, app, evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
}

void FehlzeitenPanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lv_fehlzeiten->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delFehlzeit(i);
			break;
		}
	}
}