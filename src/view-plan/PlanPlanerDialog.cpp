/* 
 * File:   PlanPlanerDialog.cpp
 * Author: Yannik
 * 
 * Created on September 11, 2015, 9:38 AM
 */

#include "PlanPlanerDialog.h"
#include <wx/clipbrd.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/statline.h>
#include <algorithm>
#include "../controller-plan/PlanerController.h"
#include "../R.h"
#include "../Util.h"
#include "CloseDialog.h"
#include "../view-data/DeleteDialog.h"
#include "PlanerSettingsDialog.h"
#include "../export/ExportLayoutDialog.h"
#include "../export/HTMLExport.h"
#include "../export/CSVExport.h"
#include "../export/ExcelXMLExport.h"
#include "../img/minis.xpm"

PlanPlanerDialog::PlanPlanerDialog(wxWindow* parent, Planer* planer)
: wxFrame(parent, R::ID_ANY, R::PLAN_DIALOG + wxT(": ") + planer->printShort(), wxDefaultPosition, wxDefaultSize,
wxCAPTION | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxCLOSE_BOX) {
	single_instance_checker = new wxSingleInstanceChecker;
	single_instance_checker->Create(planer->getDir());
	if (single_instance_checker->IsAnotherRunning()) {
		delete single_instance_checker;
		Destroy();
		return;
	}
	controller = new PlanerController(planer, this);
	wxFrame::SetIcon(wxICON(minis));
	initComponents();
	wxDisplay display;
	wxRect screen = display.GetGeometry();
	int screen_width = screen.GetWidth();
	int screen_height = screen.GetHeight();
	int width = screen_width * 4 / 5;
	int height = screen_height * 4 / 5;
	wxFrame::SetSize(screen_width - width, 0, width, height);
	Show(true);
}

