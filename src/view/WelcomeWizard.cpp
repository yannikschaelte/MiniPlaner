#include "WelcomeWizard.h"
#include <wx/wx.h>
#include <wx/hyperlink.h>
#include <wx/settings.h>
#include <wx/wizard.h>
#include <config.h>
#include "../R.h"
#include "../img/minis.xpm"

namespace {
	const int WRAP = 420;
	const int MARGIN = 20;

	wxStaticText* text(wxWindow* parent, const wxString& label, bool markup = false) {
		wxStaticText* st = new wxStaticText(parent, R::ID_ANY, wxEmptyString);
		if (markup) st->SetLabelMarkup(label);
		else st->SetLabel(label);
		st->Wrap(WRAP);
		return st;
	}

	wxStaticText* styled(wxStaticText* st, const wxColour& colour, bool bold) {
		st->SetForegroundColour(colour);
		if (bold) st->SetFont(st->GetFont().Bold());
		return st;
	}

	/** A page with a large title; content is added to the returned sizer. */
	wxWizardPageSimple* page(wxWizard* wizard, const wxString& title, wxBoxSizer*& sizer) {
		wxWizardPageSimple* p = new wxWizardPageSimple(wizard);
		sizer = new wxBoxSizer(wxVERTICAL);
		wxStaticText* st = new wxStaticText(p, R::ID_ANY, title);
		st->SetFont(st->GetFont().Bold().Scaled(1.6));
		sizer->Add(st, 0, wxLEFT | wxRIGHT | wxTOP, MARGIN);
		sizer->AddSpacer(MARGIN);
		p->SetSizer(sizer);
		return p;
	}

	/** Shows the wizard once; sets \a relang if the language changed (wizard must be rebuilt). */
	void show(bool& relang, bool& demo) {
		const wxColour accent = wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT);
		const wxColour muted = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT);
		wxWizard wizard(NULL, R::ID_ANY, R::WELCOME_TITLE, wxBitmap(minis_xpm));
		wizard.SetBitmapPlacement(wxWIZARD_VALIGN_CENTRE);
		wizard.SetMinimumBitmapWidth(130);
		wizard.SetBitmapBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
		wxBoxSizer *s1, *s2, *s3;

		wxWizardPageSimple* p1 = page(&wizard, R::WELCOME_TITLE, s1);
		s1->Add(text(p1, R::WELCOME_INTRO), 0, wxLEFT | wxRIGHT, MARGIN);
		wxString choices[] = {R::WELCOME_EMPTY, R::WELCOME_DEMO};
		wxRadioBox* choice = new wxRadioBox(p1, R::ID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 2, choices, 1, wxRA_SPECIFY_COLS | wxBORDER_NONE);
		choice->SetFont(choice->GetFont().Larger());
		s1->Add(choice, 0, wxALL, MARGIN);
		wxStaticText* note = text(p1, R::WELCOME_DEMO_NOTE, true);
		s1->Add(styled(note, muted, false), 0, wxLEFT | wxRIGHT, MARGIN);
		s1->AddStretchSpacer();
		wxString langs[] = {wxT("Deutsch"), wxT("English")};
		wxChoice* lang = new wxChoice(p1, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 2, langs);
		lang->SetSelection(R::lang == R::LANG_DE ? 0 : 1);
		s1->Add(lang, 0, wxALL, MARGIN);
		choice->SetSelection(demo ? 1 : 0);
		lang->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt) {
			R::lang = evt.GetSelection() == 0 ? R::LANG_DE : R::LANG_EN;
			R::setLang();
			demo = choice->GetSelection() == 1;
			relang = true;
			wizard.EndModal(wxID_CANCEL);
		});

		wxWizardPageSimple* p2 = page(&wizard, R::TOUR_TITLE, s2);
		wxFlexGridSizer* tour = new wxFlexGridSizer(3, 10, 12);
		const wxString* names[] = {&R::DIENSTE, &R::MINIS, &R::MGRUPPEN, &R::TERMINE, &R::TGRUPPEN, &R::FEHLZEITEN, &R::PLAENE};
		const wxString* descs[] = {&R::TOUR_DIENSTE, &R::TOUR_MINIS, &R::TOUR_MGRUPPEN, &R::TOUR_TERMINE, &R::TOUR_TGRUPPEN, &R::TOUR_FEHLZEITEN, &R::TOUR_PLAENE};
		for (int i = 0; i < 7; i++) {
			tour->Add(styled(text(p2, wxString::Format(wxT("%i"), i + 1)), accent, true), 0, wxALIGN_RIGHT);
			wxStaticText* name = new wxStaticText(p2, R::ID_ANY, *names[i]);
			name->SetFont(name->GetFont().Bold());
			tour->Add(name);
			tour->Add(styled(text(p2, *descs[i]), muted, false));
		}
		s2->Add(tour, 0, wxLEFT | wxRIGHT, MARGIN);

		wxWizardPageSimple* p3 = page(&wizard, R::HILFE, s3);
		s3->Add(text(p3, R::TOUR_DOCS), 0, wxLEFT | wxRIGHT | wxBOTTOM, MARGIN);
		s3->Add(new wxHyperlinkCtrl(p3, R::ID_ANY, R::OPEN_MANUAL, wxT(MANUAL_STR)), 0, wxLEFT | wxRIGHT | wxBOTTOM, MARGIN);
		s3->Add(new wxHyperlinkCtrl(p3, R::ID_ANY, wxT(HOMEPAGE_STR), wxT(HOMEPAGE_STR)), 0, wxLEFT | wxRIGHT, MARGIN);

		wxWizardPageSimple::Chain(p1, p2);
		wxWizardPageSimple::Chain(p2, p3);
		wizard.GetPageAreaSizer()->Add(p1);
		wizard.GetPageAreaSizer()->Add(p2);
		wizard.GetPageAreaSizer()->Add(p3);
		const bool finished = wizard.RunWizard(p1);
		if (!relang) demo = finished && choice->GetSelection() == 1;
	}
}

bool WelcomeWizard::run() {
	bool relang, demo = false;
	do {
		relang = false;
		show(relang, demo);
	} while (relang);
	return demo;
}
