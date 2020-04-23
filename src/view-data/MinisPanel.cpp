/* 
 * File:   MinisPanel.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 5:37 PM
 */

#include "MinisPanel.h"
#include <algorithm>
#include "../App.h"
#include "../model-data/Messdiener.h"
#include "MiniDialog.h"
#include "DeleteDialog.h"
#include "../export/MiniExportDialog.h"
#include "../import/MiniImportDialog.h"
#include "MiniExtrasDialog.h"

MinisPanel::MinisPanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;
	sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer_r = new wxBoxSizer(wxVERTICAL);
	lc_minis = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem lc_minis_cols[R::MINI_ATTS_NUM + 1];
	lc_minis_cols[0].SetText(wxT(""));
	lc_minis->InsertColumn(0, lc_minis_cols[0]);
	for (int i = 1; i < R::MINI_ATTS_NUM + 1; i++) {
		lc_minis_cols[i].SetText(R::MINI_ATTS[i - 1]);
		lc_minis->InsertColumn(i, lc_minis_cols[i]);
	}
	notifyMinis();
	sizer->Add(lc_minis, 1, wxEXPAND, 0);
	
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer_r->Add(new wxPanel(this, R::ID_ANY), 1, wxEXPAND, 0);
	bt_import = new wxButton(this, R::ID_IMPORT, R::IMPORT);
	sizer_r->Add(bt_import, 0, 0, 0);
	bt_export = new wxButton(this, R::ID_EXPORT, R::EXPORT);
	sizer_r->Add(bt_export, 0, 0, 0);
	bt_extras = new wxButton(this, R::ID_BT_COMPUTE, R::EXTRAS);
	sizer_r->Add(bt_extras, 0, 0, 0);
	sizer->Add(sizer_r, 0, wxEXPAND, 0);

	SetSizer(sizer);
}

void MinisPanel::notifyMinis(int index) {
	shownMinis = app->list_mini;
	drawMinis(index);
}

void MinisPanel::drawMinis(int index) {
	lc_minis->DeleteAllItems();
	const int num = shownMinis.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		Messdiener* m = shownMinis.at(i);
		lc_minis->InsertItem(item);
		lc_minis->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lc_minis->SetItem(i, 1, m->name);
		lc_minis->SetItem(i, 2, m->vorname);
		lc_minis->SetItem(i, 3, Messdiener::printDienste(m));
		lc_minis->SetItem(i, 4, m->geburtstag);
		lc_minis->SetItem(i, 5, m->strasse_nr);
		lc_minis->SetItem(i, 6, m->plz_ort);
		lc_minis->SetItem(i, 7, m->tel);
		lc_minis->SetItem(i, 8, m->mobile);
		lc_minis->SetItem(i, 9, m->email);
		lc_minis->SetItem(i, 10, m->bem);
	}
	if (index != -1) lc_minis->Select(index, true);
	for (int i = 0; i < R::MINI_ATTS_NUM + 1; i++) {
		lc_minis->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(MinisPanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, MinisPanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, MinisPanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, MinisPanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, MinisPanel::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, MinisPanel::onLIKey)
//EVT_LIST_COL_CLICK(R::ID_LC, MinisPanel::onColClick)
EVT_BUTTON(R::ID_EXPORT, MinisPanel::onBtExport)
EVT_BUTTON(R::ID_IMPORT, MinisPanel::onBtImport)
EVT_BUTTON(R::ID_BT_COMPUTE, MinisPanel::onBtExtras)
END_EVENT_TABLE()

void MinisPanel::onBtAdd(wxCommandEvent&) {
	MiniDialog* dialog = new MiniDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void MinisPanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_minis->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delMini(i);
		break;
	}
}

void MinisPanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_minis->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		MiniDialog* dialog = new MiniDialog(this, app, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
}

void MinisPanel::onLIActivated(wxListEvent& evt) {
	MiniDialog* dialog = new MiniDialog(this, app, evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
}

void MinisPanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lc_minis->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delMini(i);
			break;
		}
	}
}

void MinisPanel::sortByString(bool inc, wxString Messdiener::* var) {
	if (inc) {
		std::sort(shownMinis.begin(), shownMinis.end(), [&var](const Messdiener* m1, const Messdiener* m2) {return (m1->*var).Cmp(m2->*var) < 0;});
	} else {
		std::sort(shownMinis.begin(), shownMinis.end(), [&var](const Messdiener* m1, const Messdiener* m2) {return (m1->*var).Cmp(m2->*var) > 0;});
	}
	drawMinis();
}

void MinisPanel::onBtExport(wxCommandEvent&) {
	MiniExportDialog dialog(this, &app->list_mini);
	dialog.ShowModal();
}

void MinisPanel::onBtImport(wxCommandEvent&) {
	bool edt = false;
	std::vector<Messdiener*> list_mini;
	MiniImportDialog dialog(this, &list_mini, &edt);
	dialog.ShowModal();
	if (edt) app->importMinis(list_mini);
}

void MinisPanel::onBtExtras(wxCommandEvent&) {
	MiniExtrasDialog dialog(this, &app->list_mini);
	dialog.ShowModal();
}