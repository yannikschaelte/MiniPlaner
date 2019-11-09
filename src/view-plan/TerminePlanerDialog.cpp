/* 
 * File:   TerminePlanerDialog.cpp
 * Author: Yannik
 * 
 * Created on August 25, 2015, 7:56 PM
 */

#include "TerminePlanerDialog.h"
#include <algorithm>
#include "../App.h"
#include "../R.h"
#include "../Util.h"
#include "PTerminDialog.h"
#include "../view-data/DeleteDialog.h"

TerminePlanerDialog::TerminePlanerDialog(wxWindow* parent, App* _app, bool* _edt,
		wxDateTime* _datum_beginn,
		wxDateTime* _datum_ende,
		std::vector<Dienst*>* _list_dienst,
		std::vector<PTermin*>* _list_termin,
		std::vector<PMessdiener*>* _list_mini,
		std::vector<PMGruppe*>* _list_mgruppe,
		std::vector<PFehlzeit*>* _list_fehlzeit)
: wxDialog(parent, R::ID_ANY, R::PLAN_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	deleteContents = true;
	edt = _edt;
	datum_beginn = _datum_beginn;
	datum_ende = _datum_ende;
	list_dienst = _list_dienst;
	list_termin = _list_termin;
	list_mini = _list_mini;
	list_mgruppe = _list_mgruppe;
	list_fehlzeit = _list_fehlzeit;
	initComponents();
}

