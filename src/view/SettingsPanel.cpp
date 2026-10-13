#include "SettingsPanel.h"
#include "../Paths.h"
#include "../R.h"
#include "../UserData.h"

SettingsPanel::SettingsPanel(wxWindow* parent)
: wxPanel(parent, R::ID_ANY) {
	wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);

	grid->Add(new wxStaticText(this, R::ID_ANY, R::SPRACHE), 0, wxALIGN_CENTER_VERTICAL);
	wxBoxSizer* lang = new wxBoxSizer(wxVERTICAL);
	wxString langs[] = {wxT("Deutsch"), wxT("English")};
	wxChoice* choice = new wxChoice(this, R::ID_ANY, wxDefaultPosition, wxDefaultSize, 2, langs);
	choice->SetSelection(R::lang == R::LANG_DE ? 0 : 1);
	choice->Bind(wxEVT_CHOICE, &SettingsPanel::onLanguage, this);
	lang->Add(choice);
	lang->Add(new wxStaticText(this, R::ID_ANY, R::SET_LANG_NOTE), 0, wxTOP, 4);
	grid->Add(lang);

	grid->Add(new wxStaticText(this, R::ID_ANY, R::SET_DATA_FOLDER), 0, wxALIGN_CENTER_VERTICAL);
	wxBoxSizer* folder = new wxBoxSizer(wxHORIZONTAL);
	folder->Add(new wxStaticText(this, R::ID_ANY, Paths::dataDir()), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
	wxButton* open = new wxButton(this, R::ID_ANY, R::SET_OPEN_FOLDER);
	open->Bind(wxEVT_BUTTON, [](wxCommandEvent&) { wxLaunchDefaultApplication(Paths::dataDir()); });
	folder->Add(open);
	grid->Add(folder);

	grid->AddSpacer(0);
	wxBoxSizer* data = new wxBoxSizer(wxHORIZONTAL);
	wxButton* demo = new wxButton(this, R::ID_ANY, R::SET_LOAD_DEMO);
	demo->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { changeData(R::MSG_CONFIRM_DEMO, [] { UserData::loadDemo(); }); });
	wxButton* del = new wxButton(this, R::ID_ANY, R::SET_DELETE_ALL);
	del->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { changeData(R::MSG_CONFIRM_DELETE, [] { UserData::clearAll(); }); });
	data->Add(demo, 0, wxRIGHT, 10);
	data->Add(del);
	grid->Add(data);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(grid, 0, wxALL, 20);
	SetSizer(sizer);
}

void SettingsPanel::changeData(const wxString& question, void (*operation)()) {
	if (wxMessageBox(question, R::EINSTELLUNGEN, wxYES_NO | wxICON_QUESTION, this) != wxYES) return;
	operation();
	wxMessageBox(R::MSG_RESTART, R::EINSTELLUNGEN, wxOK | wxICON_INFORMATION, this);
	wxGetTopLevelParent(this)->Close(true);
}

void SettingsPanel::onLanguage(wxCommandEvent& evt) {
	R::lang = evt.GetSelection() == 0 ? R::LANG_DE : R::LANG_EN;
}
