/* 
 * File:   Util.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 11:36 AM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <wx/datetime.h>
#include <wx/string.h>
#include <vector>
#include "model-plan/PMessdiener.h"
#include "model-plan/PTermin.h"

namespace Util {
	extern wxDateTime wxString_to_wxDateTime(const wxString& s);
	extern wxString wxDateTime_to_wxString(const wxDateTime& d);
	//return dd.mm.yyyy if s valid date, else false and empty target string
	extern bool formatDate(const wxString& s, wxString* target);
	//return true and hh:mm if valid time, else false
	extern bool formatTime(const wxString& s, wxString* target);
	extern wxString rmD(const wxString& s);
	extern void erase_from_minivec(std::vector<PMessdiener*>* list, PMessdiener* mini);
	extern void setMiniNums(std::vector<PMessdiener*>* mlist, std::vector<PTermin*>* tlist);

	enum Wochentag {
		SONNTAG,
		MONTAG,
		DIENSTAG,
		MITTWOCH,
		DONNERSTAG,
		FREITAG,
		SAMSTAG
	};

	enum MONATSWOCHE {
		ERSTER,
		ZWEITER,
		DRITTER,
		VIERTER,
		FUENFTER,
		VORLETZTER,
		LETZTER
	};
};

#endif	/* UTIL_H */