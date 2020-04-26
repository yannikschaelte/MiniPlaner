/* 
 * File:   PlanFileHandler.cpp
 * Author: Yannik
 * 
 * Created on August 27, 2015, 9:06 PM
 */

#include "PlanFileHandler.h"
#include <wx/textfile.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/tokenzr.h>
#include "DataFileHandler.h"
#include "../Util.h"

const wxString PlanFileHandler::RES = wxT("res");
const wxString PlanFileHandler::D = wxT("\t");
const wxString PlanFileHandler::DIENSTEFILE = wxT("/dienste.dat");
const wxString PlanFileHandler::MINISFILE = wxT("/minis.dat");
const wxString PlanFileHandler::TERMINEFILE = wxT("/termine.dat");
const wxString PlanFileHandler::MGRUPPENFILE = wxT("/mgruppen.dat");
const wxString PlanFileHandler::FEHLZEITENFILE = wxT("/fehlzeiten.dat");
const wxString PlanFileHandler::SETTINGSFILE = wxT("/settings.dat");

PlanerInfo PlanFileHandler::createDir(wxDateTime datum_beginn, wxDateTime datum_ende) {
	wxString base = datum_beginn.Format(wxT("%Y-%m-%d")) + wxT("_") + datum_ende.Format(wxT("%Y-%m-%d"));
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	if (wxDir::Exists(RES + wxT("/") + base)) {
		int counter = 2;
		while (wxDir::Exists(RES + wxT("/") + base + wxString::Format(wxT("(%i)"), counter))) {
			counter++;
		}
		wxDir::Make(RES + wxT("/") + base + wxString::Format(wxT("(%i)"), counter));
		return PlanerInfo(datum_beginn, datum_ende, counter);
	} else {
		wxDir::Make(RES + wxT("/") + base);
		return PlanerInfo(datum_beginn, datum_ende, 1);
	}
}

void PlanFileHandler::deleteDir(PlanerInfo info) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	} else {
		wxString dir = RES + wxT("/") + info.getDir();
		wxDir::Remove(dir, wxPATH_RMDIR_RECURSIVE);
	}
}

