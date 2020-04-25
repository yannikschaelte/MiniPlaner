/* 
 * File:   MainFrame.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 4:00 PM
 */

#include "MainFrame.h"
#include <wx/textfile.h>
#include <wx/dir.h>
#include <wx/tokenzr.h>
#include <wx/display.h>
#include <wx/settings.h>
#include <wx/filename.h>
#include <wx/mimetype.h>
#include <wx/intl.h>
#include "../R.h"
#include "../file/DataFileHandler.h"
#include "../img/minis.xpm"
#include "AboutPanel.h"

MainFrame::MainFrame(App* _app)
: wxFrame((wxFrame*) NULL, R::ID_ANY, R::MINI_PLANER, wxDefaultPosition, wxDefaultSize, wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX) {
	app = _app;
	wxFrame::SetIcon(wxICON(minis));
	wxDisplay display;
	wxRect screen = display.GetGeometry();
	wxFrame::SetSize(0, 0, screen.GetWidth() * 3 / 4, screen.GetHeight() * 3 / 4);

	wxPanel* pl_bg = new wxPanel(this, R::ID_ANY);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	pl_tabs = new wxPanel(pl_bg, R::ID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxTAB_TRAVERSAL);
	wxBoxSizer* sizer_tabs = new wxBoxSizer(wxVERTICAL);

	wxString list_names[9] = {R::DIENSTE, R::MINIS, R::MGRUPPEN, R::TERMINE, R::TGRUPPEN, R::FEHLZEITEN, R::PLAENE, R::HILFE, R::UEBER};
	list_tabs.reserve(9);
	for (int i = 0; i < 9; i++) {
		wxPanel* pl = new wxPanel(pl_tabs, 1000 + i);
		wxBoxSizer* sz = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText* st = new wxStaticText(pl, 1000 + i, list_names[i]);
		sz->Add(st, 1, wxEXPAND | wxLEFT | wxRIGHT, 8);
		wxBoxSizer* sz2 = new wxBoxSizer(wxHORIZONTAL);
		sz2->Add(sz, 1, wxEXPAND | wxTOP | wxBOTTOM, 2);
		pl->SetSizer(sz2);
		if (i == 7) sizer_tabs->Add(new wxPanel(pl_tabs, R::ID_ANY), 1, wxEXPAND, 0);
		sizer_tabs->Add(pl, 0, wxEXPAND | wxALL, 0);

		pl->Bind(wxEVT_LEFT_DOWN, &MainFrame::onLBSel, this);
		st->Bind(wxEVT_LEFT_DOWN, &MainFrame::onLBSel, this);
		pl->Bind(wxEVT_RIGHT_DOWN, &MainFrame::onLBSel, this);
		st->Bind(wxEVT_RIGHT_DOWN, &MainFrame::onLBSel, this);
		list_tabs.push_back(std::make_pair(pl, st));
	}
	pl_tabs->SetSizerAndFit(sizer_tabs);

	sizer->Add(pl_tabs, 0, wxEXPAND | wxALL, 0);
	sizer->AddSpacer(5);

	dienste_panel = new DienstePanel(pl_bg, app);
	minis_panel = new MinisPanel(pl_bg, app);
	m_gruppen_panel = new MGruppenPanel(pl_bg, app);
	termine_panel = new TerminePanel(pl_bg, app);
	t_gruppen_panel = new TGruppenPanel(pl_bg, app);
	fehlzeiten_panel = new FehlzeitenPanel(pl_bg, app);
	plaene_panel = new PlaenePanel(pl_bg, app);
	about_panel = new AboutPanel(pl_bg);

	sizer_r = new wxBoxSizer(wxVERTICAL);

	sizer_r->Add(dienste_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(minis_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(m_gruppen_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(termine_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(t_gruppen_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(fehlzeiten_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(plaene_panel, 1, wxEXPAND | wxALL, 0);
	sizer_r->Add(about_panel, 1, wxEXPAND | wxALL, 0);

	list_pls.reserve(8);
	list_pls.push_back(dienste_panel);
	list_pls.push_back(minis_panel);
	list_pls.push_back(m_gruppen_panel);
	list_pls.push_back(termine_panel);
	list_pls.push_back(t_gruppen_panel);
	list_pls.push_back(fehlzeiten_panel);
	list_pls.push_back(plaene_panel);
	list_pls.push_back(about_panel);

	handleLBSel(1); //init with minis
	sizer->Add(sizer_r, 1, wxEXPAND | wxALL, 0);

	pl_bg->SetSizer(sizer);
	loadGUISettings();

	wxFrame::Show(true);
}

void MainFrame::OnClose(wxCloseEvent&) {
	saveGUISettings();
	Destroy();
}

void MainFrame::loadGUISettings() {
	wxString line = R::window_size;
	if (!line.IsEmpty()) {
		wxStringTokenizer zr(line, DataFileHandler::D, wxTOKEN_RET_EMPTY_ALL);
		wxString s1 = zr.NextToken();
		if (s1.Cmp(wxT("FULLSCREEN")) == 0) {
			this->Maximize(true);
		} else {
			int x = wxAtoi(s1);
			int y = wxAtoi(zr.NextToken());
			int width = wxAtoi(zr.NextToken());
			int height = wxAtoi(zr.NextToken());
			this->SetSize(x, y, width, height);
		}
	}
}

void MainFrame::saveGUISettings() {
	wxPoint point = this->GetPosition();
	wxSize size = this->GetSize();
	wxString line;
	if (this->IsMaximized()) {
		line = wxT("FULLSCREEN");
	} else {
		line = wxString::Format(wxT("%i"), point.x) + DataFileHandler::D
				+ wxString::Format(wxT("%i"), point.y) + DataFileHandler::D
				+ wxString::Format(wxT("%i"), size.GetWidth()) + DataFileHandler::D
				+ wxString::Format(wxT("%i"), size.GetHeight());
	}
	R::window_size = line;
}

void MainFrame::notifyDienste(int index) {
	dienste_panel->notifyDienste(index);
}

void MainFrame::notifyMinis(int index) {
	minis_panel->notifyMinis(index);
}

void MainFrame::notifyEinzeltermine(int index) {
	termine_panel->notifyEinzeltermine(index);
}

void MainFrame::notifySerientermine(int index) {
	termine_panel->notifySerientermine(index);
}

void MainFrame::notifyMGruppen(int index) {
	m_gruppen_panel->notifyMGruppen(index);
}

void MainFrame::notifyTGruppen(int index) {
	t_gruppen_panel->notifyTGruppen(index);
}

void MainFrame::notifyFehlzeiten(int index) {
	fehlzeiten_panel->notifyFehlzeiten(index);
}

void MainFrame::notifyPlaene(int index) {
	plaene_panel->notifyPlaene(index);
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()

void MainFrame::onLBSel(wxMouseEvent& evt) {
	wxWindow* wnd = (wxWindow*) evt.GetEventObject();
	for (int i = 0; i < 9; i++) {
		if (wnd == (wxWindow*) list_tabs.at(i).first || wnd == (wxWindow*) list_tabs.at(i).second) {
			handleLBSel(i);
			return;
		}
	}
}

void MainFrame::handleLBSel(int index) {
	if (index == 7) {
		wxFileType* filetype = wxTheMimeTypesManager->GetFileTypeFromExtension(wxString("pdf"));
		if (filetype == NULL) {
			wxMessageDialog dialog(this, R::MSG_MANUAL_NOT_OPENED, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
			dialog.ShowModal();
		} else {
			wxString cmd = filetype->GetOpenCommand(wxT("help/Handbuch.pdf"));
			wxExecute(cmd);
			delete filetype;
		}
		return;
	}
	if (index == sel) return;
	for (int i = 0; i < 9; i++) {
		if (i == 7) continue;
		bool isSel = (i == index);
		list_pls.at(i == 8 ? 7 : i)->Show(isSel);
		if (isSel) {
			list_tabs.at(i).first->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
			list_tabs.at(i).second->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
			list_tabs.at(i).second->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
		} else {
			list_tabs.at(i).first->SetBackgroundColour(wxNullColour);
			list_tabs.at(i).second->SetBackgroundColour(wxNullColour);
			list_tabs.at(i).second->SetForegroundColour(wxNullColour);
		}
		list_tabs.at(i).first->Refresh();
	}
	sizer_r->Layout();
	sel = index;
}