void TerminePlanerDialog::initComponents() {
	pl_zeitraum = new wxPanel(this, R::ID_ANY);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	//Zeitraum
	wxFlexGridSizer* sizer_zeitraum = new wxFlexGridSizer(2, 2, 0, 0);
	st_beginn = new wxStaticText(pl_zeitraum, R::ID_ANY, R::DATUM_BEGINN);
	sizer_zeitraum->Add(st_beginn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	cl_beginn = new wxCalendarCtrl(pl_zeitraum, R::ID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, 0);
	sizer_zeitraum->Add(cl_beginn, 0, wxALL, 5);
	st_ende = new wxStaticText(pl_zeitraum, R::ID_ANY, R::DATUM_ENDE);
	sizer_zeitraum->Add(st_ende, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	cl_ende = new wxCalendarCtrl(pl_zeitraum, R::ID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, 0);
	sizer_zeitraum->Add(cl_ende, 0, wxALL, 5);
	pl_zeitraum->SetSizer(sizer_zeitraum);
	pl_zeitraum->Fit();
	sizer->Add(pl_zeitraum, 1, wxEXPAND | wxALL, 5);

	//Termine
	nb_termine = new wxNotebook(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

	nb_pl_termine = new wxPanel(nb_termine, R::ID_ANY);
	nb_termine->InsertPage(0, nb_pl_termine, R::TERMINE);
	wxBoxSizer* sizer_nb_pl_termine = new wxBoxSizer(wxHORIZONTAL);
	lv_termine = new wxListView(nb_pl_termine, R::ID_LC, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[R::TEINZEL_NUM + 1];
	cols[0].SetText(wxT(""));
	lv_termine->InsertColumn(0, cols[0]);
	for (int i = 1; i < R::TEINZEL_NUM + 1; i++) {
		cols[i].SetText(R::TEINZEL_ATTS[i - 1]);
		lv_termine->InsertColumn(i, cols[i]);
	}
	sizer_nb_pl_termine->Add(lv_termine, 1, wxEXPAND | wxALL, 0);
	wxBoxSizer* sizer_nb_pl_termine_r = new wxBoxSizer(wxVERTICAL);
	bt_termine_edt = new wxButton(nb_pl_termine, R::ID_BT_EDT, R::EDT);
	sizer_nb_pl_termine_r->Add(bt_termine_edt, 0, 0, 0);
	bt_termine_del = new wxButton(nb_pl_termine, R::ID_BT_DEL, R::DEL);
	sizer_nb_pl_termine_r->Add(bt_termine_del, 0, 0, 0);
	sizer_nb_pl_termine->Add(sizer_nb_pl_termine_r, 0, 0, 0);
	nb_pl_termine->SetSizer(sizer_nb_pl_termine);

	//TGruppen
	nb_pl_tgruppen = new wxPanel(nb_termine, R::ID_ANY);
	nb_termine->InsertPage(1, nb_pl_tgruppen, R::TGRUPPEN);
	wxBoxSizer* sizer_nb_pl_tgruppen = new wxBoxSizer(wxHORIZONTAL);
	lv_tgruppen = new wxListView(nb_pl_tgruppen, R::ID_LC2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols2[2];
	cols2[0].SetText(wxT(""));
	cols2[1].SetText(R::TGRUPPE);
	lv_tgruppen->InsertColumn(0, cols2[0]);
	lv_tgruppen->InsertColumn(1, cols2[1]);
	sizer_nb_pl_tgruppen->Add(lv_tgruppen, 1, wxEXPAND | wxALL, 0);
	nb_pl_tgruppen->SetSizer(sizer_nb_pl_tgruppen);

	sizer->Add(nb_termine, 1, wxEXPAND | wxALL, 5);

	//Navigation
	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_back = new wxButton(this, R::ID_BT_BACK, R::ZURUECK);
	btsizer->Add(bt_back, 0, 0, 0);
	bt_cont = new wxButton(this, R::ID_BT_CONT, R::WEITER);
	btsizer->Add(bt_cont, 0, wxRIGHT, 5);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel, 0, 0, 0);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	setModusZeitraum();
}

void TerminePlanerDialog::setModusZeitraum() {
	modus = MODUS_ZEITRAUM;
	pl_zeitraum->Show();
	nb_termine->Hide();
	bt_back->Hide();
	Fit();
}

void TerminePlanerDialog::setModusTermine() {
	modus = MODUS_TERMINE;
	pl_zeitraum->Hide();
	nb_termine->Show();
	bt_back->Show();
	Fit();
}

void TerminePlanerDialog::notifyTermine(int index) {
	lv_termine->DeleteAllItems();
	for (int i = 0; i < (int) list_termin->size(); i++) {
		wxListItem item;
		item.SetId(i);
		PTermin* t = list_termin->at(i);
		lv_termine->InsertItem(item);
		lv_termine->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_termine->SetItem(i, 1, t->name);
		lv_termine->SetItem(i, 2, t->ort);
		lv_termine->SetItem(i, 3, Util::wxDateTime_to_wxString(t->datum) + wxT(" (") + R::WOCHENTAGE[t->datum.GetWeekDay()] + wxT(")"));
		lv_termine->SetItem(i, 4, t->zeit_beginn);
		lv_termine->SetItem(i, 5, PTermin::printDienste(t));
		lv_termine->SetItem(i, 6, t->bem);
	}
	if (index != -1) lv_termine->Select(index, true);
	for (int i = 0; i < R::TEINZEL_NUM + 1; i++) {
		lv_termine->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

void TerminePlanerDialog::notifyTGruppen() {
	lv_tgruppen->DeleteAllItems();
	int counter = 0;
	int gcounter = 1;
	for (std::vector<PTermin*>::iterator iter = list_termin->begin(); iter != list_termin->end(); iter++) {
		if ((**iter).prev == (PTermin *) NULL) {
			PTermin* termin = *iter;
			wxListItem item;
			item.SetId(counter);
			lv_tgruppen->InsertItem(item);
			lv_tgruppen->SetItem(counter, 0, wxString::Format(wxT("%i"), gcounter));
			bool ownRow = false;
			while (termin != (PTermin*) NULL) {
				if (ownRow) {
					counter++;
					wxListItem item;
					item.SetId(counter);
					lv_tgruppen->InsertItem(item);
				} else {
					ownRow = true;
				}
				lv_tgruppen->SetItem(counter, 1, PTermin::printShort(termin));
				termin = termin->next;
			}
			counter++;
			gcounter++;
		}
	}
	lv_tgruppen->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_tgruppen->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(TerminePlanerDialog, wxDialog)
EVT_BUTTON(R::ID_BT_BACK, TerminePlanerDialog::onBtBack)
EVT_BUTTON(R::ID_BT_CONT, TerminePlanerDialog::onBtCont)
EVT_BUTTON(R::ID_BT_CANCEL, TerminePlanerDialog::onBtCancel)
EVT_BUTTON(R::ID_BT_EDT, TerminePlanerDialog::onBtEdt)
EVT_BUTTON(R::ID_BT_DEL, TerminePlanerDialog::onBtDel)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, TerminePlanerDialog::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, TerminePlanerDialog::onLIKey)
EVT_CLOSE(TerminePlanerDialog::onClose)
END_EVENT_TABLE()

void TerminePlanerDialog::onBtBack(wxCommandEvent&) {
	if (modus == MODUS_TERMINE) {
		for (std::vector<Dienst*>::iterator iter = list_dienst->begin(); iter != list_dienst->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PTermin*>::iterator iter = list_termin->begin(); iter != list_termin->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PMessdiener*>::iterator iter = list_mini->begin(); iter != list_mini->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PMGruppe*>::iterator iter = list_mgruppe->begin(); iter != list_mgruppe->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PFehlzeit*>::iterator iter = list_fehlzeit->begin(); iter != list_fehlzeit->end(); iter++) {
			delete *iter;
		}
		list_dienst->clear();
		list_termin->clear();
		list_mini->clear();
		list_mgruppe->clear();
		list_fehlzeit->clear();

		setModusZeitraum();
	}
}

void TerminePlanerDialog::onBtCont(wxCommandEvent&) {
	if (modus == MODUS_ZEITRAUM) {
		*datum_beginn = cl_beginn->GetDate();
		*datum_ende = cl_ende->GetDate();
		if (datum_beginn->IsLaterThan(*datum_ende)) {
			wxMessageDialog dialog(this, R::MSG_DATUM_ORDER);
			dialog.ShowModal();
			return;
		}
		//**Translation of dates************************************************
		std::vector<TerminCreator::PTerminHolder> list_termin_paar;
		TerminCreator::createLists(*datum_beginn, *datum_ende,
				&app->list_dienst,
				&app->list_einzeltermin, &app->list_serientermin, &app->list_tgruppe,
				&app->list_mini, &app->list_mgruppe, &app->list_fehlzeit,
				list_dienst, &list_termin_paar, list_mini, list_mgruppe, list_fehlzeit);
		//reminiscence of old times (division might be useful)
		TerminCreator::fillMLists(&list_termin_paar, list_mini, &app->list_fehlzeit, list_dienst);
		TerminCreator::createTerminList(&list_termin_paar, list_termin);
		//**********************************************************************
		notifyTermine();
		notifyTGruppen();
		setModusTermine();
	} else {
		deleteContents = false;
		*edt = true;

		//prepare ids
		int counter = 0;
		for (std::vector<Dienst*>::iterator iter = list_dienst->begin(); iter != list_dienst->end(); iter++) {
			(**iter)._id = counter++;
		}
		counter = 0;
		for (std::vector<PMessdiener*>::iterator iter = list_mini->begin(); iter != list_mini->end(); iter++) {
			(**iter)._id = counter++;
		}
		counter = 0;
		for (std::vector<PMGruppe*>::iterator iter = list_mgruppe->begin(); iter != list_mgruppe->end(); iter++) {
			(**iter)._id = counter++;
		}
		counter = 0;
		for (std::vector<PTermin*>::iterator iter = list_termin->begin(); iter != list_termin->end(); iter++) {
			(**iter)._id = counter++;
		}
		counter = 0;
		for (std::vector<PFehlzeit*>::iterator iter = list_fehlzeit->begin(); iter != list_fehlzeit->end(); iter++) {
			(**iter)._id = counter++;
		}
		Close(true);
	}
}

void TerminePlanerDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void TerminePlanerDialog::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		edtTermin(i);
		break;
	}
}

void TerminePlanerDialog::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) delTermin(i);
		break;
	}
}

void TerminePlanerDialog::onLIActivated(wxListEvent& evt) {
	edtTermin(evt.GetItem().GetId());
}

void TerminePlanerDialog::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lv_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) delTermin(i);
			break;
		}
	}
}