void PlanFileHandler::savePlaner(Planer* planer) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxString base = RES + wxT("/") + planer->getDir();
	if (!wxDir::Exists(base)) {
		wxDir::Make(base);
	}
	//save Dienste
	wxTextFile dienste_file(base + DIENSTEFILE);
	if (!dienste_file.Exists()) {
		dienste_file.Create();
	}
	dienste_file.Open();
	dienste_file.Clear();
	for (int i = 0; i < (int) planer->list_dienst.size(); i++) {
		Dienst d = *(planer->list_dienst.at(i));
		dienste_file.AddLine(d.name);
	}
	dienste_file.Write();
	dienste_file.Close();
	//save Termine
	wxTextFile termine_file(base + TERMINEFILE);
	if (!termine_file.Exists()) {
		termine_file.Create();
	}
	termine_file.Open();
	termine_file.Clear();
	for (int i = 0; i < (int) planer->list_termin.size(); i++) {
		PTermin t = *(planer->list_termin.at(i));
		wxString line = t.name + D + t.ort + D + Util::wxDateTime_to_wxString(t.datum) + D + t.zeit_beginn + D
				+ (t.prev == NULL ? wxT("-1") : wxString::Format(wxT("%i"), t.prev->_id)) + D
				+ (t.next == NULL ? wxT("-1") : wxString::Format(wxT("%i"), t.next->_id)) + D
				+ t.bem;
		termine_file.AddLine(line);
		line = wxString::Format(wxT("%zu"), t.list_dienst_num.size());
		termine_file.AddLine(line); //Anzahl Dienste, gleich für alle Listen
		for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter = t.list_dienst_minis.begin(); iter != t.list_dienst_minis.end(); iter++) {
			line = wxString::Format(wxT("%i"), iter->first->_id);
			for (std::vector<PMessdiener*>::iterator iter_m = iter->second.begin(); iter_m != iter->second.end(); iter_m++) {
				line += D + (*iter_m == NULL ? wxT("-1") : wxString::Format(wxT("%i"), (**iter_m)._id));
			}
			termine_file.AddLine(line);
		}
		for (std::vector<std::pair<Dienst*, int> >::iterator iter = t.list_dienst_num.begin(); iter != t.list_dienst_num.end(); iter++) {
			line = wxString::Format(wxT("%i"), iter->first->_id) + D + wxString::Format(wxT("%i"), iter->second);
			termine_file.AddLine(line);
		}
		for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter = t.list_dienst_minis_possible.begin(); iter != t.list_dienst_minis_possible.end(); iter++) {
			line = wxString::Format(wxT("%i"), iter->first->_id);
			for (std::vector<PMessdiener*>::iterator iter_m = iter->second.begin(); iter_m != iter->second.end(); iter_m++) {
				line += D + wxString::Format(wxT("%i"), (**iter_m)._id);
			}
			termine_file.AddLine(line);
		}
		for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter = t.list_dienst_minis_available.begin(); iter != t.list_dienst_minis_available.end(); iter++) {
			line = wxString::Format(wxT("%i"), iter->first->_id);
			for (std::vector<PMessdiener*>::iterator iter_m = iter->second.begin(); iter_m != iter->second.end(); iter_m++) {
				line += D + wxString::Format(wxT("%i"), (**iter_m)._id);
			}
			termine_file.AddLine(line);
		}
	}
	termine_file.Write();
	termine_file.Close();
	//save Minis
	wxTextFile minis_file(base + MINISFILE);
	if (!minis_file.Exists()) {
		minis_file.Create();
	}
	minis_file.Open();
	minis_file.Clear();
	for (int i = 0; i < (int) planer->list_mini.size(); i++) {
		PMessdiener m = *(planer->list_mini.at(i));
		wxString line = m.name + D + m.vorname + D + wxString::Format(wxT("%i"), m.num);
		for (std::vector<Dienst*>::iterator iter_d = m.dienste.begin(); iter_d != m.dienste.end(); iter_d++) {
			line += D + wxString::Format(wxT("%i"), (**iter_d)._id);
		}
		minis_file.AddLine(line);
	}
	minis_file.Write();
	minis_file.Close();
	//save MGruppen
	wxTextFile mgruppen_file(base + MGRUPPENFILE);
	if (!mgruppen_file.Exists()) {
		mgruppen_file.Create();
	}
	mgruppen_file.Open();
	mgruppen_file.Clear();
	for (int i = 0; i < (int) planer->list_mgruppe.size(); i++) {
		PMGruppe mg = *(planer->list_mgruppe.at(i));
		wxString line = wxString::Format(wxT("%i"), mg.modus);
		for (std::vector<PMessdiener*>::iterator iter_m = mg.list.begin(); iter_m != mg.list.end(); iter_m++) {
			line += D + wxString::Format(wxT("%i"), (**iter_m)._id);
		}
		mgruppen_file.AddLine(line);
	}
	mgruppen_file.Write();
	mgruppen_file.Close();
	//save Fehlzeiten
	wxTextFile fehlzeiten_file(base + FEHLZEITENFILE);
	if (!fehlzeiten_file.Exists()) {
		fehlzeiten_file.Create();
	}
	fehlzeiten_file.Open();
	fehlzeiten_file.Clear();
	int num_fehlzeiten = planer->list_fehlzeit.size();
	for (int i = 0; i < num_fehlzeiten; i++) {
		PFehlzeit* f = planer->list_fehlzeit.at(i);
		wxString line = wxString::Format(wxT("%i"), Fehlzeit::ZEITRAUM) + D + wxString::Format(wxT("%i"), f->mini->_id)
				+ D + Util::wxDateTime_to_wxString(f->datum_beginn)
				+ D + Util::wxDateTime_to_wxString(f->datum_ende);
		fehlzeiten_file.AddLine(line);
	}
	fehlzeiten_file.Write();
	fehlzeiten_file.Close();
	//save Settings
	wxTextFile settings_file(base + SETTINGSFILE);
	if (!settings_file.Exists()) {
		settings_file.Create();
	}
	settings_file.Open();
	settings_file.Clear();
	wxString line = wxString::Format(wxT("%i"), planer->settings.modus_fehlzeiten) + D + wxString::Format(wxT("%i"), planer->settings.modus_algorithmus);
	settings_file.AddLine(line);
	settings_file.Write();
	settings_file.Close();
}

