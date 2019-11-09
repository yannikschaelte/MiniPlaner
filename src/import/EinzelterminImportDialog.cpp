/* 
 * File:   EinzelterminImportDialog.cpp
 * Author: Yannik
 * 
 * Created on August 29, 2016, 9:42 PM
 */

#include "EinzelterminImportDialog.h"
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include "../Util.h"
#include "../R.h"

EinzelterminImportDialog::EinzelterminImportDialog(wxWindow* parent, std::vector<Einzeltermin*>* _list_einzel, bool* _edt, std::vector<Dienst*>* _list_dienst)
: wxDialog(parent, R::ID_ANY, R::EINZELTERMIN_IMPORT_DIALOG, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
list_einzel(_list_einzel), edt(_edt), list_dienst(_list_dienst) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_head = new wxStaticText(this, R::ID_ANY, R::MINI_CSV_MSG);
	sizer->Add(st_head, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	const wxString SEP = wxT(";");
	wxStaticText* st_cells = new wxStaticText(this, R::ID_ANY, R::NAME + SEP + R::ORT + SEP + R::DATUM
			+ SEP + R::ZEIT + SEP + R::ANZAHL + SEP + R::BEM);
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
	wxFlexGridSizer* sizer_dienst = new wxFlexGridSizer(2, 2, 0, 0);
	int num = list_dienst->size();
	wxString dienste_s[num];
	for (int i = 0; i < num; i++) {
		dienste_s[i] = list_dienst->at(i)->name;
	}
	wxStaticText* st_dienst = new wxStaticText(this, R::ID_ANY, wxT("Std.-") + R::DIENST);
	sizer_dienst->Add(st_dienst, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
	ch_dienst = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, num, dienste_s);
	ch_dienst->SetLabel(R::DIENST);
	ch_dienst->SetSelection(0); //seems to work with empty lists
	sizer_dienst->Add(ch_dienst, 0, wxEXPAND | wxALL, 2);
	wxStaticText* st_anzahl = new wxStaticText(this, R::ID_ANY, wxT("Std.-") + R::ANZAHL);
	sizer_dienst->Add(st_anzahl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
	sp_anzahl = new wxSpinCtrl(this, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000000, 1);
	sizer_dienst->Add(sp_anzahl, 0, wxEXPAND | wxALL, 2);
	sizer->Add(sizer_dienst, 0, wxALL, 5);

	sizer->AddSpacer(5);
	bt_file = new wxButton(this, R::ID_BT_COMPUTE, R::CSV_DATEI_WAEHLEN);
	sizer->Add(bt_file, 0, wxALL, 5);

	sizer->AddSpacer(5);
	wxStaticText* st_preview = new wxStaticText(this, R::ID_ANY, R::VORSCHAU + wxT(": "));
	sizer->Add(st_preview, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
	wxBoxSizer* sizer_preview = new wxBoxSizer(wxHORIZONTAL);
	lc_termine = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT);
	wxListItem lc_termine_cols[R::TEINZEL_NUM];
	for (int i = 0; i < R::TEINZEL_NUM; i++) {
		lc_termine_cols[i].SetText(R::TEINZEL_ATTS[i]);
		lc_termine->InsertColumn(i, lc_termine_cols[i]);
	}
	for (int i = 0; i < R::TEINZEL_NUM; i++) {
		lc_termine->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
	sizer_preview->Add(lc_termine, 1, wxEXPAND);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_preview->Add(bt_del, 0, 0);
	sizer->Add(sizer_preview, 1, wxEXPAND | wxALL, 5);

	wxStaticText* st_import_msg = new wxStaticText(this, R::ID_ANY, R::EINZELTERMIN_IMPORT_MSG);
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

void EinzelterminImportDialog::notifyTermine() {
	lc_termine->DeleteAllItems();
	int num_termine = tmp_list.size();
	for (int i = 0; i < num_termine; i++) {
		Einzeltermin* t = &tmp_list.at(i);
		wxListItem item;
		item.SetId(i);
		lc_termine->InsertItem(item);
		lc_termine->SetItem(i, 0, t->name);
		lc_termine->SetItem(i, 1, t->ort);
		lc_termine->SetItem(i, 2, t->datum + wxT(" (") + R::WOCHENTAGE[Util::wxString_to_wxDateTime(t->datum).GetWeekDay()] + wxT(")"));
		lc_termine->SetItem(i, 3, t->zeit_beginn);
		lc_termine->SetItem(i, 4, Einzeltermin::printDienste(t));
		lc_termine->SetItem(i, 5, t->bem);
	}
	for (int i = 0; i < R::TEINZEL_NUM; i++) {
		lc_termine->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

BEGIN_EVENT_TABLE(EinzelterminImportDialog, wxDialog)
EVT_BUTTON(R::ID_BT_COMPUTE, EinzelterminImportDialog::onBtFile)
EVT_BUTTON(R::ID_BT_DEL, EinzelterminImportDialog::onBtDel)
EVT_BUTTON(R::ID_BT_OK, EinzelterminImportDialog::onBtOk)
EVT_BUTTON(R::ID_BT_CANCEL, EinzelterminImportDialog::onBtCancel)
END_EVENT_TABLE()


void EinzelterminImportDialog::onBtFile(wxCommandEvent&) {
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
	//delimiter
	wxString D;
	if (rb_semicolon->GetValue()) D = wxT(";");
	else if (rb_comma->GetValue()) D = wxT(",");
	else if (rb_tab->GetValue()) D = wxT("\t");
	else if (rb_space->GetValue()) D = wxT(" ");
	else {
		D = tc_sep->GetValue().Mid(0, 1);
		tc_sep->SetValue(D);
	}
	//std dienst
	Dienst* dienst = list_dienst->at(ch_dienst->GetSelection());
	int std_anzahl = sp_anzahl->GetValue();
	//iterate
	int counter_termin = 0;
	wxString failedLines = wxT("");
	wxString lastDate = wxT(""); //sometimes not mentioned if same as previous one
	for (wxString line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()) {
		counter_termin++;
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = wxT(""), ort = wxT(""), datum_s = wxT(""), zeit_s = wxT(""), anzahl_s = wxT(""), bem = wxT("");
		wxString * items[6] = {&name, &ort, &datum_s, &zeit_s, &anzahl_s, &bem};
		int counter = 0;
		while (zr.HasMoreTokens() && counter < 6) {
			*items[counter++] = Util::rmD(zr.NextToken());
		}
		//retrieve date
		wxString datum = wxT("");
		if (datum_s.IsSameAs(wxT("")) && !lastDate.IsSameAs(wxT(""))) datum = lastDate;
		else if (!Util::formatDate(datum_s, &datum)) {
			wxStringTokenizer zr(datum_s, wxT(" "));
			wxString d2 = zr.NextToken();
			while (zr.HasMoreTokens()) d2 = zr.GetNextToken();
			//form ANYTHING dd.mm.yyyy
			if (!Util::formatDate(d2, &datum)) {
				wxStringTokenizer zr(d2, wxT("."));
				if (zr.CountTokens() == 2) {
					long day, month_i;
					bool day_b = zr.NextToken().ToLong(&day, 10);
					bool month_b = zr.NextToken().ToLong(&month_i, 10);
					if (day_b && month_b && day >= 1 && month_i >= 1 && day <= 31 && month_i <= 12) {
						wxDateTime::Month month = wxDateTime::Month(month_i - 1);
						wxDateTime today = wxDateTime::Today();
						int year = today.GetYear();
						if (month < today.GetMonth() || (month <= today.GetMonth() && day < today.GetDay())) year++;
						if (day <= wxDateTime::GetNumberOfDays(month, year)) {
							wxDateTime date(day, month, year);
							if (date.IsValid()) {
								datum = Util::wxDateTime_to_wxString(date);
								lastDate = datum;
							}
						}
					}
				}
			}
		}
		if (datum.IsSameAs(wxT(""))) failedLines += wxString::Format(wxT("%i (") + R::DATUM + wxT(")"), counter_termin) + wxT("\n");
		else {
			wxString zeit;
			if (!Util::formatTime(zeit_s, &zeit)) failedLines += wxString::Format(wxT("%i (") + R::ZEIT + wxT(")"), counter_termin) + wxT("\n");
			else {
				long anzahl;
				if (anzahl_s.IsSameAs(wxT("-"))) anzahl = 0;
				else if (!anzahl_s.ToLong(&anzahl, 10)) anzahl = std_anzahl;
				std::vector<std::pair<Dienst*, int> > dienste;
				if (anzahl != 0) {
					dienste.push_back(std::make_pair(dienst, anzahl));
				}
				tmp_list.push_back(Einzeltermin(name, ort, datum, zeit, dienste, bem));
			}
		}
	}
	//evtl. fehlerhafte Zeilen
	if (failedLines.length() > 0) {
		wxMessageDialog dialog(this, R::MSG_RETRIEVE_NOT_POSSIBLE + wxT("\n") + failedLines, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		dialog.ShowModal();
	}
	notifyTermine();
	file.Close();
}

void EinzelterminImportDialog::onBtDel(wxCommandEvent&) {
	int i = -1;
	bool didErase = false;
	int counter = 0;
	for (;;) {
		i = lc_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		tmp_list.erase(tmp_list.begin() + (i - counter++));
		didErase = true;
	}
	if (didErase) notifyTermine();
}

void EinzelterminImportDialog::onBtOk(wxCommandEvent&) {
	*edt = true;
	for (std::vector<Einzeltermin>::iterator iter_t = tmp_list.begin(); iter_t != tmp_list.end(); iter_t++) {
		list_einzel->push_back(new Einzeltermin(*iter_t));
	}
	Close(true);
}

void EinzelterminImportDialog::onBtCancel(wxCommandEvent&) {
	Close(true);
}