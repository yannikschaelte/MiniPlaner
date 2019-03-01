/* 
 * File:   PlanerSettingsDialog.cpp
 * Author: Yannik
 * 
 * Created on October 7, 2015, 4:16 PM
 */

#include "PlanerSettingsDialog.h"
#include "../R.h"

PlanerSettingsDialog::PlanerSettingsDialog(wxWindow* parent, Planer::Settings* _settings, bool* _edt)
: wxDialog(parent, R::ID_ANY, R::PLANER_SETTINGS_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), settings(_settings), edt(_edt) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizer_t = new wxBoxSizer(wxVERTICAL);
	rb_anrechnen = new wxRadioButton(this, R::ID_ANY, R::FEHLZEITEN_ANRECHNEN, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	sizer_t->Add(rb_anrechnen, 0, wxEXPAND | wxALL, 2);
	rb_kompensieren = new wxRadioButton(this, R::ID_ANY, R::FEHLZEITEN_KOMPENSIEREN);
	sizer_t->Add(rb_kompensieren, 0, wxEXPAND | wxALL, 2);
	sizer_t->AddSpacer(10);
	rb_alg_minimum = new wxRadioButton(this, R::ID_ANY, R::ALG_MINIMUM, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	sizer_t->Add(rb_alg_minimum, 0, wxEXPAND | wxALL, 2);
	rb_alg_chrono = new wxRadioButton(this, R::ID_ANY, R::ALG_CHRONO);
	sizer_t->Add(rb_alg_chrono, 0, wxEXPAND | wxALL, 2);
	sizer->Add(sizer_t, 1, wxALL | wxEXPAND, 5);
	if (settings->modus_fehlzeiten == Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN) {
		rb_anrechnen->SetValue(true);
	} else {
		rb_kompensieren->SetValue(true);
	}
	if (settings->modus_algorithmus == Planer::Settings::MODUS_ALGORITHMUS_MINIMUM) {
		rb_alg_minimum->SetValue(true);
	} else {
		rb_alg_chrono->SetValue(true);
	}

	sizer->AddSpacer(20);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

BEGIN_EVENT_TABLE(PlanerSettingsDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, PlanerSettingsDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, PlanerSettingsDialog::onBtCancel)
END_EVENT_TABLE()


void PlanerSettingsDialog::onBtOk(wxCommandEvent&) {
	settings->modus_fehlzeiten = rb_anrechnen->GetValue() ? Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN : Planer::Settings::MODUS_FEHLZEITEN_KOMPENSIEREN;
	settings->modus_algorithmus = rb_alg_minimum->GetValue() ? Planer::Settings::MODUS_ALGORITHMUS_MINIMUM : Planer::Settings::MODUS_ALGORITHMUS_CHRONOLOGISCH;
	*edt = true;
	Close(true);
}

void PlanerSettingsDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}