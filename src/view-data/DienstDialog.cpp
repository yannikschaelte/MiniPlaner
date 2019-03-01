/* 
 * File:   DienstDialog.cpp
 * Author: Yannik
 * 
 * Created on August 19, 2015, 1:25 PM
 */

#include "DienstDialog.h"
#include "../App.h"
#include "../model-data/Dienst.h"
#include "../Util.h"

DienstDialog::DienstDialog(wxWindow* parent, App* _app)
: wxDialog(parent, R::ID_ANY, R::DIENST_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = false;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

DienstDialog::DienstDialog(wxWindow* parent, App* _app, int _index)
: wxDialog(parent, R::ID_ANY, R::DIENST_DIALOG, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	app = _app;
	edt = true;
	index = _index;
	initComponents();
	R::setSubWindowPosition(parent, this);
}

void DienstDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* sizer_t = new wxFlexGridSizer(1, 2, 0, 0);

	st_name = new wxStaticText(this, R::ID_ANY, R::NAME);
	sizer_t->Add(st_name, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
	tc_name = new wxTextCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	sizer_t->Add(tc_name, 1, wxALL | wxEXPAND, 2);
	if (edt) {
		tc_name->SetValue(app->list_dienst.at(index)->name);
	}
	sizer_t->AddGrowableCol(1, 1);

	sizer->Add(sizer_t, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizer(sizer);
	Fit();
	if (GetSize().GetWidth() < 260) {
		SetSize(260, -1);
	}
}

BEGIN_EVENT_TABLE(DienstDialog, wxDialog)
EVT_BUTTON(R::ID_BT_OK, DienstDialog::onBtOK)
EVT_BUTTON(R::ID_BT_CANCEL, DienstDialog::onBtCancel)
END_EVENT_TABLE()

void DienstDialog::onBtOK(wxCommandEvent&) {
	Dienst* d = new Dienst(Util::rmD(tc_name->GetValue()));
	if (edt) {
		if (!app->edtDienst(index, d)) {
			delete d;
			wxMessageDialog dialog(this, R::MSG_DIENST_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			delete d;
			Close(true);
		}
	} else {
		if (!app->addDienst(d)) {
			delete d;
			wxMessageDialog dialog(this, R::MSG_DIENST_UNIQUE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			Close(true);
		}
	}
}

void DienstDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}