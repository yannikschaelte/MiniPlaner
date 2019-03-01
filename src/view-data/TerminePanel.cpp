/* 
 * File:   TerminePanel.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 5:37 PM
 */

#include "TerminePanel.h"
#include <wx/splitter.h>
#include "../App.h"
#include "../Util.h"
#include "EinzelterminDialog.h"
#include "SerienterminDialog.h"
#include "../import/EinzelterminImportDialog.h"
#include "DeleteDialog.h"

TerminePanel::TerminePanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;

	wxSplitterWindow* splitterWindow = new wxSplitterWindow(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);
	splitterWindow->SetSashGravity(0.5);
	splitterWindow->SetMinimumPaneSize(20);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* pl_1 = new wxPanel(splitterWindow, R::ID_ANY);
	wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
	st_einzel = new wxStaticText(pl_1, R::ID_ANY, R::EINZELTERMINE);
	sizer_1->Add(st_einzel, 0, wxTOP, 5);
	wxBoxSizer* sizer_einzel = new wxBoxSizer(wxHORIZONTAL);
	lc_einzel = new wxListView(pl_1, R::ID_LC, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	lc_einzel_cols[0].SetId(0);
	lc_einzel_cols[0].SetText(wxT(""));
	lc_einzel->InsertColumn(0, lc_einzel_cols[0]);
	for (int i = 1; i < R::TEINZEL_NUM + 1; i++) {
		lc_einzel_cols[i].SetId(i);
		lc_einzel_cols[i].SetText(R::TEINZEL_ATTS[i - 1]);
		lc_einzel->InsertColumn(i, lc_einzel_cols[i]);
	}
	sizer_einzel->Add(lc_einzel, 1, wxEXPAND, 0);
	notifyEinzeltermine();
	wxBoxSizer* sizer_einzel_r = new wxBoxSizer(wxVERTICAL);
	bt_einzel_add = new wxButton(pl_1, R::ID_BT_ADD, R::ADD);
	sizer_einzel_r->Add(bt_einzel_add, 0, 0, 0);
	bt_einzel_edt = new wxButton(pl_1, R::ID_BT_EDT, R::EDT);
	sizer_einzel_r->Add(bt_einzel_edt, 0, 0, 0);
	bt_einzel_del = new wxButton(pl_1, R::ID_BT_DEL, R::DEL);
	sizer_einzel_r->Add(bt_einzel_del, 0, 0, 0);
	sizer_einzel_r->Add(new wxPanel(this, R::ID_ANY), 1, wxEXPAND, 0);
	bt_einzel_import = new wxButton(pl_1, R::ID_IMPORT, R::IMPORT);
	sizer_einzel_r->Add(bt_einzel_import, 0, 0, 0);
	sizer_einzel->Add(sizer_einzel_r, 0, wxEXPAND, 0);
	sizer_1->Add(sizer_einzel, 1, wxEXPAND, 0);
	pl_1->SetSizer(sizer_1);

	wxPanel* pl_2 = new wxPanel(splitterWindow, R::ID_ANY);
	wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
	st_serie = new wxStaticText(pl_2, R::ID_ANY, R::SERIENTERMINE);
	sizer_2->Add(st_serie, 0, 0, 0);
	wxBoxSizer* sizer_serie = new wxBoxSizer(wxHORIZONTAL);
	lc_serie = new wxListView(pl_2, R::ID_LC2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	lc_serie_cols[0].SetId(0);
	lc_serie_cols[0].SetText(wxT(""));
	lc_serie->InsertColumn(0, lc_serie_cols[0]);
	for (int i = 1; i < R::TSERIE_NUM + 1; i++) {
		lc_serie_cols[i].SetId(i);
		lc_serie_cols[i].SetText(R::TSERIE_ATTS[i - 1]);
		lc_serie->InsertColumn(i, lc_serie_cols[i]);
	}
	sizer_serie->Add(lc_serie, 1, wxEXPAND, 0);
	notifySerientermine();
	wxBoxSizer* sizer_serie_r = new wxBoxSizer(wxVERTICAL);
	bt_serie_add = new wxButton(pl_2, R::ID_BT_ADD2, R::ADD);
	sizer_serie_r->Add(bt_serie_add, 0, 0, 0);
	bt_serie_edt = new wxButton(pl_2, R::ID_BT_EDT2, R::EDT);
	sizer_serie_r->Add(bt_serie_edt, 0, 0, 0);
	bt_serie_del = new wxButton(pl_2, R::ID_BT_DEL2, R::DEL);
	sizer_serie_r->Add(bt_serie_del, 0, 0, 0);
	sizer_serie->Add(sizer_serie_r, 0, wxEXPAND, 0);
	sizer_2->Add(sizer_serie, 1, wxEXPAND, 0);
	pl_2->SetSizer(sizer_2);

	splitterWindow->SplitHorizontally(pl_1, pl_2);
	sizer->Add(splitterWindow, 1, wxEXPAND, 0);
	SetSizer(sizer);
}

void TerminePanel::notifyEinzeltermine(int index) {
	lc_einzel->DeleteAllItems();
	const int num = app->list_einzeltermin.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		Einzeltermin t = *(app->list_einzeltermin.at(num - 1 - i));
		lc_einzel->InsertItem(item);
		lc_einzel->SetItem(i, 0, wxString::Format(wxT("%i"), num - i));
		lc_einzel->SetItem(i, 1, t.name);
		lc_einzel->SetItem(i, 2, t.ort);
		lc_einzel->SetItem(i, 3, t.datum + wxT(" (") + R::WOCHENTAGE[Util::wxString_to_wxDateTime(t.datum).GetWeekDay()] + wxT(")"));
		lc_einzel->SetItem(i, 4, t.zeit_beginn);
		lc_einzel->SetItem(i, 5, Einzeltermin::printDienste(&t));
		lc_einzel->SetItem(i, 6, t.bem);
	}
	if (index != -1) lc_einzel->Select(num - 1 - index, true);
	for (int i = 0; i < R::TEINZEL_NUM + 1; i++) {
		lc_einzel->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

void TerminePanel::notifySerientermine(int index) {
	lc_serie->DeleteAllItems();
	const int num = app->list_serientermin.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		Serientermin t = *(app->list_serientermin.at(i));
		lc_serie->InsertItem(item);
		lc_serie->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lc_serie->SetItem(i, 1, t.name);
		lc_serie->SetItem(i, 2, t.ort);
		lc_serie->SetItem(i, 3, Serientermin::printModus(&t));
		lc_serie->SetItem(i, 4, t.zeit_beginn);
		lc_serie->SetItem(i, 5, Serientermin::printDienste(&t));
		lc_serie->SetItem(i, 6, t.datum_beginn);
		lc_serie->SetItem(i, 7, t.datum_ende);
		lc_serie->SetItem(i, 8, t.bem);
	}
	if (index != -1) lc_serie->Select(index, true);
	for (int i = 0; i < R::TSERIE_NUM + 1; i++) {
		lc_serie->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(TerminePanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, TerminePanel::onBtEinAdd)
EVT_BUTTON(R::ID_BT_DEL, TerminePanel::onBtEinDel)
EVT_BUTTON(R::ID_BT_EDT, TerminePanel::onBtEinEdt)
EVT_BUTTON(R::ID_IMPORT, TerminePanel::onBtEinImport)
EVT_BUTTON(R::ID_BT_ADD2, TerminePanel::onBtSerAdd)
EVT_BUTTON(R::ID_BT_DEL2, TerminePanel::onBtSerDel)
EVT_BUTTON(R::ID_BT_EDT2, TerminePanel::onBtSerEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, TerminePanel::onLIEinActivated)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC2, TerminePanel::onLISerActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, TerminePanel::onLIEinKey)
EVT_LIST_KEY_DOWN(R::ID_LC2, TerminePanel::onLISerKey)
END_EVENT_TABLE()

void TerminePanel::onBtEinAdd(wxCommandEvent&) {
	EinzelterminDialog* dialog = new EinzelterminDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void TerminePanel::onBtEinDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_einzel->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delEinzeltermin(app->list_einzeltermin.size() - 1 - i);
		break;
	}
}

void TerminePanel::onBtEinEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_einzel->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		EinzelterminDialog *dialog = new EinzelterminDialog(this, app, app->list_einzeltermin.size() - 1 - i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
}

void TerminePanel::onBtEinImport(wxCommandEvent&) {
	bool edt = false;
	std::vector<Einzeltermin*> list_einzel;
	EinzelterminImportDialog dialog(this, &list_einzel, &edt, &app->list_dienst);
	dialog.ShowModal();
	if (edt) app->importEinzeltermine(list_einzel);
}

void TerminePanel::onBtSerAdd(wxCommandEvent&) {
	SerienterminDialog* dialog = new SerienterminDialog(this, app);
	dialog->ShowModal();
	delete dialog;
}

void TerminePanel::onBtSerDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_serie->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) app->delSerientermin(i);
		break;
	}
}

void TerminePanel::onBtSerEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lc_serie->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		SerienterminDialog* dialog = new SerienterminDialog(this, app, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
}

void TerminePanel::onLIEinActivated(wxListEvent& evt) {
	EinzelterminDialog* dialog = new EinzelterminDialog(this, app, app->list_einzeltermin.size() - 1 - evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
}

void TerminePanel::onLISerActivated(wxListEvent& evt) {
	SerienterminDialog* dialog = new SerienterminDialog(this, app, evt.GetItem().GetId());
	dialog->ShowModal();
	delete dialog;
}

void TerminePanel::onLIEinKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lc_einzel->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delEinzeltermin(app->list_einzeltermin.size() - 1 - i);
			break;
		}
	}
}

void TerminePanel::onLISerKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lc_serie->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delSerientermin(i);
			break;
		}
	}
}