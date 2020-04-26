/* 
 * File:   AboutPanel.cpp
 * Author: Yannik
 * 
 * Created on October 4, 2015, 11:10 PM
 */

#include "AboutPanel.h"
#include <wx/generic/statbmpg.h>
#include <wx/hyperlink.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <config.h>
#include "../img/minis.xpm"
#include "../R.h"
#include "../Util.h"

AboutPanel::AboutPanel(wxWindow* parent)
: wxPanel(parent, R::ID_ANY) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
#ifdef __WINDOWS__
	// Load from a resource with explicit width and height
	wxIcon icon(wxT("minis"), wxICON_DEFAULT_TYPE, 64, 64);
#else
	wxIcon icon = wxICON(minis);
#endif
	wxBitmap bitmap;
	bitmap.CopyFromIcon(icon);
	wxStaticBitmap* sb_icon = new wxStaticBitmap(this, R::ID_ANY, bitmap);
	sizer_1->Add(sb_icon, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	wxBoxSizer* sizer_1_r = new wxBoxSizer(wxVERTICAL);
	wxStaticText* st_name = new wxStaticText(this, R::ID_ANY, wxT(NAME_STR " " VERSION_STR));
	st_name->SetFont(st_name->GetFont().Bold());
	sizer_1_r->Add(st_name, 0, wxALL, 1);
	wxStaticText* st_desc = new wxStaticText(this, R::ID_ANY, R::HEADLINE);
	sizer_1_r->Add(st_desc, 0, wxALL, 1);
	sizer_1_r->Add(new wxStaticText(this, R::ID_ANY, wxT(COPYRIGHT_STR)), 0, wxALL, 1);
	sizer_1->Add(sizer_1_r, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	sizer->Add(sizer_1, 0, wxEXPAND | wxALL, 10);

	wxFlexGridSizer* sizer_2 = new wxFlexGridSizer(10, 2, 0, 0);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, R::AUTOR), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT(AUTHOR_STR)), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT("E-Mail: ")), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT("yannik.schaelte@gmail.com")), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT("Homepage: ")), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT("https://yannikschaelte.github.io/MiniPlaner/")), 0, wxALL, 2);
	sizer_2->AddSpacer(10);
	sizer_2->AddSpacer(10);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, R::KOMPILIERTMIT), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT(COMPILER_STR)), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, R::BIBLIOTHEKEN), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, wxT(WX_DEP_STR)), 0, wxALL, 2);
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, R::INSTALLATIONSVERZEICHNIS), 0, wxALL, 2);
	wxFileName file(wxStandardPaths::Get().GetExecutablePath());
	sizer_2->Add(new wxStaticText(this, R::ID_ANY, file.GetPath()), 0, wxALL, 2);
	sizer_2->AddGrowableCol(1, 1);
	sizer->Add(sizer_2, 0, wxEXPAND | wxALL, 10);

	sizer->AddSpacer(40);
	sizer->Add(new wxStaticText(this, R::ID_ANY, R::KONTAKT_MSG), 0, wxALL, 10);

	SetSizer(sizer);
}