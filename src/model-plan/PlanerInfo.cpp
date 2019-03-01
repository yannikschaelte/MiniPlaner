/* 
 * File:   PlanerInfo.cpp
 * Author: Yannik
 * 
 * Created on September 12, 2015, 7:20 PM
 */

#include "PlanerInfo.h"
#include "../Util.h"

PlanerInfo::PlanerInfo(wxDateTime _datum_beginn, wxDateTime _datum_ende, int _counter)
: datum_beginn(_datum_beginn), datum_ende(_datum_ende), counter(_counter) {

}

wxString PlanerInfo::getDir() {
	if (counter == 1) {
		return datum_beginn.Format(wxT("%Y-%m-%d")) + wxT("_") + datum_ende.Format(wxT("%Y-%m-%d"));
	} else {
		return datum_beginn.Format(wxT("%Y-%m-%d")) + wxT("_") + datum_ende.Format(wxT("%Y-%m-%d") + wxString::Format(wxT("(%i)"), counter));
	}
}

wxString PlanerInfo::printShort() {
	wxString s = Util::wxDateTime_to_wxString(datum_beginn) + wxT(" - ") + Util::wxDateTime_to_wxString(datum_ende);
	if (counter != 1) {
		s += wxString::Format(wxT(" (%i)"), counter);
	}
	return s;
}

bool PlanerInfo::cmp(const PlanerInfo& p1, const PlanerInfo& p2) {
	if (p1.datum_beginn.IsSameDate(p2.datum_beginn)) {
		return p1.datum_ende.IsEarlierThan(p2.datum_ende);
	}
	return p1.datum_beginn.IsEarlierThan(p2.datum_beginn);
}
