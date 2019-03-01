/* 
 * File:   MiniExtrasDialog.cpp
 * Author: Yannik
 * 
 * Created on February 11, 2016, 9:39 PM
 */

#include "MiniExtrasDialog.h"
#include <wx/clipbrd.h>
#include "../R.h"

MiniExtrasDialog::MiniExtrasDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini)
: wxDialog(parent, R::ID_ANY, R::MINI_EXTRAS_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	list_mini = _list_mini;

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* sizer_1 = new wxFlexGridSizer(2, 2, 0, 0);
	
	wxButton* bt_email = new wxButton(this, R::ID_BT_ADD, R::EMAILS);
	sizer_1->Add(bt_email, 0, wxALL, 2);
	wxStaticText* st_email = new wxStaticText(this, R::ID_ANY, R::KOPIERTEMAILS);
	sizer_1->Add(st_email, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	
	wxButton* bt_adressen = new wxButton(this, R::ID_BT_DEL, R::ADRESSEN);
	sizer_1->Add(bt_adressen, 0, wxALL, 2);
	wxStaticText* st_adressen = new wxStaticText(this, R::ID_ANY, R::KOPIERTADRESSEN);
	sizer_1->Add(st_adressen, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	
	sizer->Add(sizer_1, 0, wxALL, 2);

	textbox = new wxTextCtrl(this, R::ID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	sizer->Add(textbox, 1, wxALL | wxEXPAND, 2);
	SetSizerAndFit(sizer);
	if (GetSize().GetHeight() < 210) {
		SetSize(-1, 210);
	}
}

void MiniExtrasDialog::createEmails() {
	successString.Empty();
	failureString.Empty();
	for (std::vector<Messdiener*>::iterator iter = list_mini->begin(); iter != list_mini->end(); iter++) {
		Messdiener* mini = *iter;
		if (mini->email.IsEmpty()) {
			failureString += mini->name + wxT(", ") + mini->vorname + wxT("\n");
		} else {
			successString += mini->email + wxT("; ");
		}
	}
}

void MiniExtrasDialog::createAddresses() {
	successString.Empty();
	failureString.Empty();
	for (std::vector<Messdiener*>::iterator iter = list_mini->begin(); iter != list_mini->end(); iter++) {
		Messdiener* mini = *iter;
		if (mini->plz_ort.IsEmpty() && mini->strasse_nr.IsEmpty()) {
			failureString += mini->name + wxT(", ") + mini->vorname + wxT("\n");
		} else {
			successString += mini->vorname + wxT(" ") + mini->name + wxT("\n") + mini->strasse_nr + wxT("\n") + mini->plz_ort + wxT("\n\n");
		}
	}
}

BEGIN_EVENT_TABLE(MiniExtrasDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD, MiniExtrasDialog::onBtEmail)
EVT_BUTTON(R::ID_BT_DEL, MiniExtrasDialog::onBtAddresses)
END_EVENT_TABLE()

void MiniExtrasDialog::onBtEmail(wxCommandEvent&) {
	createEmails();
	if (wxTheClipboard->Open()) {
		wxTheClipboard->SetData(new wxTextDataObject(successString));
		wxTheClipboard->Close();
		wxString msg = R::KOPIERTEMAILSFERTIG;
		if (!failureString.IsEmpty()) {
			msg += R::KOPIERTWARNICHTMOEGLICH + failureString;
		}
		textbox->SetValue(msg);
	}
}

void MiniExtrasDialog::onBtAddresses(wxCommandEvent&) {
	createAddresses();
	if (wxTheClipboard->Open()) {
		wxTheClipboard->SetData(new wxTextDataObject(successString));
		wxTheClipboard->Close();
		wxString msg = R::KOPIERTADRESSENFERTIG;
		if (!failureString.IsEmpty()) {
			msg += R::KOPIERTWARNICHTMOEGLICH + failureString;
		}
		textbox->SetValue(msg);
	}
}