void PlanPlanerDialog::initComponents() {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxSplitterWindow* splitter_window = new wxSplitterWindow(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	splitter_window->SetSashGravity(0.25);
	splitter_window->SetMinimumPaneSize(20);

	//LINKS
	wxNotebook* nb_l = new wxNotebook(splitter_window, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
	//Minis
	lv_minis = new wxListView(nb_l, R::ID_LC, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	nb_l->InsertPage(0, lv_minis, R::MINIS);
	wxString mini_cols_s[5] = {wxT(""), R::NACHNAME, R::VORNAME, R::DIENSTE, R::EINSAETZE};
	for (int i = 0; i < 5; i++) {
		if (i == 0 || i == 4) {
			lv_minis->InsertColumn(i, mini_cols_s[i], wxLIST_FORMAT_RIGHT);
		} else {
			lv_minis->InsertColumn(i, mini_cols_s[i], wxLIST_FORMAT_LEFT);
		}
	}
	notifyMinis();
	//MGruppen
	lv_mgruppen = new wxListView(nb_l, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	nb_l->InsertPage(1, lv_mgruppen, R::MGRUPPEN);
	wxListItem cols_mg[3];
	cols_mg[0].SetText(wxT(""));
	cols_mg[1].SetText(R::MODUS);
	cols_mg[2].SetText(R::GRUPPE);
	lv_mgruppen->InsertColumn(0, cols_mg[0]);
	lv_mgruppen->InsertColumn(1, cols_mg[1]);
	lv_mgruppen->InsertColumn(2, cols_mg[2]);
	notifyMGruppen();
	//Termine
	wxPanel* pl_termine = new wxPanel(nb_l, R::ID_ANY);
	wxBoxSizer* sizer_termine = new wxBoxSizer(wxVERTICAL);
	lv_termine = new wxListView(pl_termine, R::ID_CH, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	wxListItem cols[R::TEINZEL_NUM + 1];
	cols[0].SetText(wxT(""));
	lv_termine->InsertColumn(0, cols[0]);
	for (int i = 1; i < R::TEINZEL_NUM + 1; i++) {
		cols[i].SetText(R::TEINZEL_ATTS[i - 1]);
		lv_termine->InsertColumn(i, cols[i]);
	}
	sizer_termine->Add(lv_termine, 1, wxEXPAND | wxALL, 0);
	wxBoxSizer* sizer_termine_bts = new wxBoxSizer(wxHORIZONTAL);
	sizer_termine_bts->Add(new wxPanel(), 1, wxEXPAND, 0);
	bt_termine_edt = new wxButton(pl_termine, R::ID_EXPORT, R::EDT);
	sizer_termine_bts->Add(bt_termine_edt, 0, 0, 0);
	bt_termine_del = new wxButton(pl_termine, R::ID_IMPORT, R::DEL);
	sizer_termine_bts->Add(bt_termine_del, 0, 0, 0);
	sizer_termine->Add(sizer_termine_bts, 0, wxEXPAND, 0);
	pl_termine->SetSizer(sizer_termine);
	nb_l->InsertPage(2, pl_termine, R::TERMINE);
	notifyTermine();
	//TGruppen
	lv_tgruppen = new wxListView(nb_l, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	nb_l->InsertPage(3, lv_tgruppen, R::TGRUPPEN);
	wxListItem cols_pg[2];
	cols_pg[0].SetText(wxT(""));
	cols_pg[1].SetText(R::TGRUPPE);
	lv_tgruppen->InsertColumn(0, cols_pg[0]);
	lv_tgruppen->InsertColumn(1, cols_pg[1]);
	notifyTGruppen();

	//MITTE
	nb_termine = new wxNotebook(splitter_window, R::ID_LB, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

	//Eingabemaske
	pl_maske = new wxScrolled<wxPanel>(nb_termine, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	sizer_maske = new wxGridBagSizer(5, 5);
	wxBoxSizer* sizer_maske_wrap = new wxBoxSizer(wxVERTICAL);
	sizer_maske_wrap->Add(sizer_maske, 1, wxEXPAND | wxALL, 10);
	pl_maske->SetSizer(sizer_maske_wrap);
	pl_maske->SetBackgroundColour(*wxWHITE);
	nb_termine->InsertPage(0, pl_maske, R::MASKE);

	//Vorschau
	html_preview = new wxHtmlWindow(nb_termine, R::ID_ANY);
	initPreview();
	notifyMaskeAndPreview();
	nb_termine->InsertPage(1, html_preview, R::VORSCHAU);

	nb_termine->SetSelection(1);

	splitter_window->SplitVertically(nb_l, nb_termine);
	sizer->Add(splitter_window, 1, wxEXPAND | wxALL, 0);

	//RECHTS
	wxPanel* pl_r = new wxPanel(this, R::ID_ANY);
	wxBoxSizer* sizer_r = new wxBoxSizer(wxVERTICAL);
	sizer_r->Add(new wxStaticText(pl_r, R::ID_ANY, R::DATEN), 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
	bt_options = new wxButton(pl_r, R::ID_BT_EDT2, R::EINSTELLUNGEN);
	sizer_r->Add(bt_options, 0, wxEXPAND, 0);
	bt_compute = new wxButton(pl_r, R::ID_BT_COMPUTE, R::AUTOMATISCH);
	bt_compute->SetBackgroundColour(wxColour(225, 255, 164, 255));
	sizer_r->Add(bt_compute, 0, wxEXPAND, 0);
	bt_stop = new wxButton(pl_r, R::ID_BT_STOP, R::STOPPEN);
	bt_stop->Disable();
	sizer_r->Add(bt_stop, 0, wxEXPAND, 0);
	wxBoxSizer* sz_unredo = new wxBoxSizer(wxHORIZONTAL);
	bt_undo = new wxButton(pl_r, R::ID_UNDO, wxT("\x21A9"));
	bt_undo->Disable();
	sz_unredo->Add(bt_undo, 1, wxEXPAND | wxALL, 0);
	bt_redo = new wxButton(pl_r, R::ID_REDO, wxT("\x21AA"));
	bt_redo->Disable();
	sz_unredo->Add(bt_redo, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(sz_unredo, 0, wxEXPAND, 0);
	bt_clear = new wxButton(pl_r, R::ID_BT_DEL, R::LEEREN);
	sizer_r->Add(bt_clear, 0, wxEXPAND, 0);
	bt_save = new wxButton(pl_r, R::ID_BT_OK, R::SPEICHERN);
	bt_save->Disable();
	sizer_r->Add(bt_save, 0, wxEXPAND, 0);

	sizer_r->AddSpacer(10);
	sizer_r->Add(new wxStaticLine(pl_r, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);
	sizer_r->AddSpacer(10);

	sizer_r->Add(new wxStaticText(pl_r, R::ID_ANY, R::EXPORT), 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
	bt_settings = new wxButton(pl_r, R::ID_BT_ADD, R::LAYOUT);
	sizer_r->Add(bt_settings, 0, wxEXPAND, 0);
	sizer_r->AddSpacer(10);
	rb_file = new wxRadioButton(pl_r, R::ID_ANY, R::DATEI_AUSGABE, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	sizer_r->Add(rb_file, 0, wxEXPAND, 0);
	rb_clipboard = new wxRadioButton(pl_r, R::ID_ANY, R::CLIPBOARD_AUSGABE);
	sizer_r->Add(rb_clipboard, 0, 0, 0);
	sizer_r->AddSpacer(10);
	bt_html = new wxButton(pl_r, R::ID_BT_ADD2, wxT("HTML"));
	sizer_r->Add(bt_html, 0, wxEXPAND, 0);
	bt_csv = new wxButton(pl_r, R::ID_BT_EDT, wxT("Tab-CSV"));
	sizer_r->Add(bt_csv, 0, wxEXPAND, 0);
	bt_excel_xml = new wxButton(pl_r, R::ID_BT_DEL2, wxT("Excel-XML"));
	sizer_r->Add(bt_excel_xml, 0, wxEXPAND, 0);

	pl_r->SetSizer(sizer_r);

	sizer->Add(pl_r, 0, wxEXPAND, 0);

	SetSizerAndFit(sizer);

	//Threads
	Bind(wxEVT_THREAD, &PlanPlanerDialog::onThreadDone, this);
}

void PlanPlanerDialog::initPreview() {
	layout.title = R::MESSDIENERPLAN + wxT(" ") + Util::wxDateTime_to_wxString(controller->planer->datum_beginn) + wxT(" - ")
			+ Util::wxDateTime_to_wxString(controller->planer->datum_ende);
	layout.showDienste = true;
	layout.modus_minis = ExportLayout::MODUS_MINIS_CELLS;
	layout.n = 2;
	layout.modus_basics = ExportLayout::MODUS_BASICS_LEFT;
	layout.modus_namen = ExportLayout::MODUS_NAMEN_VORNAME_NACHNAME;
}

void PlanPlanerDialog::initMaske() {
	pl_maske->Hide();
	int col = 0;
	for (std::vector<PTermin*>::iterator iter_t = controller->planer->list_termin.begin(); iter_t != controller->planer->list_termin.end(); iter_t++) {
		std::vector<std::vector<wxStaticText*> > tview_list_termin;
		std::vector<std::vector<wxPanel*> > tview_list_termin_pl;
		sizer_maske->Add(new wxStaticText(pl_maske, R::ID_ANY, wxString::Format(wxT("%i  "), (**iter_t)._id + 1)), wxGBPosition(col, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
		wxStaticText* st_name = new wxStaticText(pl_maske, R::ID_ANY, PTermin::printBasics(*iter_t));
		st_name->SetFont(st_name->GetFont().Bold());
		sizer_maske->Add(st_name, wxGBPosition(col, 1), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
		if (!(**iter_t).bem.IsSameAs(wxT(""))) {
			wxStaticText* st_bem = new wxStaticText(pl_maske, R::ID_ANY, (**iter_t).bem);
			sizer_maske->Add(st_bem, wxGBPosition(col + 1, 1), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
		}
		int num_dienste = (**iter_t).list_dienst_num.size();
		tview_list_termin.reserve(num_dienste);
		tview_list_termin_pl.reserve(num_dienste);
		int col_start = col; //Erinnerung an Anfang
		for (int i = 0; i < num_dienste; i++) {
			wxStaticText* st_dienst = new wxStaticText(pl_maske, R::ID_ANY, (**iter_t).list_dienst_num.at(i).first->name);
			st_dienst->SetFont(st_dienst->GetFont().Italic());
			sizer_maske->Add(st_dienst, wxGBPosition(col, 2), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
			std::vector<wxStaticText*> tview_list_dienst;
			std::vector<wxPanel*> tview_list_dienst_pl;
			int num_einsatz = (**iter_t).list_dienst_num.at(i).second;
			tview_list_dienst.reserve(num_einsatz);
			tview_list_dienst_pl.reserve(num_einsatz);
			for (int j = 0; j < num_einsatz; j++) {
				wxPanel* pl_einsatz = new wxPanel(pl_maske, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
				wxBoxSizer* sizer_einsatz = new wxBoxSizer(wxVERTICAL);
				wxStaticText* st_einsatz = new wxStaticText(pl_einsatz, R::ID_ANY, wxT("-            "));
				st_einsatz->Bind(wxEVT_LEFT_DCLICK, &PlanPlanerDialog::onShowPMiniChoiceDialog, this);
				st_einsatz->Bind(wxEVT_LEFT_DOWN, &PlanPlanerDialog::onHighlight, this);
				st_einsatz->SetBackgroundColour(colour_default);
				pl_einsatz->SetBackgroundColour(colour_default);
				sizer_einsatz->Add(st_einsatz, 1, wxEXPAND | wxALL, 2);
				pl_einsatz->SetSizer(sizer_einsatz);
				tview_list_dienst.push_back(st_einsatz);
				tview_list_dienst_pl.push_back(pl_einsatz);
				if (j % 2 == 0) {
					sizer_maske->Add(pl_einsatz, wxGBPosition(col, 3), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxEXPAND);
					if (j == num_einsatz - 1) {
						sizer_maske->Add(0, 0, wxGBPosition(col, 4));
						col++;
					}
				} else {
					sizer_maske->Add(pl_einsatz, wxGBPosition(col, 4), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxEXPAND);
					col++;
				}
			}
			tview_list_termin.push_back(tview_list_dienst);
			tview_list_termin_pl.push_back(tview_list_dienst_pl);
		}
		if (num_dienste == 0) {
			col++;
		}
		if (col == col_start) {
			if (!(**iter_t).bem.IsSameAs(wxT(""))) {
				col++;
			}
		}
		col++;
		tview_choices.push_back(tview_list_termin);
		tview_pls.push_back(tview_list_termin_pl);
	}
	pl_maske->FitInside();
	pl_maske->SetScrollRate(10, 10);
	pl_maske->Show();
	maskeShown = true;
}

void PlanPlanerDialog::redrawMaske() {
	if(!maskeShown) return;
	sizer_maske->Clear(false);
	pl_maske->DestroyChildren();
	tview_choices.clear();
	tview_pls.clear();
	maskeShown = false;
	if(modus == MODUS_MASKE) {
		initMaske();
	}
}

void PlanPlanerDialog::notifyMinis() {
	lv_minis->DeleteAllItems();
	int num = controller->planer->list_mini.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		lv_minis->InsertItem(item);
		PMessdiener m = *(controller->planer->list_mini.at(i));
		lv_minis->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_minis->SetItem(i, 1, m.name);
		lv_minis->SetItem(i, 2, m.vorname);
		lv_minis->SetItem(i, 3, PMessdiener::printDienste(&m));
		lv_minis->SetItem(i, 4, wxString::Format(wxT("%i"), m.num));
	}
	for (int i = 0; i < 5; i++) {
		lv_minis->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

void PlanPlanerDialog::notifyMGruppen() {
	lv_mgruppen->DeleteAllItems();
	int num = controller->planer->list_mgruppe.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		PMGruppe* mg = controller->planer->list_mgruppe.at(i);
		lv_mgruppen->InsertItem(item);
		lv_mgruppen->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_mgruppen->SetItem(i, 1, R::MGMODI[mg->modus]);
		lv_mgruppen->SetItem(i, 2, PMGruppe::printShort(mg));
	}
	for (int i = 0; i < 3; i++) {
		lv_mgruppen->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

void PlanPlanerDialog::notifyTermine(int index) {
	lv_termine->DeleteAllItems();
	for (int i = 0; i < (int) controller->planer->list_termin.size(); i++) {
		wxListItem item;
		item.SetId(i);
		PTermin* t = controller->planer->list_termin.at(i);
		lv_termine->InsertItem(item);
		lv_termine->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_termine->SetItem(i, 1, t->name);
		lv_termine->SetItem(i, 2, t->ort);
		lv_termine->SetItem(i, 3, Util::wxDateTime_to_wxString(t->datum) + wxT(" (") + R::WOCHENTAGE[t->datum.GetWeekDay()] + wxT(")"));
		lv_termine->SetItem(i, 4, t->zeit_beginn);
		lv_termine->SetItem(i, 5, PTermin::printDienste(t));
		lv_termine->SetItem(i, 6, t->bem);
	}
	if (index != -1) lv_termine->Select(index, true);
	for (int i = 0; i < R::TEINZEL_NUM + 1; i++) {
		lv_termine->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
}

void PlanPlanerDialog::notifyTGruppen() {
	lv_tgruppen->DeleteAllItems();
	int counter = 0;
	int gcounter = 1;
	for (std::vector<PTermin*>::iterator iter = controller->planer->list_termin.begin(); iter != controller->planer->list_termin.end(); iter++) {
		if ((**iter).prev == (PTermin *) NULL) {
			PTermin* termin = *iter;
			wxListItem item;
			item.SetId(counter);
			lv_tgruppen->InsertItem(item);
			lv_tgruppen->SetItem(counter, 0, wxString::Format(wxT("%i"), gcounter));
			bool ownRow = false;
			while (termin != (PTermin*) NULL) {
				if (ownRow) {
					counter++;
					wxListItem item;
					item.SetId(counter);
					lv_tgruppen->InsertItem(item);
				} else {
					ownRow = true;
				}
				lv_tgruppen->SetItem(counter, 1, PTermin::printShort(termin));
				termin = termin->next;
			}
			counter++;
			gcounter++;
		}
	}
	lv_tgruppen->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_tgruppen->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void PlanPlanerDialog::notifyMaskeAndPreview() {
	if (modus == MODUS_MASKE) {
		previewUpToDate = false;
		notifyMaske();
		maskeUpToDate = true;
	} else {
		maskeUpToDate = false;
		notifyPreview();
		previewUpToDate = true;
	}
}

void PlanPlanerDialog::notifyMaske() {
	int num_termine = controller->planer->list_termin.size();
	for (int i = 0; i < num_termine; i++) {
		PTermin* t = controller->planer->list_termin.at(i);
		int num_dienste = t->list_dienst_num.size();
		for (int j = 0; j < num_dienste; j++) {
			int m_counter = 0;
			for (std::vector<PMessdiener*>::iterator iter_m = t->list_dienst_minis.at(j).second.begin(); iter_m != t->list_dienst_minis.at(j).second.end(); iter_m++) {
				wxStaticText* st = tview_choices.at(i).at(j).at(m_counter++);
				st->SetLabel(*iter_m == NULL ? wxT("-            ") : (**iter_m).vorname + wxT(" ") + (**iter_m).name);
			}
		}
	}
	pl_maske->Layout();
}

void PlanPlanerDialog::notifyPreview() {
	html_preview->SetPage(HTMLExport::createHTML(&layout, controller->planer, true));
}

void PlanPlanerDialog::notifySave(bool canSave) {
	bt_save->Enable(canSave);
}

void PlanPlanerDialog::notifyHistory(bool enabled) {
	bt_undo->Enable(enabled);
}

void PlanPlanerDialog::notifyFuture(bool enabled) {
	bt_redo->Enable(enabled);
}

BEGIN_EVENT_TABLE(PlanPlanerDialog, wxFrame)
EVT_CLOSE(PlanPlanerDialog::onClose)
EVT_BUTTON(R::ID_BT_COMPUTE, PlanPlanerDialog::onCompute)
EVT_BUTTON(R::ID_BT_STOP, PlanPlanerDialog::onStop)
EVT_BUTTON(R::ID_BT_EDT2, PlanPlanerDialog::onOptions)
EVT_BUTTON(R::ID_UNDO, PlanPlanerDialog::onUndo)
EVT_BUTTON(R::ID_REDO, PlanPlanerDialog::onRedo)
EVT_BUTTON(R::ID_BT_DEL, PlanPlanerDialog::onClear)
EVT_BUTTON(R::ID_BT_OK, PlanPlanerDialog::onSave)
EVT_BUTTON(R::ID_BT_ADD, PlanPlanerDialog::onBtLayout)
EVT_BUTTON(R::ID_BT_ADD2, PlanPlanerDialog::onBtHTML)
EVT_BUTTON(R::ID_BT_EDT, PlanPlanerDialog::onBtCSV)
EVT_BUTTON(R::ID_BT_DEL2, PlanPlanerDialog::onBtExcelXML)
EVT_BUTTON(R::ID_EXPORT, PlanPlanerDialog::onBtTermineEdt)
EVT_BUTTON(R::ID_IMPORT, PlanPlanerDialog::onBtTermineDel)
EVT_LIST_ITEM_ACTIVATED(R::ID_CH, PlanPlanerDialog::onLITermineActivated)
EVT_LIST_ITEM_SELECTED(R::ID_LC, PlanPlanerDialog::onMinisViewHighlight)
EVT_NOTEBOOK_PAGE_CHANGED(R::ID_LB, PlanPlanerDialog::onNBPageChange)
END_EVENT_TABLE()

void PlanPlanerDialog::onClose(wxCloseEvent& evt) {
	if (controller->edt) {
		bool save = false;
		bool close = false;
		CloseDialog dialog(this, &save, &close);
		dialog.ShowModal();
		if (save) {
			controller->onSave();
		}
		if (!close) {
			evt.Veto(true);
			return;
		}
	}
	continueComputation = false;
	if (GetThread() && GetThread()->IsRunning()) GetThread()->Wait();
	delete controller;
	delete single_instance_checker;
	single_instance_checker = 0;
	evt.Skip();
}

void PlanPlanerDialog::onCompute(wxCommandEvent&) {
	if (continueComputation) return;
	continueComputation = true;
	bt_compute->Disable();
	bt_stop->Enable();
	if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR || GetThread()->Run() != wxTHREAD_NO_ERROR) {
		continueComputation = false;
		bt_compute->Enable();
		bt_stop->Disable();
		return;
	}
}

wxThread::ExitCode PlanPlanerDialog::Entry() {
	int canCreate = controller->simpleCheckCanCreatePlan();
	wxThreadEvent* evt = new wxThreadEvent();
	if (canCreate == 0) {
		controller->computePlan(&continueComputation);
		evt->SetInt(0);
	} else if (canCreate == 1) {
		evt->SetInt(1);
	} else {//canCreate == 2
		evt->SetInt(2);
	}
	wxQueueEvent(GetEventHandler(), evt);
	return (wxThread::ExitCode) 0;
}

void PlanPlanerDialog::onThreadDone(wxThreadEvent& evt) {
	bt_compute->Enable();
	bt_stop->Disable();
	if (evt.GetInt() == 1) {
		wxMessageDialog dialog(this, R::MSG_PLAN_CREATE_IMPOSSIBLE, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		dialog.ShowModal();
	} else if (evt.GetInt() == 0 && continueComputation) {
		notifyMinis();
		unHighlight();
		notifyMaskeAndPreview();
		notifyHistory(true);
		notifyFuture(false);
		notifySave(true);
	}
	continueComputation = false; //windows interactive again
}

void PlanPlanerDialog::onStop(wxCommandEvent&) {
	continueComputation = false; //comp stops in next loop
}

void PlanPlanerDialog::onOptions(wxCommandEvent&) {
	if (continueComputation) return;
	bool edt = false;
	PlanerSettingsDialog dialog(this, &controller->planer->settings, &edt);
	dialog.ShowModal();
	if (edt) {
		controller->edt = true;
		notifySave(true);
	}
}

void PlanPlanerDialog::onUndo(wxCommandEvent&) {
	if (continueComputation) return;
	controller->onUndo();
}

void PlanPlanerDialog::onRedo(wxCommandEvent&) {
	if (continueComputation) return;
	controller->onRedo();
}

void PlanPlanerDialog::onClear(wxCommandEvent&) {
	if (continueComputation) return;
	controller->onClear();
}

void PlanPlanerDialog::onShowPMiniChoiceDialog(wxMouseEvent& evt) {
	if (continueComputation) return;
	if (evt.GetEventObject()->IsKindOf(wxCLASSINFO(wxStaticText))) {
		wxStaticText* st = (wxStaticText*) evt.GetEventObject();
		bool found = false;
		PTermin* termin;
		int dienst;
		int mini;
		int num_termine = tview_choices.size();
		for (int i = 0; i < num_termine && !found; i++) {
			int num_dienste = tview_choices.at(i).size();
			for (int j = 0; j < num_dienste && !found; j++) {
				int num_einsaetze = tview_choices.at(i).at(j).size();
				for (int k = 0; k < num_einsaetze; k++) {
					if (st == tview_choices.at(i).at(j).at(k)) {
						found = true;
						termin = controller->planer->list_termin.at(i);
						dienst = j;
						mini = k;
						break;
					}
				}
			}
		}
		if (found) {
			highlightPMiniChoiceDialog(termin, dienst, mini);
			PMiniChoiceDialog* dialog = new PMiniChoiceDialog(this, controller, termin, dienst, mini);
			dialog->Show();
		}
	}
}

void PlanPlanerDialog::highlightPMiniChoiceDialog(PTermin* termin, int dienst, int mini_i) {
	PMessdiener* mini = termin->list_dienst_minis.at(dienst).second.at(mini_i);
	highlight(mini);
	tview_choices.at(termin->_id).at(dienst).at(mini_i)->SetBackgroundColour(colour_selection);
	tview_pls.at(termin->_id).at(dienst).at(mini_i)->SetBackgroundColour(colour_selection);
	tview_pls.at(termin->_id).at(dienst).at(mini_i)->Refresh();
}

void PlanPlanerDialog::unHighlightPMiniChoiceDialog(PTermin* termin, int dienst, int mini_i) {
	PMessdiener* mini = termin->list_dienst_minis.at(dienst).second.at(mini_i);
	tview_mini_high = NULL;
	highlight(mini);
}

void PlanPlanerDialog::unHighlight() {
	tview_mini_high = NULL;
	int num_termine = tview_choices.size();
	for (int i = 0; i < num_termine; i++) {
		int num_dienste = tview_choices.at(i).size();
		for (int j = 0; j < num_dienste; j++) {
			int num_einsaetze = tview_choices.at(i).at(j).size();
			for (int k = 0; k < num_einsaetze; k++) {
				tview_choices.at(i).at(j).at(k)->SetBackgroundColour(colour_default);
				tview_pls.at(i).at(j).at(k)->SetBackgroundColour(colour_default);
				tview_pls.at(i).at(j).at(k)->Refresh();
			}
		}
	}
	int num_minis = controller->planer->list_mini.size();
	for (int i = 0; i < num_minis; i++) {
		lv_minis->Select(i, false);
	}
}

void PlanPlanerDialog::highlight(PMessdiener* mini) {
	if (mini == NULL || mini == tview_mini_high) {
		unHighlight();
	} else {
		tview_mini_high = mini;
		int num_termine = tview_choices.size();
		for (int i = 0; i < num_termine; i++) {
			int num_dienste = tview_choices.at(i).size();
			for (int j = 0; j < num_dienste; j++) {
				int num_einsaetze = tview_choices.at(i).at(j).size();
				for (int k = 0; k < num_einsaetze; k++) {
					if (mini == controller->planer->list_termin.at(i)->list_dienst_minis.at(j).second.at(k)) {
						tview_choices.at(i).at(j).at(k)->SetBackgroundColour(colour_highlight);
						tview_pls.at(i).at(j).at(k)->SetBackgroundColour(colour_highlight);
						tview_pls.at(i).at(j).at(k)->Refresh();
					} else {
						tview_choices.at(i).at(j).at(k)->SetBackgroundColour(colour_default);
						tview_pls.at(i).at(j).at(k)->SetBackgroundColour(colour_default);
						tview_pls.at(i).at(j).at(k)->Refresh();
					}
				}
			}
		}
		int num_minis = controller->planer->list_mini.size();
		for (int i = 0; i < num_minis; i++) {
			lv_minis->Select(i, i == mini->_id);
		}
	}
}

void PlanPlanerDialog::onHighlight(wxMouseEvent& evt) {
	if (continueComputation) return;
	if (evt.GetEventObject()->IsKindOf(wxCLASSINFO(wxStaticText))) {
		wxStaticText* st = (wxStaticText*) evt.GetEventObject();
		bool found = false;
		PMessdiener* mini;
		int num_termine = tview_choices.size();
		for (int i = 0; i < num_termine && !found; i++) {
			int num_dienste = tview_choices.at(i).size();
			for (int j = 0; j < num_dienste && !found; j++) {
				int num_einsaetze = tview_choices.at(i).at(j).size();
				for (int k = 0; k < num_einsaetze; k++) {
					if (st == tview_choices.at(i).at(j).at(k)) {
						found = true;
						mini = controller->planer->list_termin.at(i)->list_dienst_minis.at(j).second.at(k);
						break;
					}
				}
			}
		}
		if (found) {
			highlight(mini);
		}
	}
}

void PlanPlanerDialog::onMinisViewHighlight(wxListEvent& evt) {
	if (modus == MODUS_PREVIEW) return;
	if (continueComputation) return;
	PMessdiener* m = controller->planer->list_mini.at(evt.GetItem().GetId());
	//prevent loop
	if (m != tview_mini_high) highlight(m);
}

void PlanPlanerDialog::onSave(wxCommandEvent&) {
	if (continueComputation) return;
	controller->onSave();
}

void PlanPlanerDialog::onNBPageChange(wxBookCtrlEvent& evt) {
	if (evt.GetSelection() == 0) {
		if (!maskeShown) initMaske();
		modus = MODUS_MASKE;
		if (!maskeUpToDate) notifyMaskeAndPreview();
	} else {
		modus = MODUS_PREVIEW;
		if (!previewUpToDate) notifyMaskeAndPreview();
	}
}

void PlanPlanerDialog::onBtLayout(wxCommandEvent&) {
	if (continueComputation) return;
	ExportLayoutDialog* dialog = new ExportLayoutDialog(this, &layout);
	dialog->ShowModal();
	delete dialog;
	notifyPreview();
}

void PlanPlanerDialog::onBtHTML(wxCommandEvent&) {
	if (continueComputation) return;
	wxString text = HTMLExport::createHTML(&layout, controller->planer, false);
	if (rb_file->GetValue()) {
		wxFileDialog saveFileDialog(this, R::SPEICHERN_HTML, wxT("output"),
				R::MESSDIENERPLAN_SH + wxT("_") + controller->planer->getDir() + wxT(".html"), wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
		wxFileOutputStream output_stream(saveFileDialog.GetPath());
		if (!output_stream.IsOk()) {
			return;
		}
		wxScopedCharBuffer text_utf8 = text.ToUTF8();
		output_stream.Write(text_utf8, text_utf8.length());
		output_stream.Close();
	} else {
		if (wxTheClipboard->Open()) {
			wxTheClipboard->SetData(new wxTextDataObject(text));
			wxTheClipboard->Close();
		}
	}
}

void PlanPlanerDialog::onBtCSV(wxCommandEvent&) {
	if (continueComputation) return;
	wxString text = CSVExport::createCSV(&layout, controller->planer);
	if (rb_file->GetValue()) {
		wxFileDialog saveFileDialog(this, R::SPEICHERN_CSV, wxT("output"),
				R::MESSDIENERPLAN_SH + wxT("_") + controller->planer->getDir() + wxT(".csv"), wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
		wxFileOutputStream output_stream(saveFileDialog.GetPath());
		if (!output_stream.IsOk()) {
			return;
		}
		wxScopedCharBuffer text_utf8 = text.ToUTF8();
		output_stream.Write(text_utf8, text_utf8.length());
		output_stream.Close();
	} else {
		if (wxTheClipboard->Open()) {
			wxTheClipboard->SetData(new wxTextDataObject(text));
			wxTheClipboard->Close();
		}
	}
}

void PlanPlanerDialog::onBtExcelXML(wxCommandEvent&) {
	if (continueComputation) return;
	wxString text = ExcelXMLExport::createExcelXML(&layout, controller->planer);
	if (rb_file->GetValue()) {
		wxFileDialog saveFileDialog(this, R::SPEICHERN_EXCEL_XML, wxT("output"),
				R::MESSDIENERPLAN_SH + wxT("_") + controller->planer->getDir() + wxT(".xml"), wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
		wxFileOutputStream output_stream(saveFileDialog.GetPath());
		if (!output_stream.IsOk()) {
			return;
		}
		wxScopedCharBuffer text_utf8 = text.ToUTF8();
		output_stream.Write(text_utf8, text_utf8.length());
		output_stream.Close();
	} else {
		if (wxTheClipboard->Open()) {
			wxTheClipboard->SetData(new wxTextDataObject(text));
			wxTheClipboard->Close();
		}
	}
}

void PlanPlanerDialog::onBtTermineEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		controller->onEdtTermin(i);
		break;
	}
}

void PlanPlanerDialog::onBtTermineDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_termine->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		bool del = false;
		DeleteDialog dialog(this, &del);
		dialog.ShowModal();
		if (del) controller->onDelTermin(i);
		break;
	}
}

void PlanPlanerDialog::onLITermineActivated(wxListEvent& evt) {
	controller->onEdtTermin(evt.GetItem().GetId());
}