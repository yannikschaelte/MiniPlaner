/* 
 * File:   PlanerMiniInterfaceDialog.cpp
 * Author: Yannik
 * 
 * Created on March 22, 2016, 2:54 PM
 */

#include "PlanerMiniInterfaceDialog.h"
#include <algorithm>
#include <wx/clipbrd.h>
#include <wx/filedlg.h>
#include <wx/statline.h>
#include <wx/wfstream.h>
#include <wx/tokenzr.h>
#include "../App.h"
#include "../R.h"
#include "../Util.h"
#include "../view-plan/PTerminDialog.h"
#include "../view-data/DeleteDialog.h"
#include "../file/DataFileHandler.h"

PlanerMiniInterfaceDialog::PlanerMiniInterfaceDialog(wxWindow* parent, App* _app, bool* _edt,
		wxDateTime* _datum_beginn,
		wxDateTime* _datum_ende,
		std::vector<Dienst*>* _list_dienst,
		std::vector<PTermin*>* _list_termin,
		std::vector<PMessdiener*>* _list_mini,
		std::vector<PMGruppe*>* _list_mgruppe,
		std::vector<PFehlzeit*>* _list_fehlzeit)
: wxDialog(parent, R::ID_ANY, wxT("MiniInterface-Dialog"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
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

void PlanerMiniInterfaceDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxChoicebook* choicebook = new wxChoicebook(this, R::ID_ANY);
	sizer->Add(choicebook, 1, wxEXPAND, 0);
	SetSizer(sizer);
	pl_1 = new wxPanel(choicebook, R::ID_ANY);
	choicebook->AddPage(pl_1, wxT("Daten für MiniInterface-Formular exportieren"));
	pl_2 = new wxPanel(choicebook, R::ID_ANY);
	choicebook->AddPage(pl_2, wxT("Mit Daten aus MiniInterface-Formular Plan erstellen"));

	//Export********************************************************************
	wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
	pl_1->SetSizer(sizer_1);

	//Zeitraum
	pl_zeitraum = new wxPanel(pl_1, R::ID_ANY);
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
	sizer_1->Add(pl_zeitraum, 1, wxEXPAND | wxALL, 5);

	//Termine
	nb_termine = new wxNotebook(pl_1, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

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

	sizer_1->Add(nb_termine, 1, wxEXPAND | wxALL, 5);

	//Navigation
	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_back = new wxButton(pl_1, R::ID_BT_BACK, R::ZURUECK);
	btsizer->Add(bt_back, 0, 0, 0);
	bt_cont = new wxButton(pl_1, R::ID_BT_CONT, R::WEITER);
	btsizer->Add(bt_cont, 0, wxRIGHT, 5);
	bt_cancel = new wxButton(pl_1, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel, 0, 0, 0);
	sizer_1->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	//Import********************************************************************
	wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
	st_imp_text = new wxStaticText(pl_2, R::ID_ANY, wxT("Kopieren Sie den kompletten Inhalt der Datei \"MiniInterface.dat\" in die Zwischenablage\n(z.B. per Strg+A, Strg+C)."));
	sizer_2->Add(st_imp_text, 0, wxEXPAND | wxALL, 5);
	cb_imp_anw = new wxCheckBox(pl_2, R::ID_ANY, wxT("Bei positiver Rückmeldung (\"Felder mit Häkchen\") Messdiener zufällig eintragen (berücksichtigt keine M.-Gruppen)"));
	cb_imp_anw->SetValue(true);
	sizer_2->Add(cb_imp_anw, 0, wxEXPAND | wxALL, 5);
	bt_imp_pull = new wxButton(pl_2, R::ID_BT_ADD2, wxT("Lade Daten aus Zwischenablage"));
	sizer_2->Add(bt_imp_pull, 0, wxALL, 5);
	sizer_2->Add(new wxPanel(this), 1, wxEXPAND, 0);
	//Navigation
	wxBoxSizer* btsizer_2 = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn_2 = new wxPanel(this);
	pl_nn_2->SetSize(30, -1);
	btsizer_2->Add(pl_nn_2, 1, wxEXPAND);
	bt_imp_cancel = new wxButton(pl_2, R::ID_BT_CANCEL, R::CANCEL);
	btsizer_2->Add(bt_imp_cancel, 0, 0, 0);
	sizer_2->Add(btsizer_2, 0, wxALL | wxEXPAND, 5);

	pl_2->SetSizer(sizer_2);
	setModusZeitraum();
}

void PlanerMiniInterfaceDialog::setModusZeitraum() {
	modus = MODUS_ZEITRAUM;
	pl_zeitraum->Show();
	nb_termine->Hide();
	bt_back->Hide();
	Fit();
}

void PlanerMiniInterfaceDialog::setModusTermine() {
	modus = MODUS_TERMINE;
	pl_zeitraum->Hide();
	nb_termine->Show();
	bt_back->Show();
	Fit();
}

void PlanerMiniInterfaceDialog::notifyTermine(int index) {
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

void PlanerMiniInterfaceDialog::notifyTGruppen() {
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

wxString PlanerMiniInterfaceDialog::createData() {
	wxString D = DataFileHandler::D;
	//datum, dienste
	wxString text = Util::wxDateTime_to_wxString(*datum_beginn) + D + Util::wxDateTime_to_wxString(*datum_ende) + D + wxString::Format(wxT("%i"), list_dienst->size());
	for (int i = 0; i < (int) list_dienst->size(); i++) {
		text += D + list_dienst->at(i)->name;
	}
	text += wxT("\n");
	//termine
	text += wxString::Format(wxT("%i"), list_termin->size());
	for (int i = 0; i < (int) list_termin->size(); i++) {
		text += wxT("\n");
		PTermin t = *(list_termin->at(i));
		text += t.name + D + t.ort + D + Util::wxDateTime_to_wxString(t.datum) + D + t.zeit_beginn + D
				+ (t.prev == NULL ? wxT("-1") : wxString::Format(wxT("%i"), t.prev->_id)) + D
				+ (t.next == NULL ? wxT("-1") : wxString::Format(wxT("%i"), t.next->_id)) + D
				+ t.bem;
		for (std::vector<std::pair<Dienst*, int> >::iterator iter = t.list_dienst_num.begin(); iter != t.list_dienst_num.end(); iter++) {
			text += D + wxString::Format(wxT("%i"), iter->first->_id) + D + wxString::Format(wxT("%i"), iter->second);
		}
	}
	//minis mit anwesenheiten
	text += wxT("\n") + wxString::Format(wxT("%i"), list_mini->size());
	for (int i = 0; i < (int) list_mini->size(); i++) {
		text += wxT("\n");
		PMessdiener* m = list_mini->at(i);
		text += m->name + D + m->vorname;
		for (int j = 0; j < (int) m->dienste.size(); j++) {
			text += D + wxString::Format(wxT("%i"), m->dienste.at(j)->_id);
		}
		text += wxT("\n");
		for (int j = 0; j < (int) list_termin->size(); j++) {
			bool canPlay = false;
			for (std::vector< std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter = list_termin->at(j)->list_dienst_minis_possible.begin();
					iter != list_termin->at(j)->list_dienst_minis_possible.end() && !canPlay; iter++) {
				if (std::find(iter->second.begin(), iter->second.end(), m) != iter->second.end()) {
					canPlay = true;
				}
			}
			if (canPlay) {
				text += wxString::Format(wxT("%i"), ANW_VIELLEICHT) + D;
			} else {
				text += wxString::Format(wxT("%i"), ANW_NEIN) + D;
			}
		}
	}
	//mgruppen
	text += wxT("\n") + wxString::Format(wxT("%i"), list_mgruppe->size());
	for (int i = 0; i < (int) list_mgruppe->size(); i++) {
		PMGruppe mg = *(list_mgruppe->at(i));
		wxString line = wxString::Format(wxT("%i"), mg.modus);
		for (std::vector<PMessdiener*>::iterator iter_m = mg.list.begin(); iter_m != mg.list.end(); iter_m++) {
			line += D + wxString::Format(wxT("%i"), (**iter_m)._id);
		}
		text += wxT("\n") + line;
	}
	//fehlzeiten
	text += wxT("\n") + wxString::Format(wxT("%i"), list_fehlzeit->size());
	for (int i = 0; i < (int) list_fehlzeit->size(); i++) {
		PFehlzeit* f = list_fehlzeit->at(i);
		wxString line = wxString::Format(wxT("%i"), Fehlzeit::ZEITRAUM) + D + wxString::Format(wxT("%i"), f->mini->_id)
				+ D + Util::wxDateTime_to_wxString(f->datum_beginn)
				+ D + Util::wxDateTime_to_wxString(f->datum_ende);
		text += wxT("\n") + line;
	}
	return text;
}

void PlanerMiniInterfaceDialog::edtTermin(int index) {
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

void PlanerMiniInterfaceDialog::delTermin(int index) {
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

BEGIN_EVENT_TABLE(PlanerMiniInterfaceDialog, wxDialog)
EVT_BUTTON(R::ID_BT_BACK, PlanerMiniInterfaceDialog::onBtBack)
EVT_BUTTON(R::ID_BT_CONT, PlanerMiniInterfaceDialog::onBtCont)
EVT_BUTTON(R::ID_BT_CANCEL, PlanerMiniInterfaceDialog::onBtCancel)
EVT_BUTTON(R::ID_BT_EDT, PlanerMiniInterfaceDialog::onBtEdt)
EVT_BUTTON(R::ID_BT_DEL, PlanerMiniInterfaceDialog::onBtDel)
EVT_BUTTON(R::ID_BT_ADD2, PlanerMiniInterfaceDialog::onBtImpPull)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, PlanerMiniInterfaceDialog::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, PlanerMiniInterfaceDialog::onLIKey)
EVT_CLOSE(PlanerMiniInterfaceDialog::onClose)
END_EVENT_TABLE()

void PlanerMiniInterfaceDialog::onBtBack(wxCommandEvent&) {
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

void PlanerMiniInterfaceDialog::onBtCont(wxCommandEvent&) {
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

		//generate data for file
		wxString text = createData();
		wxFileDialog saveFileDialog(this, wxT("Datei speichern"), wxT("output"), wxT("MiniInterface.dat"), wxT("MiniInterface.dat"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
		wxFileOutputStream output_stream(saveFileDialog.GetPath());
		if (!output_stream.IsOk()) {
			return;
		}
		wxScopedCharBuffer text_utf8 = text.ToUTF8();
		output_stream.Write(text_utf8, text_utf8.length());
		output_stream.Close();

		//closing
		Close(true);
	}
}

void PlanerMiniInterfaceDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void PlanerMiniInterfaceDialog::onBtEdt(wxCommandEvent&) {
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

void PlanerMiniInterfaceDialog::onBtDel(wxCommandEvent&) {
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

void PlanerMiniInterfaceDialog::onBtImpPull(wxCommandEvent&) {
	//tidy up from exp
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
	//done
	if (readData()) {
		*edt = true;
		deleteContents = false;
		wxMessageBox(wxT("Daten erfolgreich verarbeitet!"), wxT("Meldung"), wxICON_EXCLAMATION);
		Close(true);
	} else {
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
		wxMessageBox(wxT("Daten aus Zwischenablage konnten nicht korrekt verarbeitet werden!"), wxT("Fehler"), wxICON_ERROR);
	}
}

bool PlanerMiniInterfaceDialog::readData() {
	if (wxTheClipboard->Open()) {
		wxString D = DataFileHandler::D;
		wxTextDataObject data;
		wxTheClipboard->GetData(data);
		wxTheClipboard->Close();
		wxString text = data.GetText();
		wxStringTokenizer zr(text, wxT("\n"), wxTOKEN_RET_EMPTY_ALL);
		//datum
		wxStringTokenizer zr_1(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
		*datum_beginn = Util::wxString_to_wxDateTime(zr_1.NextToken());
		*datum_ende = Util::wxString_to_wxDateTime(zr_1.NextToken());
		//dienste
		int num_dienste;
		if (!safeAtoi(zr_1.NextToken(), &num_dienste)) return false;
		for (int i = 0; i < num_dienste; i++) {
			list_dienst->push_back(new Dienst(zr_1.NextToken()));
		}
		//termine
		std::vector<std::pair<int, std::pair<int, int> > > termin_prev_next;
		int num_termine;
		if (!safeAtoi(zr.NextToken(), &num_termine)) return false;
		for (int i = 0; i < num_termine; i++) {
			wxStringTokenizer zr_2(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
			wxString name = zr_2.NextToken();
			wxString ort = zr_2.NextToken();
			wxDateTime datum = Util::wxString_to_wxDateTime(zr_2.NextToken());
			wxString zeit_beginn = zr_2.NextToken();
			int prev;
			if (!safeAtoi(zr_2.NextToken(), &prev)) return false;
			int next;
			if (!safeAtoi(zr_2.NextToken(), &next)) return false;
			termin_prev_next.push_back(std::make_pair(i, std::make_pair(prev, next)));
			wxString bem = zr_2.NextToken();
			std::vector<std::pair<Dienst*, int> > list_num;
			while (zr_2.HasMoreTokens()) {
				int id;
				if (!safeAtoi(zr_2.NextToken(), &id)) return false;
				int num;
				if (!safeAtoi(zr_2.NextToken(), &num)) return false;
				list_num.push_back(std::make_pair(list_dienst->at(id), num));
			}
			PTermin* termin = new PTermin(name, ort, datum, zeit_beginn, bem, list_num);
			list_termin->push_back(termin);
		}
		//set links prev-next
		for (std::vector<std::pair<int, std::pair<int, int> > >::iterator iter_t = termin_prev_next.begin(); iter_t != termin_prev_next.end(); iter_t++) {
			if (iter_t->second.first != -1) {
				list_termin->at(iter_t->first)->prev = list_termin->at(iter_t->second.first);
			}
			if (iter_t->second.second != -1) {
				list_termin->at(iter_t->first)->next = list_termin->at(iter_t->second.second);
			}
		}
		//minis
		int num_minis;
		if (!safeAtoi(zr.NextToken(), &num_minis)) return false;
		std::vector< std::pair<PMessdiener*, std::vector<int> > > list_mini_anw;
		for (int i = 0; i < num_minis; i++) {
			wxStringTokenizer zr_3(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
			wxString name = zr_3.NextToken();
			wxString vorname = zr_3.NextToken();
			std::vector<Dienst*> dienste;
			while (zr_3.HasMoreTokens()) {
				int id;
				if (!safeAtoi(zr_3.NextToken(), &id)) return false;
				dienste.push_back(list_dienst->at(id));
			}
			PMessdiener* mini = new PMessdiener(name, vorname, dienste);
			list_mini->push_back(mini);
			//anw
			std::vector<int> list_anw;
			wxStringTokenizer zr_3_2(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
			for (int j = 0; j < num_termine; j++) {
				int id;
				if (!safeAtoi(zr_3_2.NextToken(), &id)) return false;
				list_anw.push_back(id);
			}
			list_mini_anw.push_back(std::make_pair(mini, list_anw));
		}
		//mgruppen
		int num_mgruppen;
		if (!safeAtoi(zr.NextToken(), &num_mgruppen)) return false;
		for (int i = 0; i < num_mgruppen; i++) {
			wxStringTokenizer zr_4(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
			int modus;
			if (!safeAtoi(zr_4.NextToken(), &modus)) return false;
			std::vector<PMessdiener*> mlist;
			while (zr_4.HasMoreTokens()) {
				int id;
				if (!safeAtoi(zr_4.NextToken(), &id)) return false;
				mlist.push_back(list_mini->at(id));
			}
			list_mgruppe->push_back(new PMGruppe(modus, mlist));
		}
		//set missing links Minis-MGruppen
		for (std::vector<PMGruppe*>::iterator iter = list_mgruppe->begin(); iter != list_mgruppe->end(); iter++) {
			for (std::vector<PMessdiener*>::iterator iter_m = (**iter).list.begin(); iter_m != (**iter).list.end(); iter_m++) {
				(**iter_m).gruppe = *iter;
			}
		}
		//fehlzeiten
		int num_fehlzeiten;
		if (!safeAtoi(zr.NextToken(), &num_fehlzeiten)) return false;
		for (int i = 0; i < num_fehlzeiten; i++) {
			wxStringTokenizer zr_5(zr.NextToken(), D, wxTOKEN_RET_EMPTY_ALL);
			zr_5.NextToken(); //Modus
			int id;
			if (!safeAtoi(zr_5.NextToken(), &id)) return false;
			PMessdiener* m = list_mini->at(id);
			wxDateTime datum_beginn = Util::wxString_to_wxDateTime(zr_5.NextToken());
			wxDateTime datum_ende = Util::wxString_to_wxDateTime(zr_5.NextToken());
			list_fehlzeit->push_back(new PFehlzeit(m, datum_beginn, datum_ende));
		}
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
		////termin lists
		//fill lists according to abilities
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis;
		for (std::vector<Dienst*>::iterator iter_d = list_dienst->begin(); iter_d != list_dienst->end(); iter_d++) {
			std::vector<PMessdiener*> m_liste;
			for (std::vector<PMessdiener*>::iterator iter_m = list_mini->begin(); iter_m != list_mini->end(); iter_m++) {
				if (std::find((**iter_m).dienste.begin(), (**iter_m).dienste.end(), *iter_d) != (**iter_m).dienste.end()) {
					m_liste.push_back(*iter_m);
				}
			}
			list_dienst_minis.push_back(std::make_pair(*iter_d, m_liste));
		}
		//fill list_dienst_minis (with ZEROs) and list_dienst_minis_possible (according to above abilities)
		for (std::vector<PTermin*>::iterator iter_t = list_termin->begin(); iter_t != list_termin->end(); iter_t++) {
			for (std::vector<std::pair<Dienst*, int> >::iterator iter_d = (**iter_t).list_dienst_num.begin(); iter_d != (**iter_t).list_dienst_num.end(); iter_d++) {
				std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_list = list_dienst_minis.begin();
				for (; iter_list->first != iter_d->first; iter_list++) {
				}
				(**iter_t).list_dienst_minis_possible.push_back(*iter_list);
				//fill in same order and initiate with NULL pointers (needed later and for file)
				std::vector<PMessdiener*> mset;
				mset.reserve(iter_d->second);
				for (int i = 0; i < iter_d->second; i++) {
					mset.push_back(NULL);
				}
				(**iter_t).list_dienst_minis.push_back(std::make_pair(iter_list->first, mset));
			}
		}
		//abwesenheiten
		for (int i = 0; i < num_minis; i++) {
			for (int j = 0; j < num_termine; j++) {
				if (list_mini_anw.at(i).second.at(j) == ANW_NEIN) {
					for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = list_termin->at(j)->list_dienst_minis_possible.begin();
							iter_poss != list_termin->at(j)->list_dienst_minis_possible.end(); iter_poss++) {
						Util::erase_from_minivec(&iter_poss->second, list_mini->at(i));
					}
				}
			}
		}
		//fill avai
		for (int j = 0; j < num_termine; j++) {
			for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = list_termin->at(j)->list_dienst_minis_possible.begin();
					iter_poss != list_termin->at(j)->list_dienst_minis_possible.end(); iter_poss++) {
				list_termin->at(j)->list_dienst_minis_available.push_back(*iter_poss);
			}
		}
		//anwesenheiten
		if (cb_imp_anw->IsChecked()) {
			std::random_shuffle(list_mini_anw.begin(), list_mini_anw.end());
			for (int j = 0; j < num_termine; j++) {
				PTermin* termin = list_termin->at(j);
				int num_dienste = termin->list_dienst_num.size();
				std::random_shuffle(list_mini_anw.begin(), list_mini_anw.end());
				for (int i = 0; i < num_minis; i++) {
					if (list_mini_anw.at(i).second.at(j) == ANW_JA) {
						PMessdiener* mini = list_mini_anw.at(i).first;
						for (int k = num_dienste - 1; k >= 0; k--) {
							//calculate req
							int num_req = termin->list_dienst_num.at(k).second;
							for (std::vector<PMessdiener*>::iterator iter = termin->list_dienst_minis.at(k).second.begin(); iter != termin->list_dienst_minis.at(k).second.end(); iter++) {
								if (*iter != NULL) num_req--;
							}
							if (num_req > 0 && std::find(termin->list_dienst_minis_available.at(k).second.begin(), termin->list_dienst_minis_available.at(k).second.end(), mini)
									!= termin->list_dienst_minis_available.at(k).second.end()) {
								std::vector<PMessdiener*>::iterator iter = termin->list_dienst_minis.at(k).second.begin();
								while (*iter != NULL) iter++;
								*iter = mini;
								mini->num++;
								num_req--;
								for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_d = termin->list_dienst_minis_available.begin(); iter_d != termin->list_dienst_minis_available.end(); iter_d++) {
									Util::erase_from_minivec(&iter_d->second, mini);
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool PlanerMiniInterfaceDialog::safeAtoi(wxString text, int* var) {
	if (text.IsEmpty() || !text.IsNumber()) return false;
	*var = wxAtoi(text);
	return true;
}

void PlanerMiniInterfaceDialog::onLIActivated(wxListEvent& evt) {
	edtTermin(evt.GetItem().GetId());
}

void PlanerMiniInterfaceDialog::onLIKey(wxListEvent& evt) {
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

void PlanerMiniInterfaceDialog::onClose(wxCloseEvent& evt) {
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