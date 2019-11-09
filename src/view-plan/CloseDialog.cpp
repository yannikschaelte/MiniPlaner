/* 
 * File:   CloseDialog.cpp
 * Author: Yannik
 * 
 * Created on October 2, 2015, 3:31 PM
 */

#include "CloseDialog.h"
#include "../R.h"

CloseDialog::CloseDialog(wxWindow* parent, bool* _save, bool* _close) 
: wxDialog(parent, R::ID_ANY, R::SPEICHERN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	save = _save;
	close = _close;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* st_q = new wxStaticText(this, R::ID_ANY, R::Q_SPEICHERN);
	sizer->Add(st_q, 1, wxEXPAND | wxALL, 5);
	
	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_yes = new wxButton(this, R::ID_BT_OK, R::JA);
	btsizer->Add(bt_yes);
	bt_no = new wxButton(this, R::ID_BT_CANCEL, R::NEIN);
	btsizer->Add(bt_no);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

BEGIN_EVENT_TABLE(CloseDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, CloseDialog::onBtYes)
EVT_BUTTON(R::ID_BT_CANCEL, CloseDialog::onBtNo)
END_EVENT_TABLE()
		

void CloseDialog::onBtYes(wxCommandEvent&) {
	*save = true;
	*close = true;
	Close(true);
}

void CloseDialog::onBtNo(wxCommandEvent&) {
	*close = true;
	Close(true);
}