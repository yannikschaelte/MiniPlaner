/* 
 * File:   MiniExportDialog.cpp
 * Author: Yannik
 * 
 * Created on October 2, 2015, 7:46 PM
 */

#include "../Paths.h"
#include "MiniExportDialog.h"
#include <wx/statline.h>
#include "ExportOutput.h"

MiniExportDialog::MiniExportDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini)
: wxDialog(parent, R::ID_ANY, R::MINI_EXPORT_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
	list_mini = _list_mini;
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizer_l = new wxBoxSizer(wxVERTICAL);
	wxStaticText* st_spalten = new wxStaticText(this, R::ID_ANY, R::SPALTEN);
	sizer_l->Add(st_spalten, 0, wxEXPAND | wxALL, 2);
	cb_num = new wxCheckBox(this, R::ID_ANY, wxT("(") + R::NUM + wxT(")"));
	cb_num->SetValue(false);
	sizer_l->Add(cb_num, 0, wxEXPAND | wxALL, 2);
	for (int i = 0; i < R::MINI_ATTS_NUM; i++) {
		cb_cols[i] = new wxCheckBox(this, R::ID_ANY, R::MINI_ATTS[i]);
		if (i == 2 || i == 9) cb_cols[i]->SetValue(false);
		else cb_cols[i]->SetValue(true);
		sizer_l->Add(cb_cols[i], 0, wxEXPAND | wxALL, 2);
	}
	sizer->Add(sizer_l, 1, wxEXPAND | wxALL, 5);

	sizer->Add(new wxStaticLine(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL), 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	rb_file = new wxRadioButton(this, R::ID_ANY, R::DATEI_AUSGABE, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	sizer_r->Add(rb_file, 0, wxEXPAND, 0);
	rb_clipboard = new wxRadioButton(this, R::ID_ANY, R::CLIPBOARD_AUSGABE);
	sizer_r->Add(rb_clipboard, 0, 0, 0);
	sizer_r->AddSpacer(10);
	bt_xlsx = new wxButton(this, R::ID_BT_DEL2, wxT("Excel (.xlsx)"));
	sizer_r->Add(bt_xlsx, 0, wxEXPAND, 0);
	bt_csv = new wxButton(this, R::ID_BT_DEL, wxT("CSV"));
	sizer_r->Add(bt_csv, 0, wxEXPAND, 0);
	bt_html = new wxButton(this, R::ID_BT_ADD2, wxT("HTML"));
	sizer_r->Add(bt_html, 0, wxEXPAND, 0);
	sizer->Add(sizer_r, 0, wxEXPAND | wxALL, 5);

	SetSizerAndFit(sizer);
}

wxString MiniExportDialog::createHTML() {
	wxString page = wxT("<!DOCTYPE html>\n<html>\n	<head>\n		<title>") + R::MESSDIENERLISTE + wxT("</title>"
			"\n		<meta charset=\"utf-8\"/>"
			"\n		<meta name=\"description\" content=\"MiniPlaner Messdienerliste\"/>"
			"\n		<meta name=\"keywords\" content=\"MiniPlaner, Messdienerliste\"/>"
			"\n		<meta name=\"author\" content=\"Yannik Schälte\"/>"
			"\n		<style>"
			"\n		td {padding: 3px;}"
			"\n		.phead {font-weight: bold;}"
			"\n		.num {text-align: right;}"
			"\n		</style>"
			"\n	</head>");
	page += wxT("\n	<body>\n		<table>\n			<tr>");
	//header
	if (cb_num->GetValue()) page += wxT("<td class=\"phead\"></td>");
	for (int i = 0; i < R::MINI_ATTS_NUM; i++) {
		if (cb_cols[i]->GetValue()) {
			page += wxT("<td class=\"phead\">") + R::MINI_ATTS[i] + wxT("</td>");
		}
	}
	page += wxT("</tr>");
	//list
	int num_minis = list_mini->size();
	for (int i = 0; i < num_minis; i++) {
		Messdiener* m = list_mini->at(i);
		page += wxT("\n			<tr>");
		if (cb_num->GetValue()) page += wxT("<td class=\"num\">") + wxString::Format(wxT("%i"), i + 1) + wxT("</td>");
		if (cb_cols[0]->GetValue()) page += wxT("<td>") + m->name + wxT("</td>");
		if (cb_cols[1]->GetValue()) page += wxT("<td>") + m->vorname + wxT("</td>");
		if (cb_cols[2]->GetValue()) page += wxT("<td>") + Messdiener::printDienste(m) + wxT("</td>");
		if (cb_cols[3]->GetValue()) page += wxT("<td>&#8203;") + m->geburtstag + wxT("</td>");
		if (cb_cols[4]->GetValue()) page += wxT("<td>") + m->strasse_nr + wxT("</td>");
		if (cb_cols[5]->GetValue()) page += wxT("<td>") + m->plz_ort + wxT("</td>");
		if (cb_cols[6]->GetValue()) page += wxT("<td>&#8203;") + m->tel + wxT("</td>");
		if (cb_cols[7]->GetValue()) page += wxT("<td>&#8203;") + m->mobile + wxT("</td>");
		if (cb_cols[8]->GetValue()) page += wxT("<td>") + m->email + wxT("</td>");
		if (cb_cols[9]->GetValue()) page += wxT("<td>&#8203;") + m->bem + wxT("</td>");
		page += wxT("</tr>");
	}
	page += wxT("\n		</table>\n	</body>\n</html>");
	return page;
}

wxString MiniExportDialog::createCSV() {
	wxString page = wxT("sep=") + D + N;
	//header
	if(cb_num->GetValue()) page += D;
	for (int i = 0; i < R::MINI_ATTS_NUM; i++) {
		if (cb_cols[i]->GetValue()) {
			page += R::MINI_ATTS[i] + D;
		}
	}
	page += N;
	//list
	int num_minis = list_mini->size();
	for (int i = 0; i < num_minis; i++) {
		Messdiener* m = list_mini->at(i);
		if (cb_num->GetValue()) page += wxString::Format(wxT("%i"), i + 1) + D;
		if (cb_cols[0]->GetValue()) page += m->name + D;
		if (cb_cols[1]->GetValue()) page += m->vorname + D;
		if (cb_cols[2]->GetValue()) page += Messdiener::printDienste(m) + D;
		if (cb_cols[3]->GetValue()) page += m->geburtstag + D;
		if (cb_cols[4]->GetValue()) page += m->strasse_nr + D;
		if (cb_cols[5]->GetValue()) page += m->plz_ort + D;
		if (cb_cols[6]->GetValue()) page += m->tel + D;
		if (cb_cols[7]->GetValue()) page += m->mobile + D;
		if (cb_cols[8]->GetValue()) page += m->email + D;
		if (cb_cols[9]->GetValue()) page += m->bem + D;
		page += N;
	}
	return page;
}

BEGIN_EVENT_TABLE(MiniExportDialog, wxDialog)
EVT_BUTTON(R::ID_BT_ADD2, MiniExportDialog::onBtHTML)
EVT_BUTTON(R::ID_BT_DEL, MiniExportDialog::onBtCSV)
EVT_BUTTON(R::ID_BT_DEL2, MiniExportDialog::onBtXlsx)
END_EVENT_TABLE()

void MiniExportDialog::onBtHTML(wxCommandEvent&) {
	wxString text = createHTML();
	ExportOutput::save(this, rb_file->GetValue(), R::SPEICHERN_HTML, R::MESSDIENERLISTE_SH + wxT(".html"), text);
}

void MiniExportDialog::onBtCSV(wxCommandEvent&) {
	wxString text = createCSV();
	ExportOutput::save(this, rb_file->GetValue(), R::SPEICHERN_CSV, R::MESSDIENERLISTE_SH + wxT(".csv"), text);
}

void MiniExportDialog::onBtXlsx(wxCommandEvent&) {
	wxString text = createCSV();
	ExportOutput::save(this, rb_file->GetValue(), R::SPEICHERN_XLSX, R::MESSDIENERLISTE_SH + wxT(".xlsx"), text);
}
