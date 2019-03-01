/* 
 * File:   DienstePanel.cpp
 * Author: Yannik
 * 
 * Created on August 19, 2015, 11:37 AM
 */

#include "DienstePanel.h"
#include "../R.h"
#include "../App.h"
#include "DienstDialog.h"
#include "DeleteDialog.h"

DienstePanel::DienstePanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	lc_dienste = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem lc_dienste_cols[2];
	lc_dienste_cols[0].SetText(wxT(""));
	lc_dienste->InsertColumn(0, lc_dienste_cols[0]);
	lc_dienste_cols[1].SetText(R::DIENST);
	lc_dienste->InsertColumn(1, lc_dienste_cols[1]);
	notifyDienste();
	sizer->Add(lc_dienste, 1, wxEXPAND, 0);
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer->Add(sizer_r, 0, 0, 0);
	SetSizerAndFit(sizer);
}

void DienstePanel::notifyDienste(int index) {
	lc_dienste->DeleteAllItems();
	const int num = app->list_dienst.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		Dienst d = *(app->list_dienst.at(i));
		lc_dienste->InsertItem(item);
		lc_dienste->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lc_dienste->SetItem(i, 1, d.name);
	}
	if (index != -1) lc_dienste->Select(index, true);
	lc_dienste->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lc_dienste->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(DienstePanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, DienstePanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, DienstePanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, DienstePanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, DienstePanel::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, DienstePanel::onLIKey)
END_EVENT_TABLE()

void DienstePanel::onBtAdd(wxCommandEvent&) {
	DienstDialog dialog(this, app);
	dialog.ShowModal();
}

void DienstePanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delDienst(i);
		break;
	}
}

void DienstePanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		DienstDialog dialog(this, app, i);
		dialog.ShowModal();
		break;
	}
}

void DienstePanel::onLIActivated(wxListEvent& evt) {
	DienstDialog dialog(this, app, evt.GetItem().GetId());
	dialog.ShowModal();
}

void DienstePanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lc_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delDienst(i);
			break;
		}
	}
}