/* 
 * File:   SettingsDialog.cpp
 * Author: Yannik
 * 
 * Created on September 30, 2015, 4:14 PM
 */

#include "ExportLayoutDialog.h"
#include "../R.h"

ExportLayoutDialog::ExportLayoutDialog(wxWindow* parent, ExportLayout* _layout)
: wxDialog(parent, R::ID_ANY, R::EXPORT_LAYOUT_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), layout(_layout) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer_config = new wxFlexGridSizer(5, 2, 0, 0);

	wxStaticText* st_title = new wxStaticText(this, R::ID_ANY, R::TITEL);
	sizer_config->Add(st_title, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_title = new wxTextCtrl(this, R::ID_ANY, layout->title);
	sizer_config->Add(tc_title, 1, wxEXPAND | wxALL, 2);

	wxStaticText* st_showDienste = new wxStaticText(this, R::ID_ANY, R::DIENSTE_ZEIGEN);
	sizer_config->Add(st_showDienste, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	cb_showDienste = new wxCheckBox(this, R::ID_ANY, wxT(""));
	cb_showDienste->SetValue(layout->showDienste);
	sizer_config->Add(cb_showDienste, 1, wxALL | wxEXPAND, 2);

	wxStaticText* st_minis = new wxStaticText(this, R::ID_ANY, R::MINIS_LAYOUT);
	sizer_config->Add(st_minis, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	wxBoxSizer* sizer_minis = new wxBoxSizer(wxHORIZONTAL);
	ch_minis = new wxChoice(this, R::ID_CH, wxDefaultPosition, wxDefaultSize, 2, R::MINIS_LAYOUT_MODI);
	ch_minis->Select(layout->modus_minis);
	sizer_minis->Add(ch_minis, 1, wxEXPAND | wxALL, 0);
	sp_minis = new wxSpinCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000000000, layout->n);
	sizer_minis->Add(sp_minis, 0, wxALL, 0);
	if (layout->modus_minis != ExportLayout::MODUS_MINIS_CELLS) {
		sp_minis->Hide();
	}
	sizer_config->Add(sizer_minis, 1, wxALL | wxEXPAND, 2);

	wxStaticText* st_basics = new wxStaticText(this, R::ID_ANY, R::BASICS_LAYOUT);
	sizer_config->Add(st_basics, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_basics = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 2, R::BASICS_LAYOUT_MODI);
	ch_basics->Select(layout->modus_basics);
	sizer_config->Add(ch_basics, 1, wxALL | wxEXPAND, 2);

	wxStaticText* st_namen = new wxStaticText(this, R::ID_ANY, R::NAMEN_LAYOUT);
	sizer_config->Add(st_namen, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	ch_namen = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 4, R::NAMEN_LAYOUT_MODI);
	ch_namen->Select(layout->modus_namen);
	sizer_config->Add(ch_namen, 1, wxALL | wxEXPAND, 2);

	sizer_config->AddGrowableCol(1, 1);
	sizer->Add(sizer_config, 1, wxEXPAND | wxALL, 5);

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

	if (GetSize().GetWidth() < 460) {
		SetSize(460, -1);
	}
}

BEGIN_EVENT_TABLE(ExportLayoutDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, ExportLayoutDialog::onOk)
EVT_BUTTON(R::ID_BT_CANCEL, ExportLayoutDialog::onCancel)
EVT_CHOICE(R::ID_CH, ExportLayoutDialog::onMinis)
END_EVENT_TABLE()

void ExportLayoutDialog::onOk(wxCommandEvent&) {
	layout->title = tc_title->GetValue();
	layout->showDienste = cb_showDienste->GetValue();
	layout->modus_minis = ch_minis->GetSelection();
	if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
		layout->n = sp_minis->GetValue();
	}
	layout->modus_basics = ch_basics->GetSelection();
	layout->modus_namen = ch_namen->GetSelection();
	Close(true);
}

void ExportLayoutDialog::onCancel(wxCommandEvent&) {
	Close(true);
}

void ExportLayoutDialog::onMinis(wxCommandEvent&) {
	if (ch_minis->GetSelection() == ExportLayout::MODUS_MINIS_CELLS) {
		sp_minis->Show();
	} else {
		sp_minis->Hide();
	}
	sizer_config->Layout();
}