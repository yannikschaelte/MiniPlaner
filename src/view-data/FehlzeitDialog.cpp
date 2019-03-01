/* 
 * File:   FehlzeitDialog.cpp
 * Author: Yannik
 * 
 * Created on August 23, 2015, 5:08 PM
 */

#include "FehlzeitDialog.h"
#include "../R.h"
#include "../model-data/Messdiener.h"
#include "../model-data/Einzeltermin.h"
#include "../model-data/Serientermin.h"
#include "../App.h"
#include "../Util.h"

FehlzeitDialog::FehlzeitDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::FEHLZEIT_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

FehlzeitDialog::FehlzeitDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::FEHLZEIT_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void FehlzeitDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	gridsizer = new wxFlexGridSizer(8, 2, 0, 0);

	st_mini = new wxStaticText(this, R::ID_ANY, R::MINI);
	gridsizer->Add(st_mini, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int minis_size = app->list_mini.size();
	wxString minis[minis_size];
	for (int i = 0; i < minis_size; i++) {
		minis[i] = app->list_mini.at(i)->vorname + wxT(" ") + app->list_mini.at(i)->name;
	}
	ch_mini = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, minis_size, minis);
	gridsizer->Add(ch_mini, 1, wxEXPAND | wxALL, 2);

	st_modus = new wxStaticText(this, R::ID_ANY, R::MODUS);
	gridsizer->Add(st_modus, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_modus = new wxChoice(this, R::ID_CH, wxDefaultPosition, wxDefaultSize, 3, R::FEHLZEIT_MODI);
	ch_modus->SetSelection(0);
	gridsizer->Add(ch_modus, 1, wxEXPAND | wxALL, 2);

	st_termin = new wxStaticText(this, R::ID_ANY, R::TERMIN);
	gridsizer->Add(st_termin, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	int etermine_size = app->list_einzeltermin.size();
	int stermine_size = app->list_serientermin.size();
	wxString termine[etermine_size + stermine_size];
	for (int i = 0; i < etermine_size; i++) {
		termine[i] = Einzeltermin::printShort(app->list_einzeltermin.at(i));
	}
	for (int i = 0; i < stermine_size; i++) {
		termine[etermine_size + i] = Serientermin::printShort(app->list_serientermin.at(i));
	}
	ch_termin = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, etermine_size + stermine_size, termine);
	gridsizer->Add(ch_termin, 1, wxEXPAND | wxALL, 2);

	st_wochentag = new wxStaticText(this, R::ID_ANY, R::WOCHENTAG);
	gridsizer->Add(st_wochentag, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_wochentag = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 7, R::WOCHENTAGE);
	ch_wochentag->SetSelection(0);
	gridsizer->Add(ch_wochentag, 1, wxEXPAND | wxALL, 2);

	st_datum_beginn = new wxStaticText(this, R::ID_ANY, R::DATUM_AB);
	gridsizer->Add(st_datum_beginn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum_beginn = new wxBoxSizer(wxHORIZONTAL);
	dc_beginn = new wxDatePickerCtrl(this, R::ID_LC, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	sizer_datum_beginn->Add(dc_beginn, 1, wxEXPAND | wxALL, 2);
	st_beginn_wday = new wxStaticText(this, R::ID_ANY, wxT("(") + R::WOCHENTAGE[dc_beginn->GetValue().GetWeekDay()] + wxT(")"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum_beginn->Add(st_beginn_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum_beginn, 1, wxEXPAND | wxALL, 2);

	st_datum_ende = new wxStaticText(this, R::ID_ANY, R::DATUM_BIS);
	gridsizer->Add(st_datum_ende, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_datum_ende = new wxBoxSizer(wxHORIZONTAL);
	dc_ende = new wxDatePickerCtrl(this, R::ID_LC2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	sizer_datum_ende->Add(dc_ende, 1, wxEXPAND | wxALL, 2);
	st_ende_wday = new wxStaticText(this, R::ID_ANY, wxT("(") + R::WOCHENTAGE[dc_ende->GetValue().GetWeekDay()] + wxT(")"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	sizer_datum_ende->Add(st_ende_wday, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 2);
	gridsizer->Add(sizer_datum_ende, 1, wxEXPAND | wxALL, 2);

	st_zeit_beginn = new wxStaticText(this, R::ID_ANY, R::VON);
	gridsizer->Add(st_zeit_beginn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_beginn = new wxTextCtrl(this, R::ID_ANY, wxT("00:00"));
	tc_beginn->SetHint(wxT("hh:mm"));
	gridsizer->Add(tc_beginn, 1, wxEXPAND | wxALL, 2);

	st_zeit_ende = new wxStaticText(this, R::ID_ANY, R::BIS);
	gridsizer->Add(st_zeit_ende, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_ende = new wxTextCtrl(this, R::ID_ANY, wxT("23:59"));
	tc_ende->SetHint(wxT("hh:mm"));
	gridsizer->Add(tc_ende, 1, wxEXPAND | wxALL, 2);

	gridsizer->AddGrowableCol(1, 1);
	sizer->Add(gridsizer, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	setModusWochentag();
	SetSizerAndFit(sizer);
	if (GetSize().GetWidth() < 410) {
		SetSize(410, -1);
	}
	if (edt) {
		Fehlzeit f = *(app->list_fehlzeit.at(index));
		ch_mini->SetSelection(f.mini->_id);
		switch (f.modus) {
			case Fehlzeit::ZEITRAUM:
				dc_beginn->SetValue(Util::wxString_to_wxDateTime(f.beginn));
				st_beginn_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_beginn->GetValue().GetWeekDay()] + wxT(")"));
				dc_ende->SetValue(Util::wxString_to_wxDateTime(f.ende));
				st_ende_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_ende->GetValue().GetWeekDay()] + wxT(")"));
				ch_modus->SetSelection(Fehlzeit::ZEITRAUM);
				setModusZeitraum();
				break;
			case Fehlzeit::WOCHENTAG:
				ch_wochentag->SetSelection(f.wochentag);
				tc_beginn->SetValue(f.beginn);
				tc_ende->SetValue(f.ende);
				ch_modus->SetSelection(Fehlzeit::WOCHENTAG);
				setModusWochentag();
				break;
			case Fehlzeit::EINZELTERMIN:
				ch_termin->SetSelection(f.einzeltermin->_id);
				ch_modus->SetSelection(2);
				setModusTermin();
				break;
			default:
				ch_termin->SetSelection(app->list_einzeltermin.size() + f.serientermin->_id);
				ch_modus->SetSelection(2);
				setModusTermin();
		}
	} else {
		setModusZeitraum();
	}
}

void FehlzeitDialog::setModusZeitraum() {
	st_termin->Hide();
	ch_termin->Hide();
	st_wochentag->Hide();
	ch_wochentag->Hide();
	st_datum_beginn->Show();
	dc_beginn->Show();
	st_beginn_wday->Show();
	st_datum_ende->Show();
	dc_ende->Show();
	st_ende_wday->Show();
	st_zeit_beginn->Hide();
	tc_beginn->Hide();
	st_zeit_ende->Hide();
	tc_ende->Hide();
	gridsizer->Layout();
}

void FehlzeitDialog::setModusWochentag() {
	st_termin->Hide();
	ch_termin->Hide();
	st_wochentag->Show();
	ch_wochentag->Show();
	st_datum_beginn->Hide();
	dc_beginn->Hide();
	st_beginn_wday->Hide();
	st_datum_ende->Hide();
	dc_ende->Hide();
	st_ende_wday->Hide();
	st_zeit_beginn->Show();
	tc_beginn->Show();
	st_zeit_ende->Show();
	tc_ende->Show();
	gridsizer->Layout();
}

void FehlzeitDialog::setModusTermin() {
	st_termin->Show();
	ch_termin->Show();
	st_wochentag->Hide();
	ch_wochentag->Hide();
	st_datum_beginn->Hide();
	dc_beginn->Hide();
	st_beginn_wday->Hide();
	st_datum_ende->Hide();
	dc_ende->Hide();
	st_ende_wday->Hide();
	st_zeit_beginn->Hide();
	tc_beginn->Hide();
	st_zeit_ende->Hide();
	tc_ende->Hide();
	gridsizer->Layout();
}

BEGIN_EVENT_TABLE(FehlzeitDialog, wxDialog)
EVT_CHOICE(R::ID_CH, FehlzeitDialog::onChModus)
EVT_BUTTON(R::ID_BT_OK, FehlzeitDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, FehlzeitDialog::onBtCancel)
EVT_DATE_CHANGED(R::ID_LC, FehlzeitDialog::onDateBeginnChanged)
EVT_DATE_CHANGED(R::ID_LC2, FehlzeitDialog::onDateEndeChanged)
END_EVENT_TABLE()

void FehlzeitDialog::onChModus(wxCommandEvent&) {
	switch (ch_modus->GetSelection()) {
		case Fehlzeit::ZEITRAUM:
			setModusZeitraum();
			break;
		case Fehlzeit::WOCHENTAG:
			setModusWochentag();
			break;
		default:
			setModusTermin();
	}
}

void FehlzeitDialog::onBtOk(wxCommandEvent&) {
	int mini_i = ch_mini->GetSelection();
	if (mini_i == wxNOT_FOUND) {
		wxMessageDialog dialog(this, R::MSG_MINI_SEL_ERR);
		dialog.ShowModal();
		return;
	}
	Fehlzeit* f;
	switch (ch_modus->GetSelection()) {
		case Fehlzeit::ZEITRAUM:
		{
			wxDateTime beginn = dc_beginn->GetValue();
			wxDateTime ende = dc_ende->GetValue();
			if (ende.IsEarlierThan(beginn)) {
				wxMessageDialog dialog(this, R::MSG_DATUM_ORDER);
				dialog.ShowModal();
				return;
			}
			f = new Fehlzeit(app->list_mini.at(mini_i), Util::wxDateTime_to_wxString(dc_beginn->GetValue()), Util::wxDateTime_to_wxString(dc_ende->GetValue()));
			break;
		}
		case Fehlzeit::WOCHENTAG:
		{
			wxString zeit_beginn;
			if (!Util::formatTime(tc_beginn->GetValue(), &zeit_beginn)) {
				wxMessageDialog dialog(this, R::MSG_TIME_BEGINN_ERR);
				dialog.ShowModal();
				return;
			}
			wxString zeit_ende;
			if (!Util::formatTime(tc_ende->GetValue(), &zeit_ende)) {
				wxMessageDialog dialog(this, R::MSG_TIME_ENDE_ERR);
				dialog.ShowModal();
				return;
			}
			f = new Fehlzeit(app->list_mini.at(mini_i), ch_wochentag->GetSelection(), zeit_beginn, zeit_ende);
			break;
		}
		default:
		{
			int termin_i = ch_termin->GetSelection();
			if (termin_i == wxNOT_FOUND) {
				wxMessageDialog dialog(this, R::MSG_TERMIN_SEL_ERR);
				dialog.ShowModal();
				return;
			}
			int einzel_i = app->list_einzeltermin.size();
			if (termin_i < einzel_i) {
				f = new Fehlzeit(app->list_mini.at(mini_i), app->list_einzeltermin.at(termin_i));
			} else {
				f = new Fehlzeit(app->list_mini.at(mini_i), app->list_serientermin.at(termin_i - einzel_i));
			}
		}
	}
	if (edt) {
		if (!app->edtFehlzeit(index, f)) {
			delete f;
			wxMessageDialog dialog(this, R::MSG_FEHLZEIT_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			delete f;
			Close(true);
		}
	} else {
		if (!app->addFehlzeit(f)) {
			delete f;
			wxMessageDialog dialog(this, R::MSG_FEHLZEIT_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			Close(true);
		}
	}
}

void FehlzeitDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}

void FehlzeitDialog::onDateBeginnChanged(wxDateEvent&) {
	st_beginn_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_beginn->GetValue().GetWeekDay()] + wxT(")"));
}

void FehlzeitDialog::onDateEndeChanged(wxDateEvent&) {
	st_ende_wday->SetLabel(wxT("(") + R::WOCHENTAGE[dc_ende->GetValue().GetWeekDay()] + wxT(")"));
}