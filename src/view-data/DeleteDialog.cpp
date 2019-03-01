/* 
 * File:   DeleteDialog.cpp
 * Author: Yannik
 * 
 * Created on October 2, 2015, 4:13 PM
 */

#include "DeleteDialog.h"
#include "../R.h"

DeleteDialog::DeleteDialog(wxWindow* parent, bool* _del)
: wxDialog(parent, R::ID_ANY, R::LOESCHEN_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	del = _del;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_q = new wxStaticText(this, R::ID_ANY, R::Q_LOESCHEN);
	sizer->Add(st_q, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_yes = new wxButton(this, R::ID_BT_OK, R::JA);
	btsizer->Add(bt_yes);
	bt_no = new wxButton(this, R::ID_BT_CANCEL, R::NEIN);
	btsizer->Add(bt_no);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
	R::setSubWindowPosition(parent, this);
}

BEGIN_EVENT_TABLE(DeleteDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, DeleteDialog::onBtYes)
EVT_BUTTON(R::ID_BT_CANCEL, DeleteDialog::onBtNo)
END_EVENT_TABLE()

void DeleteDialog::onBtYes(wxCommandEvent&) {
	*del = true;
	Close(true);
}

void DeleteDialog::onBtNo(wxCommandEvent&) {
	Close(true);
}
