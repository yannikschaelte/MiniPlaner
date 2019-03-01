/* 
 * File:   Util.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 11:36 AM
 */

#include "Util.h"
#include "R.h"
#include <wx/tokenzr.h>
#include "file/DataFileHandler.h"

wxDateTime Util::wxString_to_wxDateTime(const wxString& s) {
	wxStringTokenizer zr(s, wxT("./"));
	if (zr.CountTokens() != 3) {
		return wxDateTime::Today();
	}
	int day, month, year;
	day = wxAtoi(zr.NextToken());
	month = wxAtoi(zr.NextToken());
	year = wxAtoi(zr.NextToken());
	return wxDateTime(day, wxDateTime::Month(month - 1), year);
}

wxString Util::wxDateTime_to_wxString(const wxDateTime& d) {
	if (R::lang == R::LANG_DE)
		return d.Format(wxT("%d.%m.%Y"));
	else
		return d.Format(wxT("%d/%m/%Y"));
}

bool Util::formatDate(const wxString& s, wxString* target) {
	*target = wxT("");
	wxStringTokenizer date_zr(s, wxT("."), wxTOKEN_RET_EMPTY_ALL);
	if (date_zr.CountTokens() != 3) return false;
	else {
		long day, month_i, year;
		bool day_b = date_zr.NextToken().ToLong(&day, 10);
		bool month_b = date_zr.NextToken().ToLong(&month_i, 10);
		bool year_b = date_zr.NextToken().ToLong(&year, 10);
		if (!day_b || !month_b || !year_b || day < 1 || month_i < 1 || year < 0 || day > 31 || month_i > 12) return false;
		else {
			wxDateTime::Month month = wxDateTime::Month(month_i - 1);
			if (day > wxDateTime::GetNumberOfDays(month, year)) return false;
			else {
				wxDateTime date(day, month, year);
				if (!date.IsValid()) return false;
				else *target = Util::wxDateTime_to_wxString(date);
			}
		}
	}
	return true;
}

bool Util::formatTime(const wxString& s, wxString* target) {
	wxStringTokenizer zr(s, ":");
	if (zr.CountTokens() != 2) {
		zr = wxStringTokenizer(s, ".");
		if (zr.CountTokens() != 2) return false;
	}
	long hour, minute;
	if (!zr.NextToken().ToLong(&hour, 10) || hour > 23 || hour < 0) {
		return false;
	}
	if (!zr.NextToken().ToLong(&minute, 10) || minute > 59 || minute < 0) {
		return false;
	}
	*target = wxT("");
	*target << wxString::Format(wxT("%02i"), hour) << wxT(":") << wxString::Format(wxT("%02i"), minute);

	return true;
}

/**
 * In every user input: Replace FileHandler::D, which is used as a divider in the
 * files, by a blank space character. Furthermore remove undesirable characters.
 * @param s user input string
 * @return transferred string
 */
wxString Util::rmD(const wxString& s) {
	wxString s2 = s;
	s2.Replace(wxT("\n"), wxT(" "));
	//other handling for html / xml / <-csv-output possible but not implemented
	s2.Replace(wxT("<"), wxT("&lt;"));
	s2.Replace(wxT(">"), wxT("&gt;"));

	s2.Replace(DataFileHandler::D, wxT(" "));
	return s2;
}

void Util::erase_from_minivec(std::vector<PMessdiener*>* list, PMessdiener* mini) {
	for (std::vector<PMessdiener*>::iterator iter = list->begin(); iter != list->end(); iter++) {
		if (*iter == mini) {
			list->erase(iter);
			return;
		}
	}
}

void Util::setMiniNums(std::vector<PMessdiener*>* mlist, std::vector<PTermin*>* tlist) {
	for (std::vector<PMessdiener*>::iterator iter_m = mlist->begin(); iter_m != mlist->end(); iter_m++) {
		(**iter_m).num = 0;
	}
	for (std::vector<PTermin*>::iterator iter_t = tlist->begin(); iter_t != tlist->end(); iter_t++) {
		for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_d = (**iter_t).list_dienst_minis.begin();
				iter_d != (**iter_t).list_dienst_minis.end(); iter_d++) {
			for (std::vector<PMessdiener*>::iterator iter_m = iter_d->second.begin(); iter_m != iter_d->second.end(); iter_m++) {
				if (*iter_m != NULL) (**iter_m).num++;
			}
		}
	}
}