void PlanFileHandler::loadPlaner(Planer* planer) {
	wxString base = RES + wxT("/") + planer->getDir();
	//load Dienste
	planer->list_dienst.clear();
	wxTextFile dienste_file(base + DIENSTEFILE);
	dienste_file.Open();
	for (wxString line = dienste_file.GetFirstLine(); !dienste_file.Eof(); line = dienste_file.GetNextLine()) {
		planer->list_dienst.push_back(new Dienst(line));
	}
	dienste_file.Close();
	//load Minis
	planer->list_mini.clear();
	wxTextFile minis_file(base + MINISFILE);
	minis_file.Open();
	for (wxString line = minis_file.GetFirstLine(); !minis_file.Eof(); line = minis_file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = zr.NextToken();
		wxString vorname = zr.NextToken();
		int num = wxAtoi(zr.NextToken());
		std::vector<Dienst*> mdlist;
		while (zr.HasMoreTokens()) {
			int d = wxAtoi(zr.NextToken());
			mdlist.push_back(planer->list_dienst.at(d));
		}
		planer->list_mini.push_back(new PMessdiener(name, vorname, mdlist, num));
	}
	minis_file.Close();
	//load MGruppen
	planer->list_mgruppe.clear();
	wxTextFile mgruppen_file(base + MGRUPPENFILE);
	mgruppen_file.Open();
	for (wxString line = mgruppen_file.GetFirstLine(); !mgruppen_file.Eof(); line = mgruppen_file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		int modus = wxAtoi(zr.NextToken());
		std::vector<PMessdiener*> mlist;
		while (zr.HasMoreTokens()) {
			mlist.push_back(planer->list_mini.at(wxAtoi(zr.NextToken())));
		}
		planer->list_mgruppe.push_back(new PMGruppe(modus, mlist));
	}
	mgruppen_file.Close();
	//set missing links Minis-MGruppen
	for (std::vector<PMGruppe*>::iterator iter = planer->list_mgruppe.begin(); iter != planer->list_mgruppe.end(); iter++) {
		for (std::vector<PMessdiener*>::iterator iter_m = (**iter).list.begin(); iter_m != (**iter).list.end(); iter_m++) {
			(**iter_m).gruppe = *iter;
		}
	}
	//load Fehlzeiten
	wxTextFile fehlzeiten_file(base + FEHLZEITENFILE);
	fehlzeiten_file.Open();
	for (wxString line = fehlzeiten_file.GetFirstLine(); !fehlzeiten_file.Eof(); line = fehlzeiten_file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		zr.NextToken(); //Modus
		PMessdiener* m = planer->list_mini.at(wxAtoi(zr.NextToken()));
		wxDateTime datum_beginn = Util::wxString_to_wxDateTime(zr.NextToken());
		wxDateTime datum_ende = Util::wxString_to_wxDateTime(zr.NextToken());
		planer->list_fehlzeit.push_back(new PFehlzeit(m, datum_beginn, datum_ende));
	}
	fehlzeiten_file.Close();
	//load Settings
	wxTextFile settings_file(base + SETTINGSFILE);
	settings_file.Open();
	wxString line_settings = settings_file.GetFirstLine();
	wxStringTokenizer zr(line_settings, D, wxTOKEN_RET_EMPTY_ALL);
	planer->settings.modus_fehlzeiten = wxAtoi(zr.NextToken());
	planer->settings.modus_algorithmus = wxAtoi(zr.NextToken());
	settings_file.Close();
	//load Termine
	std::vector<std::pair<int, std::pair<int, int> > > termin_prev_next;
	planer->list_termin.clear();
	wxTextFile termine_file(base + TERMINEFILE);
	termine_file.Open();
	wxString line = termine_file.GetFirstLine();
	int t_counter = 0;
	while (!termine_file.Eof()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = zr.NextToken();
		wxString ort = zr.NextToken();
		wxDateTime datum = Util::wxString_to_wxDateTime(zr.NextToken());
		wxString zeit_beginn = zr.NextToken();
		int prev = wxAtoi(zr.NextToken());
		int next = wxAtoi(zr.NextToken());
		termin_prev_next.push_back(std::make_pair(t_counter++, std::make_pair(prev, next)));
		wxString bem = zr.NextToken();
		line = termine_file.GetNextLine();
		int num_dienste = wxAtoi(line);
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_mini;
		std::vector<std::pair<Dienst*, int> > list_num;
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_poss;
		std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_avai;
		for (int i = 0; i < num_dienste; i++) {
			line = termine_file.GetNextLine();
			wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
			Dienst* d = planer->list_dienst.at(wxAtoi(zr.NextToken()));
			std::vector<PMessdiener*> mset;
			while (zr.HasMoreTokens()) {
				int m_index = wxAtoi(zr.NextToken());
				mset.push_back(m_index == -1 ? NULL : planer->list_mini.at(m_index));
			}
			list_mini.push_back(std::make_pair(d, mset));
		}
		for (int i = 0; i < num_dienste; i++) {
			line = termine_file.GetNextLine();
			wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
			Dienst* d = planer->list_dienst.at(wxAtoi(zr.NextToken()));
			int num = wxAtoi(zr.NextToken());
			list_num.push_back(std::make_pair(d, num));
		}
		for (int i = 0; i < num_dienste; i++) {
			line = termine_file.GetNextLine();
			wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
			Dienst* d = planer->list_dienst.at(wxAtoi(zr.NextToken()));
			std::vector<PMessdiener*> mset;
			while (zr.HasMoreTokens()) {
				mset.push_back(planer->list_mini.at(wxAtoi(zr.NextToken())));
			}
			list_poss.push_back(std::make_pair(d, mset));
		}
		for (int i = 0; i < num_dienste; i++) {
			line = termine_file.GetNextLine();
			wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
			Dienst* d = planer->list_dienst.at(wxAtoi(zr.NextToken()));
			std::vector<PMessdiener*> mset;
			while (zr.HasMoreTokens()) {
				mset.push_back(planer->list_mini.at(wxAtoi(zr.NextToken())));
			}
			list_avai.push_back(std::make_pair(d, mset));
		}
		PTermin* termin = new PTermin(name, ort, datum, zeit_beginn, bem, list_num);
		termin->list_dienst_minis = list_mini;
		termin->list_dienst_minis_possible = list_poss;
		termin->list_dienst_minis_available = list_avai;

		planer->list_termin.push_back(termin);
		line = termine_file.GetNextLine();
	}
	//set links prev-next
	for (std::vector<std::pair<int, std::pair<int, int> > >::iterator iter_t = termin_prev_next.begin(); iter_t != termin_prev_next.end(); iter_t++) {
		if (iter_t->second.first != -1) {
			planer->list_termin.at(iter_t->first)->prev = planer->list_termin.at(iter_t->second.first);
		}
		if (iter_t->second.second != -1) {
			planer->list_termin.at(iter_t->first)->next = planer->list_termin.at(iter_t->second.second);
		}
	}
	termine_file.Close();
	//prepare ids
	int counter = 0;
	for (std::vector<Dienst*>::iterator iter = planer->list_dienst.begin(); iter != planer->list_dienst.end(); iter++) {
		(**iter)._id = counter++;
	}
	counter = 0;
	for (std::vector<PMessdiener*>::iterator iter = planer->list_mini.begin(); iter != planer->list_mini.end(); iter++) {
		(**iter)._id = counter++;
	}
	counter = 0;
	for (std::vector<PMGruppe*>::iterator iter = planer->list_mgruppe.begin(); iter != planer->list_mgruppe.end(); iter++) {
		(**iter)._id = counter++;
	}
	counter = 0;
	for (std::vector<PTermin*>::iterator iter = planer->list_termin.begin(); iter != planer->list_termin.end(); iter++) {
		(**iter)._id = counter++;
	}
	counter = 0;
	for (std::vector<PFehlzeit*>::iterator iter = planer->list_fehlzeit.begin(); iter != planer->list_fehlzeit.end(); iter++) {
		(**iter)._id = counter++;
	}
}