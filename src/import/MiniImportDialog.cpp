/* 
 * File:   MiniImportDialog.cpp
 * Author: Yannik
 * 
 * Created on October 8, 2015, 6:28 PM
 */

#include "MiniImportDialog.h"
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include "../Util.h"
#include "../R.h"
#include "../model-data/Dienst.h"

MiniImportDialog::MiniImportDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini, bool* _edt)
: wxDialog(parent, R::ID_ANY, R::MINI_IMPORT_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
list_mini(_list_mini), edt(_edt) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_head = new wxStaticText(this, R::ID_ANY, R::MINI_CSV_MSG);
	sizer->Add(st_head, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	const wxString SEP = wxT(";");
	wxStaticText* st_cells = new wxStaticText(this, R::ID_ANY, R::NACHNAME + SEP + R::VORNAME + SEP + R::GEBURTSTAG
			+ SEP + R::STRASSE_NR + SEP + R::PLZ_ORT + SEP + R::TEL + SEP + R::MOBILE + SEP + R::EMAIL);
	st_cells->SetFont(st_cells->GetFont().Bold());
	sizer->Add(st_cells, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

	sizer->AddSpacer(5);
	wxBoxSizer* sizer_sep = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* st_sep = new wxStaticText(this, R::ID_ANY, R::SEPARATOR + wxT(": "));
	sizer_sep->Add(st_sep, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
	rb_semicolon = new wxRadioButton(this, R::ID_ANY, R::SEMIKOLON, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	sizer_sep->Add(rb_semicolon, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	rb_comma = new wxRadioButton(this, R::ID_ANY, R::KOMMA);
	sizer_sep->Add(rb_comma, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	rb_tab = new wxRadioButton(this, R::ID_ANY, wxT("Tab"));
	sizer_sep->Add(rb_tab, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	rb_space = new wxRadioButton(this, R::ID_ANY, R::LEERZEICHEN);
	sizer_sep->Add(rb_space, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	rb_other = new wxRadioButton(this, R::ID_ANY, R::ANDERES);
	sizer_sep->Add(rb_other, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	tc_sep = new wxTextCtrl(this, R::ID_ANY, wxT(""));
	sizer_sep->Add(tc_sep, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
	rb_semicolon->SetValue(true);
	sizer->Add(sizer_sep, 0, wxEXPAND | wxALL, 5);

	sizer->AddSpacer(5);
	bt_file = new wxButton(this, R::ID_BT_COMPUTE, R::CSV_DATEI_WAEHLEN);
	sizer->Add(bt_file, 0, wxALL, 5);

	sizer->AddSpacer(5);
	wxStaticText* st_preview = new wxStaticText(this, R::ID_ANY, R::VORSCHAU + wxT(": "));
	sizer->Add(st_preview, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
	wxBoxSizer* sizer_preview = new wxBoxSizer(wxHORIZONTAL);
	lc_minis = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT);
	wxString lc_minis_texts[] = {R::NACHNAME, R::VORNAME, R::GEBURTSTAG, R::STRASSE_NR, R::PLZ_ORT, R::TEL, R::MOBILE, R::EMAIL, R::BEM};
	wxListItem lc_minis_cols[R::MINI_ATTS_NUM - 1];
	for (int i = 0; i < R::MINI_ATTS_NUM - 1; i++) {
		lc_minis_cols[i].SetText(lc_minis_texts[i]);
		lc_minis->InsertColumn(i, lc_minis_cols[i]);
	}
	for (int i = 0; i < R::MINI_ATTS_NUM - 1; i++) {
		lc_minis->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
	sizer_preview->Add(lc_minis, 1, wxEXPAND);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_preview->Add(bt_del, 0, 0);
	sizer->Add(sizer_preview, 1, wxEXPAND | wxALL, 5);

	wxStaticText* st_import_msg = new wxStaticText(this, R::ID_ANY, R::MINI_IMPORT_MSG);
	sizer->Add(st_import_msg, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* btsizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* pl_nn = new wxPanel(this);
	pl_nn->SetSize(30, -1);
	btsizer->Add(pl_nn, 1, wxEXPAND);
	bt_ok = new wxButton(this, R::ID_BT_OK, R::IMPORTIEREN);
	btsizer->Add(bt_ok);
	bt_cancel = new wxButton(this, R::ID_BT_CANCEL, R::CANCEL);
	btsizer->Add(bt_cancel);
	sizer->Add(btsizer, 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
}

void MiniImportDialog::notifyMinis() {
	lc_minis->DeleteAllItems();
	int num_minis = tmp_list.size();
	for (int i = 0; i < num_minis; i++) {
		Messdiener* m = &tmp_list.at(i);
		wxListItem item;
		item.SetId(i);
		lc_minis->InsertItem(item);
		lc_minis->SetItem(i, 0, m->name);
		lc_minis->SetItem(i, 1, m->vorname);
		lc_minis->SetItem(i, 2, m->geburtstag);
		lc_minis->SetItem(i, 3, m->strasse_nr);
		lc_minis->SetItem(i, 4, m->plz_ort);
		lc_minis->SetItem(i, 5, m->tel);
		lc_minis->SetItem(i, 6, m->mobile);
		lc_minis->SetItem(i, 7, m->email);
		lc_minis->SetItem(i, 8, m->bem);
	}
	for (int i = 0; i < R::MINI_ATTS_NUM - 1; i++) {
		lc_minis->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(MiniImportDialog, wxDialog)
EVT_BUTTON(R::ID_BT_COMPUTE, MiniImportDialog::onBtFile)
EVT_BUTTON(R::ID_BT_DEL, MiniImportDialog::onBtDel)
EVT_BUTTON(R::ID_BT_OK, MiniImportDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, MiniImportDialog::onBtCancel)
END_EVENT_TABLE()


void MiniImportDialog::onBtFile(wxCommandEvent&) {
	//delete old
	tmp_list.clear();

	wxFileDialog openFileDialog(this, R::CSV_DATEI_WAEHLEN, wxT(""), wxT(""), wxT("CSV-Dateien (*.csv)|*.csv|Alle (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL) return;
	wxTextFile file(openFileDialog.GetPath());
	if (!file.Exists()) {
		wxMessageDialog dialog(this, R::MSG_FILE_NOT_FOUND, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		dialog.ShowModal();
		return;
	}
	file.Open();
	wxString D;
	if (rb_semicolon->GetValue()) D = wxT(";");
	else if (rb_comma->GetValue()) D = wxT(",");
	else if (rb_tab->GetValue()) D = wxT("\t");
	else if (rb_space->GetValue()) D = wxT(" ");
	else {
		D = tc_sep->GetValue().Mid(0, 1);
		tc_sep->SetValue(D);
	}
	//iterate
	for (wxString line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = wxT(""), vorname = wxT(""), geburtstag = wxT(""), strasse = wxT(""),
				ort = wxT(""), tel = wxT(""), mobile = wxT(""), email = wxT(""), bem = wxT("");
		wxString * items[R::MINI_ATTS_NUM - 1] = {&name, &vorname, &geburtstag, &strasse, &ort, &tel, &mobile, &email, &bem};
		int counter = 0;
		while (zr.HasMoreTokens() && counter < R::MINI_ATTS_NUM - 1) {
			*items[counter++] = Util::rmD(zr.NextToken());
		}
		Util::formatDate(geburtstag, &geburtstag);
		std::vector<Dienst*> dienste; //dummy
		tmp_list.push_back(Messdiener(name, vorname, dienste, geburtstag, strasse, ort, tel, mobile, email, bem));
	}
	notifyMinis();
	file.Close();
}

void MiniImportDialog::onBtDel(wxCommandEvent&) {
	int i = -1;
	bool didErase = false;
	int counter = 0;
	for (;;) {
		i = lc_minis->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		tmp_list.erase(tmp_list.begin() + (i - counter++));
		didErase = true;
	}
	if (didErase) notifyMinis();
}

void MiniImportDialog::onBtOk(wxCommandEvent&) {
	*edt = true;
	for (std::vector<Messdiener>::iterator iter_m = tmp_list.begin(); iter_m != tmp_list.end(); iter_m++) {
		list_mini->push_back(new Messdiener(*iter_m));
	}
	Close(true);
}

void MiniImportDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}
