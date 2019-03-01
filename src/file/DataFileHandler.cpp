/* 
 * File:   DataFileHandler.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 4:44 PM
 */

#include "DataFileHandler.h"
#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/dir.h>
#include <wx/tokenzr.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <vector>
#include "../R.h"
#include "../Util.h"

const wxString DataFileHandler::RES = wxT("res");
const wxString DataFileHandler::D = wxT("\t");
const wxString DataFileHandler::SETTINGSFILE = RES + wxT("/settings.dat");
const wxString DataFileHandler::DIENSTEFILE = RES + wxT("/dienste.dat");
const wxString DataFileHandler::MINISFILE = RES + wxT("/minis.dat");
const wxString DataFileHandler::EINZELTERMINEFILE = RES + wxT("/einzeltermine.dat");
const wxString DataFileHandler::SERIENTERMINEFILE = RES + wxT("/serientermine.dat");
const wxString DataFileHandler::MGRUPPENFILE = RES + wxT("/mgruppen.dat");
const wxString DataFileHandler::TGRUPPENFILE = RES + wxT("/tgruppen.dat");
const wxString DataFileHandler::FEHLZEITENFILE = RES + wxT("/fehlzeiten.dat");
const wxString DataFileHandler::PLANERINFOSFILE = RES + wxT("/plaene.dat");

void DataFileHandler::prepareFiles() {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxString filenames[] = {SETTINGSFILE,
		DIENSTEFILE,
		MINISFILE,
		EINZELTERMINEFILE,
		SERIENTERMINEFILE,
		MGRUPPENFILE,
		TGRUPPENFILE,
		FEHLZEITENFILE,
		PLANERINFOSFILE};
	int len = sizeof (filenames) / sizeof (wxString);
	for (int i = 0; i < len; i++) {
		wxTextFile file(filenames[i]);
		if (!file.Exists()) {
			file.Create();
		}
	}
}

void DataFileHandler::implementUpdates() {
	wxTextFile file(MINISFILE);
	file.Open();
	int lines = file.GetLineCount();
	if (lines > 0) {
		wxString line = file.GetFirstLine();
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		bool hasVersion = (zr.CountTokens() == 1) ? true : false;
		//exactly 1 token : is the version line (otherwise 0 or >1 tokens as every mini has > 7 attributes)
		if (!hasVersion) {//implement mini.bem (before there was no version)
			std::vector<std::vector<wxString> > items;
			for (; !file.Eof(); line = file.GetNextLine()) {
				std::vector<wxString> item;
				wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
				for (int i = 0; i < 8; i++) item.push_back(zr.NextToken());
				item.push_back(wxT(""));
				while (zr.HasMoreTokens()) item.push_back(zr.NextToken());
				items.push_back(item);
			}
			file.Clear();
			file.AddLine(wxString::Format(wxT("%i"), R::VERSION_NUMBER));
			int num = items.size();
			for (int i = 0; i < num; i++) {
				std::vector<wxString> item = items.at(i);
				int num2 = item.size();
				wxString line = wxT("");
				for (int j = 0; j < num2 - 1; j++) {
					line += item.at(j) + D;
				}
				line += item.at(num2 - 1);
				file.AddLine(line);
			}
			file.Write();
		}
	} else {//is empty file, insert version
		file.AddLine(wxString::Format(wxT("%i"), R::VERSION_NUMBER));
		file.Write();
	}
	file.Close();
}