void TerminePlanerDialog::edtTermin(int index) {
	PTermin* termin = list_termin->at(index);
	bool edt_termin = false;
	PTerminDialog* dialog = new PTerminDialog(this, termin, list_termin, list_dienst, list_mini, &edt_termin);
	dialog->ShowModal();
	delete dialog;
	if (edt_termin) {
		int j = 0;
		while (list_termin->at(j) != termin) j++;
		notifyTermine(j);
		notifyTGruppen();
	}
}

void TerminePlanerDialog::delTermin(int index) {
	PTermin* t = list_termin->at(index);
	if (t->prev != NULL) {
		t->prev->next = t->next;
	}
	if (t->next != NULL) {
		t->next->prev = t->prev;
	}
	delete t;
	list_termin->erase(list_termin->begin() + index);
	int counter = 0;
	for (std::vector<PTermin*>::iterator iter = list_termin->begin(); iter != list_termin->end(); iter++) {
		(**iter)._id = counter++;
	}
	Util::setMiniNums(list_mini, list_termin);
	notifyTermine();
	notifyTGruppen();
}

void TerminePlanerDialog::onClose(wxCloseEvent& evt) {
	if (deleteContents) {
		for (std::vector<Dienst*>::iterator iter = list_dienst->begin(); iter != list_dienst->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PTermin*>::iterator iter = list_termin->begin(); iter != list_termin->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PMessdiener*>::iterator iter = list_mini->begin(); iter != list_mini->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PMGruppe*>::iterator iter = list_mgruppe->begin(); iter != list_mgruppe->end(); iter++) {
			delete *iter;
		}
		for (std::vector<PFehlzeit*>::iterator iter = list_fehlzeit->begin(); iter != list_fehlzeit->end(); iter++) {
			delete *iter;
		}
	}
	evt.Skip();
}