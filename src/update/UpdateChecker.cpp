/* 
 * File:   UpdateChecker.cpp
 * Author: Yannik
 * 
 * Created on October 12, 2015, 12:23 PM
 */

#include "UpdateChecker.h"
#include <wx/utils.h>
#include <wx/sstream.h>
#include "../R.h"

void UpdateChecker::checkUpdate(wxWindow* parent) {
	wxURL url(wxT("https://raw.githubusercontent.com/yannikschaelte/MiniPlaner/master/version.dat"));
	if (url.GetError() == wxURL_NOERR) {
		wxString htmlData;
		wxInputStream* in = url.GetInputStream();
		if (in && in->IsOk()) {
			wxStringOutputStream html_stream(&htmlData);
			in->Read(html_stream);
			if (!htmlData.IsSameAs(R::VERSION_ID)) {
				UpdateDialog dialog(parent);
				dialog.ShowModal();
			}
		}
		delete in;
	}
}

UpdateChecker::UpdateDialog::UpdateDialog(wxWindow* parent)
: wxDialog(parent, R::ID_ANY, wxT("Update-Information"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* st_msg = new wxStaticText(this, R::ID_ANY, wxT("Es ist eine neuere Version des Programms verfügbar."));
	sizer->Add(st_msg, 1, wxEXPAND | wxALL, 10);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel();
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_download = new wxButton(this, R::ID_BT_COMPUTE, wxT("Zum Download"));
	btsizer->Add(bt_download);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::OK);
	btsizer->Add(bt_ok);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

BEGIN_EVENT_TABLE(UpdateChecker::UpdateDialog, wxDialog)
EVT_BUTTON(R::ID_BT_COMPUTE, UpdateDialog::onBtDownload)
EVT_BUTTON(R::ID_BT_OK, UpdateDialog::onBtOk)
END_EVENT_TABLE()


void UpdateChecker::UpdateDialog::onBtDownload(wxCommandEvent&) {
	wxLaunchDefaultBrowser(wxT("https://yannikschaelte.github.io/MiniPlaner/"));
}

void UpdateChecker::UpdateDialog::onBtOk(wxCommandEvent&) {
	Close(true);
}