void DataFileHandler::saveSettings() {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(SETTINGSFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	file.AddLine(R::window_size);
	file.AddLine(wxString::Format(wxT("%i"), R::lang));
	file.Write();
	file.Close();
}

void DataFileHandler::loadSettings() {
	wxTextFile file(SETTINGSFILE);
	file.Open();
	//depending on version, different file sizes are possible
	int num_lines = file.GetLineCount();
	//main window size
	if (num_lines > 0) {
		R::window_size = file.GetLine(0);
	}
	//language
	if (num_lines > 1) {
		R::lang = wxAtoi(file.GetLine(1));
	} else {
		int lang = wxLocale::GetSystemLanguage();
		if (lang == wxLANGUAGE_GERMAN
				|| lang == wxLANGUAGE_GERMAN_AUSTRIAN
				|| lang == wxLANGUAGE_GERMAN_BELGIUM
				|| lang == wxLANGUAGE_GERMAN_LIECHTENSTEIN
				|| lang == wxLANGUAGE_GERMAN_LUXEMBOURG
				|| lang == wxLANGUAGE_GERMAN_SWISS) {
			R::lang = R::LANG_DE;
		} else {
			R::lang = R::LANG_DE; //until language selectable
		}
	}
	file.Close();

	//set language
	R::setLang();
}

void DataFileHandler::saveDienste(const std::vector<Dienst*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(DIENSTEFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		Dienst d = *(list->at(i));
		file.AddLine(d.name);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadDienste(std::vector<Dienst*>* list) {
	wxTextFile file(DIENSTEFILE);
	file.Open();
	for (wxString line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()) {
		list->push_back(new Dienst(line));
	}
	if (list->empty()) {
		if (R::lang == R::LANG_DE)
			list->push_back(new Dienst(R::ALLGEMEIN));
		else {
			list->push_back(new Dienst(wxT("Altar Server")));
		}
	}
	file.Close();
}

void DataFileHandler::saveMinis(const std::vector<Messdiener*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(MINISFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	file.AddLine(wxString::Format(wxT("%i"), R::VERSION_NUMBER));
	for (int i = 0; i < (int) list->size(); i++) {
		Messdiener m = *(list->at(i));
		wxString line = m.name + D + m.vorname + D + m.geburtstag + D
				+ m.strasse_nr + D + m.plz_ort + D + m.tel + D + m.mobile + D + m.email + D + m.bem;
		int msize = m.dienste.size();
		for (int j = 0; j < msize; j++) {
			line += D + wxString::Format(wxT("%i"), (*(m.dienste.at(j)))._id);
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadMinis(std::vector<Dienst*>* dlist, std::vector<Messdiener*>* list) {
	wxTextFile file(MINISFILE);
	file.Open();
	int lines = file.GetLineCount();
	wxString line = file.GetFirstLine();
	if (lines > 1) {
		line = file.GetNextLine(); //first line: version
		for (; !file.Eof(); line = file.GetNextLine()) {
			wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
			wxString name = zr.NextToken();
			wxString vorname = zr.NextToken();
			wxString geburtstag = zr.NextToken();
			wxString strasse_nr = zr.NextToken();
			wxString plz_ort = zr.NextToken();
			wxString tel = zr.NextToken();
			wxString mobile = zr.NextToken();
			wxString email = zr.NextToken();
			wxString bem = zr.NextToken();
			std::vector<Dienst*> mdlist;
			while (zr.HasMoreTokens()) {
				int d = wxAtoi(zr.NextToken());
				mdlist.push_back(dlist->at(d));
			}
			list->push_back(new Messdiener(name, vorname, mdlist, geburtstag, strasse_nr, plz_ort, tel, mobile, email, bem));
		}
	}
	file.Close();
}

void DataFileHandler::saveEinzeltermine(const std::vector<Einzeltermin*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(EINZELTERMINEFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		Einzeltermin t = *(list->at(i));
		wxString line = t.name + D + t.ort + D + t.datum + D + t.zeit_beginn + D + t.bem;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter = t.dienste.begin(); iter != t.dienste.end(); iter++) {
			line += D + wxString::Format(wxT("%i"), iter->first->_id) + D + wxString::Format(wxT("%i"), iter->second);
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadEinzeltermine(std::vector<Dienst*>* dlist, std::vector<Einzeltermin*>* list) {
	wxTextFile file(EINZELTERMINEFILE);
	file.Open();
	wxString line = file.GetFirstLine();
	for (; !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = zr.NextToken();
		wxString ort = zr.NextToken();
		wxString datum = zr.NextToken();
		wxString zeit_beginn = zr.NextToken();
		wxString bem = zr.NextToken();
		std::vector< std::pair<Dienst*, int> > tdlist;
		while (zr.HasMoreTokens()) {
			int d = wxAtoi(zr.NextToken());
			tdlist.push_back(std::make_pair(dlist->at(d), wxAtoi(zr.NextToken())));
		}
		list->push_back(new Einzeltermin(name, ort, datum, zeit_beginn, tdlist, bem));
	}
	file.Close();
}

void DataFileHandler::saveSerientermine(const std::vector<Serientermin*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(SERIENTERMINEFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		Serientermin t = *(list->at(i));
		wxString line = t.name + D + t.ort + D + wxString::Format(wxT("%i"), t.modus)
				+ D + wxString::Format(wxT("%i"), t.wochentag) + D + wxString::Format(wxT("%i"), t.n)
				+ D + t.zeit_beginn + D + t.datum_beginn + D + t.datum_ende + D + t.bem;
		for (std::vector< std::pair<Dienst*, int> >::iterator iter = t.dienste.begin(); iter != t.dienste.end(); iter++) {
			line += D + wxString::Format(wxT("%i"), iter->first->_id) + D + wxString::Format(wxT("%i"), iter->second);
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadSerientermine(std::vector<Dienst*>* dlist, std::vector<Serientermin*>* list) {
	wxTextFile file(SERIENTERMINEFILE);
	file.Open();
	wxString line = file.GetFirstLine();
	for (; !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxString name = zr.NextToken();
		wxString ort = zr.NextToken();
		int modus = wxAtoi(zr.NextToken());
		int wochentag = wxAtoi(zr.NextToken());
		int n = wxAtoi(zr.NextToken());
		wxString zeit_beginn = zr.NextToken();
		wxString datum_beginn = zr.NextToken();
		wxString datum_ende = zr.NextToken();
		wxString bem = zr.NextToken();
		std::vector< std::pair<Dienst*, int> > tdlist;
		while (zr.HasMoreTokens()) {
			int d = wxAtoi(zr.NextToken());
			tdlist.push_back(std::make_pair(dlist->at(d), wxAtoi(zr.NextToken())));
		}
		list->push_back(new Serientermin(name, ort, tdlist, zeit_beginn, datum_beginn, datum_ende, modus, wochentag, n, bem));
	}
	file.Close();
}

void DataFileHandler::saveMGruppen(const std::vector<MGruppe*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(MGRUPPENFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		MGruppe mg = *(list->at(i));
		wxString line = wxString::Format(wxT("%i"), mg.modus);
		for (std::vector<Messdiener*>::iterator iter = mg.list.begin(); iter != mg.list.end(); iter++) {
			line += D + wxString::Format(wxT("%i"), (**iter)._id);
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadMGruppen(std::vector<Messdiener*>* mlist, std::vector<MGruppe*>* list) {
	wxTextFile file(MGRUPPENFILE);
	file.Open();
	wxString line = file.GetFirstLine();
	for (; !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		int modus = wxAtoi(zr.NextToken());
		//Create MGruppe with correct indices
		std::vector<Messdiener*> gmlist;
		while (zr.HasMoreTokens()) {
			int m = wxAtoi(zr.NextToken());
			gmlist.push_back(mlist->at(m));
		}
		list->push_back(new MGruppe(modus, gmlist));
	}
	file.Close();
}

void DataFileHandler::saveTGruppen(const std::vector<TGruppe*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(TGRUPPENFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		TGruppe tg = *(list->at(i));
		wxString line = wxString::Format(wxT("%i"), tg.wochentag);
		file.AddLine(line);
		line = wxT("");
		for (std::vector<Einzeltermin*>::iterator iter = tg.list_einzel.begin(); iter != tg.list_einzel.end(); iter++) {
			line += wxString::Format(wxT("%i"), (**iter)._id);
			if ((iter + 1) != tg.list_einzel.end()) {
				line += D;
			}
		}
		file.AddLine(line);
		line = wxT("");
		for (std::vector<Serientermin*>::iterator iter = tg.list_serie.begin(); iter != tg.list_serie.end(); iter++) {
			line += wxString::Format(wxT("%i"), (**iter)._id);
			if ((iter + 1) != tg.list_serie.end()) {
				line += D;
			}
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadTGruppen(std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<TGruppe*>* list) {
	wxTextFile file(TGRUPPENFILE);
	file.Open();
	wxString line = file.GetFirstLine();
	for (; !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		int wochentag = wxAtoi(zr.NextToken());
		line = file.GetNextLine();
		std::vector<Einzeltermin*> gelist;
		wxStringTokenizer zr2(line, D, wxTOKEN_RET_EMPTY_ALL);
		while (zr2.HasMoreTokens()) {
			int e = wxAtoi(zr2.NextToken());
			gelist.push_back(elist->at(e));
		}
		line = file.GetNextLine();
		std::vector<Serientermin*> gslist;
		wxStringTokenizer zr3(line, D, wxTOKEN_RET_EMPTY_ALL);
		while (zr3.HasMoreTokens()) {
			int s = wxAtoi(zr3.NextToken());
			gslist.push_back(slist->at(s));
		}
		list->push_back(new TGruppe(wochentag, gelist, gslist));
	}
	file.Close();
}

void DataFileHandler::saveFehlzeiten(const std::vector<Fehlzeit*>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(FEHLZEITENFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (int i = 0; i < (int) list->size(); i++) {
		Fehlzeit f = *(list->at(i));
		wxString line = wxString::Format(wxT("%i"), f.modus) + D + wxString::Format(wxT("%i"), f.wochentag)
				+ D + f.beginn + D + f.ende + D + wxString::Format(wxT("%i"), f.mini->_id);
		if (f.modus == Fehlzeit::EINZELTERMIN) {
			line += D + wxString::Format(wxT("%i"), f.einzeltermin->_id);
		} else if (f.modus == Fehlzeit::SERIENTERMIN) {
			line += D + wxString::Format(wxT("%i"), f.serientermin->_id);
		}
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadFehlzeiten(std::vector<Messdiener*>* mlist, std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<Fehlzeit*>* list) {
	wxTextFile file(FEHLZEITENFILE);
	file.Open();
	wxString line = file.GetFirstLine();
	for (; !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		int modus = wxAtoi(zr.NextToken());
		int wochentag = wxAtoi(zr.NextToken());
		wxString beginn = zr.NextToken();
		wxString ende = zr.NextToken();
		int m = wxAtoi(zr.NextToken());
		Messdiener* mini = mlist->at(m);
		if (modus == Fehlzeit::EINZELTERMIN) {
			int e = wxAtoi(zr.NextToken());
			Einzeltermin* einzeltermin = elist->at(e);
			list->push_back(new Fehlzeit(mini, einzeltermin));
		} else if (modus == Fehlzeit::SERIENTERMIN) {
			int s = wxAtoi(zr.NextToken());
			Serientermin* serientermin = slist->at(s);
			list->push_back(new Fehlzeit(mini, serientermin));
		} else if (modus == Fehlzeit::WOCHENTAG) {
			list->push_back(new Fehlzeit(mini, wochentag, beginn, ende));
		} else {// Fehlzeit::ZEITRAUM
			list->push_back(new Fehlzeit(mini, beginn, ende));
		}
	}
	file.Close();
}

void DataFileHandler::savePlanerInfos(std::vector<PlanerInfo>* list) {
	if (!wxDir::Exists(RES)) {
		wxDir::Make(RES);
	}
	wxTextFile file(PLANERINFOSFILE);
	if (!file.Exists()) {
		file.Create();
	}
	file.Open();
	file.Clear();
	for (std::vector<PlanerInfo>::iterator iter = list->begin(); iter != list->end(); iter++) {
		wxString line = Util::wxDateTime_to_wxString(iter->datum_beginn) + D + Util::wxDateTime_to_wxString(iter->datum_ende) + D + wxString::Format(wxT("%i"), iter->counter);
		file.AddLine(line);
	}
	file.Write();
	file.Close();
}

void DataFileHandler::loadPlanerInfos(std::vector<PlanerInfo>* list) {
	wxTextFile file(PLANERINFOSFILE);
	file.Open();
	for (wxString line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()) {
		wxStringTokenizer zr(line, D, wxTOKEN_RET_EMPTY_ALL);
		wxDateTime beginn = Util::wxString_to_wxDateTime(zr.NextToken());
		wxDateTime ende = Util::wxString_to_wxDateTime(zr.NextToken());
		int counter = wxAtoi(zr.NextToken());
		list->push_back(PlanerInfo(beginn, ende, counter));
	}
	file.Close();
}