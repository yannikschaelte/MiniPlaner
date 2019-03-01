/* 
 * File:   Planer.cpp
 * Author: Yannik
 * 
 * Created on September 11, 2015, 10:32 AM
 */

#include "Planer.h"
#include "../Util.h"

Planer::Planer(wxDateTime _datum_beginn, wxDateTime _datum_ende, int _counter)
: datum_beginn(_datum_beginn), datum_ende(_datum_ende), counter(_counter) {

}

Planer::Planer(wxDateTime _datum_beginn, wxDateTime _datum_ende, std::vector<Dienst*> _list_dienst,
		std::vector<PTermin*> _list_termin, std::vector<PMessdiener*> _list_mini, std::vector<PMGruppe*> _list_mgruppe, std::vector<PFehlzeit*> _list_fehlzeit,
		int _counter)
: datum_beginn(_datum_beginn), datum_ende(_datum_ende), list_dienst(_list_dienst), list_termin(_list_termin), list_mini(_list_mini),
list_mgruppe(_list_mgruppe), list_fehlzeit(_list_fehlzeit), counter(_counter) {

}

Planer::~Planer() {
	for (std::vector<Dienst*>::iterator iter = list_dienst.begin(); iter != list_dienst.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PTermin*>::iterator iter = list_termin.begin(); iter != list_termin.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PMessdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PMGruppe*>::iterator iter = list_mgruppe.begin(); iter != list_mgruppe.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PFehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end(); iter++) {
		delete *iter;
	}
}

wxString Planer::printShort() {
	wxString s = Util::wxDateTime_to_wxString(datum_beginn) + wxT(" - ") + Util::wxDateTime_to_wxString(datum_ende);
	if (counter != 1) {
		s += wxString::Format(wxT(" (%i)"), counter);
	}
	return s;
}

wxString Planer::getDir() {
	if (counter == 1) {
		return datum_beginn.Format(wxT("%Y-%m-%d")) + wxT("_") + datum_ende.Format(wxT("%Y-%m-%d"));
	} else {
		return datum_beginn.Format(wxT("%Y-%m-%d")) + wxT("_") + datum_ende.Format(wxT("%Y-%m-%d") + wxString::Format(wxT("(%i)"), counter));
	}
}
