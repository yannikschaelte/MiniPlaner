/* 
 * File:   MGruppenPanel.cpp
 * Author: Yannik
 * 
 * Created on August 13, 2015, 11:44 AM
 */

#include "MGruppenPanel.h"
#include "../R.h"
#include "../App.h"
#include "MGruppeDialog.h"
#include "../model-data/Messdiener.h"
#include "DeleteDialog.h"

MGruppenPanel::MGruppenPanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	lv_gruppen = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[3];
	wxString cols_s[3] = {wxT(""), R::MODUS, R::GRUPPE};
	for (int i = 0; i < 3; i++) {
		cols[i].SetText(cols_s[i]);
		lv_gruppen->InsertColumn(i, cols[i]);
	}
	notifyMGruppen();
	sizer->Add(lv_gruppen, 1, wxEXPAND, 0);
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer->Add(sizer_r, 0, 0, 0);
	SetSizerAndFit(sizer);
}

void MGruppenPanel::notifyMGruppen(int index) {
	lv_gruppen->DeleteAllItems();
	int size = app->list_mgruppe.size();
	for (int i = 0; i < size; i++) {
		wxListItem item;
		item.SetId(i);
		lv_gruppen->InsertItem(item);
		lv_gruppen->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_gruppen->SetItem(i, 1, R::MGMODI[app->list_mgruppe.at(i)->modus]);
		lv_gruppen->SetItem(i, 2, MGruppe::printShort(app->list_mgruppe.at(i)));
	}
	if (index != -1) lv_gruppen->Select(index, true);
	for (int i = 0; i < 3; i++) {
		lv_gruppen->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(MGruppenPanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, MGruppenPanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, MGruppenPanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, MGruppenPanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, MGruppenPanel::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, MGruppenPanel::onLIKey)
END_EVENT_TABLE()

void MGruppenPanel::onBtAdd(wxCommandEvent&) {
	MGruppeDialog* dialog = new MGruppeDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void MGruppenPanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_gruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delMGruppe(i);
		break;
	}
}

void MGruppenPanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_gruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		MGruppeDialog* dialog = new MGruppeDialog(this, app, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
}

void MGruppenPanel::onLIActivated(wxListEvent& evt) {
	MGruppeDialog* dialog = new MGruppeDialog(this, app, evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
}

void MGruppenPanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lv_gruppen->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delMGruppe(i);
			break;
		}
	}
}