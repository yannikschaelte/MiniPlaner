/* 
 * File:   PlanerInfo.h
 * Author: Yannik
 *
 * Created on September 12, 2015, 7:20 PM
 */

#ifndef PLANERINFO_H
#define	PLANERINFO_H

#include <wx/datetime.h>
#include <wx/string.h>

class PlanerInfo {
public:
	wxDateTime datum_beginn;
	wxDateTime datum_ende;
	int counter;
	PlanerInfo(wxDateTime _datum_beginn, wxDateTime _datum_ende, int _counter);
	wxString getDir();
	wxString printShort();
	static bool cmp(const PlanerInfo& p1, const PlanerInfo& p2);
private:

};

#endif	/* PLANERINFO_H */

