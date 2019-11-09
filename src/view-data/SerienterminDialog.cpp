/* 
 * File:   SerienterminDialog.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 6:44 PM
 */

#include "SerienterminDialog.h"
#include <algorithm>
#include "../App.h"
#include "../R.h"
#include "../Util.h"
#include "TerminDienstDialog.h"

SerienterminDialog::SerienterminDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::SERIENTERMIN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

SerienterminDialog::SerienterminDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::SERIENTERMIN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void SerienterminDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	gridsizer = new wxFlexGridSizer(12, 2, 0, 0);

	st_name = new wxStaticText(this, R::ID_ANY, R::NAME);
	gridsizer->Add(st_name, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_name = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_name, 1, wxEXPAND | wxALL, 2);

	st_ort = new wxStaticText(this, R::ID_ANY, R::ORT);
	gridsizer->Add(st_ort, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int num_orte =app->list_ort.size();
	wxString arr_orte[num_orte];
	for(int i = 0; i < num_orte; i++) {
		arr_orte[i] = app->list_ort.at(i);
	}
	tc_ort = new wxComboBox(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, num_orte, arr_orte);
	gridsizer->Add(tc_ort, 1, wxEXPAND | wxALL, 2);

	st_modus = new wxStaticText(this, R::ID_ANY, R::MODUS);
	gridsizer->Add(st_modus, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_modus = new wxChoice(this, R::ID_CH, wxDefaultPosition, wxDefaultSize, R::TMODI_NUM, R::TMODI);
	gridsizer->Add(ch_modus, 1, wxEXPAND | wxALL, 2);

	st_wochentag = new wxStaticText(this, R::ID_ANY, R::WOCHENTAG);
	gridsizer->Add(st_wochentag, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_wochentag = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 7, R::WOCHENTAGE);
	ch_wochentag->SetSelection(0);
	gridsizer->Add(ch_wochentag, 0, wxEXPAND | wxALL, 2);

	st_n = new wxStaticText(this, R::ID_ANY, wxT("n"));
	gridsizer->Add(st_n, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_n = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_n, 0, wxEXPAND | wxALL, 2);

	st_woche = new wxStaticText(this, R::ID_ANY, wxT("n"));
	gridsizer->Add(st_woche, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxString n_im_monat[] = {wxT("1."), wxT("2."), wxT("3."), wxT("4."), wxT("5."), R::VORLETZTER, R::LETZTER};
	ch_woche = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 7, n_im_monat);
	ch_woche->SetSelection(0);
	gridsizer->Add(ch_woche, 0, wxEXPAND | wxALL, 2);

	st_monatstag = new wxStaticText(this, R::ID_ANY, R::TAG);
	gridsizer->Add(st_monatstag, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxString monatstage[31];
	for (int i = 0; i < 31; i++) {
		monatstage[i] = wxString::Format(wxT("%i"), i + 1);
	}
	ch_monatstag = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 31, monatstage);
	ch_monatstag->SetSelection(0);
	gridsizer->Add(ch_monatstag, 0, wxEXPAND | wxALL, 2);

	st_zeit_beginn = new wxStaticText(this, R::ID_ANY, R::ZEIT);
	gridsizer->Add(st_zeit_beginn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_zeit_beginn = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	tc_zeit_beginn->SetHint(wxT("hh:mm"));
	gridsizer->Add(tc_zeit_beginn, 1, wxEXPAND | wxALL, 2);

	st_dienste = new wxStaticText(this, R::ID_ANY, R::DIENSTE);
	gridsizer->Add(st_dienste, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_dienste = new wxBoxSizer(wxHORIZONTAL);
	lv_dienste = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[2];
	cols[0].SetText(R::DIENST);
	lv_dienste->InsertColumn(0, cols[0]);
	cols[1].SetText(R::ANZAHL);
	lv_dienste->InsertColumn(1, cols[1]);
	sizer_dienste->Add(lv_dienste, 1, wxEXPAND, 0);
	wxBoxSizer* sizer_dienste_r = new wxBoxSizer(wxVERTICAL);
	bt_add_dienst = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_dienste_r->Add(bt_add_dienst, 0, 0, 0);
	bt_edt_dienst = new wxButton(this, R::ID_BT_EDT, R::EDT);
	sizer_dienste_r->Add(bt_edt_dienst, 0, 0, 0);
	bt_del_dienst = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_dienste_r->Add(bt_del_dienst, 0, 0, 0);
	sizer_dienste->Add(sizer_dienste_r, 0, 0, 0);
	gridsizer->Add(sizer_dienste, 1, wxEXPAND | wxALL, 2);

	st_datum_beginn = new wxStaticText(this, R::ID_ANY, R::DATUM_AB);
	gridsizer->Add(st_datum_beginn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum_beginn = new wxBoxSizer(wxHORIZONTAL);
	cb_datum_beginn = new wxCheckBox(this, R::ID_BT_ADD2, wxEmptyString);
	cb_datum_beginn->SetValue(false);
	sizer_datum_beginn->Add(cb_datum_beginn, 0, wxALL | wxALIGN_CENTER, 0);
	dc_datum_beginn = new wxDatePickerCtrl(this, R::ID_LC, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	dc_datum_beginn->Enable(false);
	sizer_datum_beginn->Add(dc_datum_beginn, 1, wxEXPAND | wxALL, 0);
	st_datum_beginn_wday = new wxStaticText(this, R::ID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum_beginn->Add(st_datum_beginn_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum_beginn, 1, wxEXPAND | wxALL, 2);

	st_datum_ende = new wxStaticText(this, R::ID_ANY, R::DATUM_BIS);
	gridsizer->Add(st_datum_ende, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum_ende = new wxBoxSizer(wxHORIZONTAL);
	cb_datum_ende = new wxCheckBox(this, R::ID_BT_DEL2, wxEmptyString);
	cb_datum_ende->SetValue(false);
	sizer_datum_ende->Add(cb_datum_ende, 0, wxALL | wxALIGN_CENTER, 0);
	dc_datum_ende = new wxDatePickerCtrl(this, R::ID_LC2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	dc_datum_ende->Enable(false);
	sizer_datum_ende->Add(dc_datum_ende, 1, wxEXPAND | wxALL, 0);
	st_datum_ende_wday = new wxStaticText(this, R::ID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum_ende->Add(st_datum_ende_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum_ende, 0, wxEXPAND | wxALL, 2);

	st_bem = new wxStaticText(this, R::ID_ANY, R::BEM);
	gridsizer->Add(st_bem, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_bem = new wxTextCtrl(this, R::ID_ANY, wxEmptyString);
	gridsizer->Add(tc_bem, 1, wxEXPAND | wxALL, 2);

	gridsizer->AddGrowableCol(1, 1);
	gridsizer->AddGrowableRow(8, 1);
	sizer->Add(gridsizer, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	setModusNWochentagImMonat(); //for size
	SetSizerAndFit(sizer);
	if (GetSize().GetWidth() < 260) {
		SetSize(260, -1);
	}
	if (edt) {
		Serientermin termin = *(app->list_serientermin.at(index));
		tc_name->SetValue(termin.name);
		tc_ort->SetValue(termin.ort);
		dienste = termin.dienste;
		notifyDienste();
		tc_zeit_beginn->SetValue(termin.zeit_beginn);
		if (termin.datum_beginn != wxT("")) {
			cb_datum_beginn->SetValue(true);
			dc_datum_beginn->Enable(true);
			dc_datum_beginn->SetValue(Util::wxString_to_wxDateTime(termin.datum_beginn));
			st_datum_beginn_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_beginn->GetValue().GetWeekDay()] + wxT(")"));
		}
		if (termin.datum_ende != wxT("")) {
			cb_datum_ende->SetValue(true);
			dc_datum_ende->Enable(true);
			dc_datum_ende->SetValue(Util::wxString_to_wxDateTime(termin.datum_ende));
			st_datum_ende_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_ende->GetValue().GetWeekDay()] + wxT(")"));
		}
		tc_bem->SetValue(termin.bem);
		ch_modus->SetSelection(termin.modus);
		modus = termin.modus;
		switch (modus) {
			case Serientermin::TAEGLICH:
				setModusTaeglich();
				break;
			case Serientermin::WOECHENTLICH:
				ch_wochentag->SetSelection(termin.wochentag);
				setModusWoechentlich();
				break;
			case Serientermin::GERADE_KW:
				ch_wochentag->SetSelection(termin.wochentag);
				setModusKW();
				break;
			case Serientermin::UNGERADE_KW:
				ch_wochentag->SetSelection(termin.wochentag);
				setModusKW();
				break;
			case Serientermin::N_WOECHENTLICH:
				ch_wochentag->SetSelection(termin.wochentag);
				tc_n->SetValue(wxString::Format(wxT("%i"), termin.n));
				setModusNWoechentlich();
				break;
			case Serientermin::W_IM_MONAT:
				ch_wochentag->SetSelection(termin.wochentag);
				ch_woche->SetSelection(termin.n);
				setModusNWochentagImMonat();
				break;
			case Serientermin::MONATLICH:
				ch_monatstag->SetSelection(termin.n - 1);
				setModusMonatlich();
				break;
		}
	} else {
		modus = Serientermin::WOECHENTLICH;
		ch_modus->SetSelection(1);
		setModusWoechentlich();
	}
}

void SerienterminDialog::notifyDienste() {
	lv_dienste->DeleteAllItems();
	for (int i = 0; i < (int) dienste.size(); i++) {
		wxListItem item;
		item.SetId(i);
		lv_dienste->InsertItem(item);
		lv_dienste->SetItem(i, 0, dienste.at(i).first->name);
		lv_dienste->SetItem(i, 1, wxString::Format(wxT("%i"), dienste.at(i).second));
	}
	lv_dienste->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_dienste->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void SerienterminDialog::setModusTaeglich() {
	st_wochentag->Hide();
	ch_wochentag->Hide();
	st_n->Hide();
	tc_n->Hide();
	st_woche->Hide();
	ch_woche->Hide();
	st_monatstag->Hide();
	ch_monatstag->Hide();
	gridsizer->Layout();
}

void SerienterminDialog::setModusWoechentlich() {
	st_wochentag->Show();
	ch_wochentag->Show();
	st_n->Hide();
	tc_n->Hide();
	st_woche->Hide();
	ch_woche->Hide();
	st_monatstag->Hide();
	ch_monatstag->Hide();
	gridsizer->Layout();
}

void SerienterminDialog::setModusKW() {
	st_wochentag->Show();
	ch_wochentag->Show();
	st_n->Hide();
	tc_n->Hide();
	st_woche->Hide();
	ch_woche->Hide();
	st_monatstag->Hide();
	ch_monatstag->Hide();
	gridsizer->Layout();
}

void SerienterminDialog::setModusNWoechentlich() {
	st_wochentag->Show();
	ch_wochentag->Show();
	st_n->Show();
	tc_n->Show();
	st_woche->Hide();
	ch_woche->Hide();
	st_monatstag->Hide();
	ch_monatstag->Hide();
	gridsizer->Layout();
}

void SerienterminDialog::setModusNWochentagImMonat() {
	st_wochentag->Show();
	ch_wochentag->Show();
	st_n->Hide();
	tc_n->Hide();
	st_woche->Show();
	ch_woche->Show();
	st_monatstag->Hide();
	ch_monatstag->Hide();
	gridsizer->Layout();
}

void SerienterminDialog::setModusMonatlich() {
	st_wochentag->Hide();
	ch_wochentag->Hide();
	st_n->Hide();
	tc_n->Hide();
	st_woche->Hide();
	ch_woche->Hide();
	st_monatstag->Show();
	ch_monatstag->Show();
	gridsizer->Layout();
}

BEGIN_EVENT_TABLE(SerienterminDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, SerienterminDialog::onBtAddDienst)
EVT_BUTTON(R::ID_BT_EDT, SerienterminDialog::onBtEdtDienst)
EVT_BUTTON(R::ID_BT_DEL, SerienterminDialog::onBtDelDienst)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, SerienterminDialog::onLIDienstActivated)
EVT_BUTTON(R::ID_BT_OK, SerienterminDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, SerienterminDialog::onBtCancel)
EVT_CHOICE(R::ID_CH, SerienterminDialog::onChModus)
EVT_DATE_CHANGED(R::ID_LC, SerienterminDialog::onDateBeginnChanged)
EVT_DATE_CHANGED(R::ID_LC2, SerienterminDialog::onDateEndeChanged)
EVT_CHECKBOX(R::ID_BT_ADD2, SerienterminDialog::onCbDatumBeginn)
EVT_CHECKBOX(R::ID_BT_DEL2, SerienterminDialog::onCbDatumEnde)
END_EVENT_TABLE()

void SerienterminDialog::onBtAddDienst(wxCommandEvent&) {
	std::vector<Dienst*> missing_dienste;
	for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste);
	dialog->ShowModal();
	delete dialog;
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void SerienterminDialog::onBtEdtDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		std::vector<Dienst*> missing_dienste;
		missing_dienste.insert(missing_dienste.begin(), dienste.at(i).first);
		for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
			bool contains = false;
			for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
				if (*iter == iter_t->first) {
					contains = true;
					break;
				}
			}
			if (!contains) {
				missing_dienste.push_back(*iter);
			}
		}
		TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste, i);
		dialog->ShowModal();
		delete dialog;
		break;
	}
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void SerienterminDialog::onBtDelDienst(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_dienste->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		dienste.erase(dienste.begin() + i);
		break;
	}
	notifyDienste();
}

void SerienterminDialog::onLIDienstActivated(wxListEvent& evt) {
	int id = evt.GetItem().GetId();
	std::vector<Dienst*> missing_dienste;
	missing_dienste.insert(missing_dienste.begin(), dienste.at(id).first);
	for (std::vector<Dienst*>::iterator iter = app->list_dienst.begin(); iter != app->list_dienst.end(); iter++) {
		bool contains = false;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_t = dienste.begin(); iter_t != dienste.end(); iter_t++) {
			if (*iter == iter_t->first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			missing_dienste.push_back(*iter);
		}
	}
	TerminDienstDialog* dialog = new TerminDienstDialog(this, &dienste, &missing_dienste, id);
	dialog->ShowModal();
	delete dialog;
	std::sort(dienste.begin(), dienste.end(), Dienst::cmp2);
	notifyDienste();
}

void SerienterminDialog::onBtOK(wxCommandEvent&) {
	wxString t_zeit_beginn;
	if (!Util::formatTime(tc_zeit_beginn->GetValue(), &t_zeit_beginn)) {
		wxMessageDialog dialog(this, R::MSG_TIME_ERR);
		dialog.ShowModal();
		return;
	}
	wxString t_datum_beginn = cb_datum_beginn->IsChecked() ? Util::wxDateTime_to_wxString(dc_datum_beginn->GetValue()) : wxT("");
	wxString t_datum_ende = cb_datum_ende->IsChecked() ? Util::wxDateTime_to_wxString(dc_datum_ende->GetValue()) : wxT("");
	Serientermin* t;
	switch (modus) {
		case Serientermin::TAEGLICH:
			t = new Serientermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
					dienste, t_zeit_beginn, t_datum_beginn, t_datum_ende, modus, 0, 0, Util::rmD(tc_bem->GetValue()));
			break;
		case Serientermin::WOECHENTLICH:
		case Serientermin::GERADE_KW:
		case Serientermin::UNGERADE_KW:
			t = new Serientermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
					dienste, t_zeit_beginn, t_datum_beginn, t_datum_ende, modus, ch_wochentag->GetSelection(), 0, Util::rmD(tc_bem->GetValue()));
			break;
		case Serientermin::N_WOECHENTLICH:
			long t_n;
			if (!tc_n->GetValue().ToLong(&t_n, 10) || t_n < 1) {
				wxMessageDialog dialog(this, R::MSG_WEEK_NUM_ERR);
				dialog.ShowModal();
				return;
			}
			if (!cb_datum_beginn->IsChecked()) {
				wxMessageDialog dialog(this, R::MSG_WEEK_COUNT_START);
				dialog.ShowModal();
				return;
			}
			t = new Serientermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
					dienste, t_zeit_beginn, t_datum_beginn, t_datum_ende, modus, ch_wochentag->GetSelection(), t_n, Util::rmD(tc_bem->GetValue()));
			break;
		case Serientermin::W_IM_MONAT:
			t = new Serientermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
					dienste, t_zeit_beginn, t_datum_beginn, t_datum_ende, modus, ch_wochentag->GetSelection(), ch_woche->GetSelection(), Util::rmD(tc_bem->GetValue()));
			break;
		default://Serientermin::MONATLICH
			t = new Serientermin(Util::rmD(tc_name->GetValue()), Util::rmD(tc_ort->GetValue()),
					dienste, t_zeit_beginn, t_datum_beginn, t_datum_ende, modus, 0, ch_monatstag->GetSelection() + 1, Util::rmD(tc_bem->GetValue()));
			break;
	}
	if (edt) {
		if (!app->edtSerientermin(index, t)) {
			delete t;
			wxMessageDialog dialog(this, R::MSG_SERIE_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			delete t;
			Close(true);
		}
	} else {
		if (!app->addSerientermin(t)) {
			delete t;
			wxMessageDialog dialog(this, R::MSG_SERIE_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			Close(true);
		}
	}
}

void SerienterminDialog::onBtCancel(wxCommandEvent&) {
	Close();
}

void SerienterminDialog::onChModus(wxCommandEvent&) {
	switch (ch_modus->GetSelection()) {
		case 0:
			modus = Serientermin::TAEGLICH;
			setModusTaeglich();
			break;
		case 1:
			modus = Serientermin::WOECHENTLICH;
			setModusWoechentlich();
			break;
		case 2:
			modus = Serientermin::GERADE_KW;
			setModusKW();
			break;
		case 3:
			modus = Serientermin::UNGERADE_KW;
			setModusKW();
			break;
		case 4:
			modus = Serientermin::N_WOECHENTLICH;
			setModusNWoechentlich();
			break;
		case 5:
			modus = Serientermin::W_IM_MONAT;
			setModusNWochentagImMonat();
			break;
		case 6:
			modus = Serientermin::MONATLICH;
			setModusMonatlich();
			break;
	}
}

void SerienterminDialog::onCbDatumBeginn(wxCommandEvent&) {
	if (dc_datum_beginn->IsEnabled()) {
		dc_datum_beginn->Enable(false);
		st_datum_beginn_wday->SetLabel(wxT(""));
	} else {
		dc_datum_beginn->Enable(true);
		st_datum_beginn_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_beginn->GetValue().GetWeekDay()] + wxT(")"));
	}
}

void SerienterminDialog::onCbDatumEnde(wxCommandEvent&) {
	if (dc_datum_ende->IsEnabled()) {
		dc_datum_ende->Enable(false);
		st_datum_ende_wday->SetLabel(wxT(""));
	} else {
		dc_datum_ende->Enable(true);
		st_datum_ende_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_ende->GetValue().GetWeekDay()] + wxT(")"));
	}
}

void SerienterminDialog::onDateBeginnChanged(wxDateEvent&) {
	st_datum_beginn_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_beginn->GetValue().GetWeekDay()] + wxT(")"));
}

void SerienterminDialog::onDateEndeChanged(wxDateEvent&) {
	st_datum_ende_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_datum_ende->GetValue().GetWeekDay()] + wxT(")"));
}