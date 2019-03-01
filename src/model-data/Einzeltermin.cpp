/* 
 * File:   Einzeltermin.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 6:22 PM
 */

#include "Einzeltermin.h"
#include "../Util.h"
#include "../R.h"

Einzeltermin::Einzeltermin() {

}

Einzeltermin::Einzeltermin(wxString _name, wxString _ort, wxString _datum, wxString _zeit_beginn, std::vector< std::pair<Dienst*, int> > _dienste, wxString _bem)
: name(_name), ort(_ort), datum(_datum), zeit_beginn(_zeit_beginn), dienste(_dienste), bem(_bem) {

}

bool Einzeltermin::cmp(const Einzeltermin* e1, const Einzeltermin* e2) {
	if (e1->datum.IsSameAs(e2->datum)) {
		return e1->zeit_beginn.Cmp(e2->zeit_beginn) < 0;
	}
	return Util::wxString_to_wxDateTime(e1->datum).IsEarlierThan(Util::wxString_to_wxDateTime(e2->datum));
}

bool Einzeltermin::equal(const Einzeltermin* e1, const Einzeltermin* e2) {
	return e1->datum.IsSameAs(e2->datum) && e1->ort.IsSameAs(e2->ort) && e1->zeit_beginn.IsSameAs(e2->zeit_beginn);
}

wxString Einzeltermin::printDienste(const Einzeltermin* e) {
	int num_dienste = e->dienste.size();
	wxString s_dienste;
	for (int i = 0; i < num_dienste; i++) {
		s_dienste += wxString::Format(wxT("%i"), e->dienste.at(i).second) + wxT(" ") + e->dienste.at(i).first->name;
		if (i < num_dienste - 1) {
			s_dienste += wxT(", ");
		}
	}
	return s_dienste;
}

wxString Einzeltermin::printShort(const Einzeltermin* e) {
	wxString ss;
	if (!e->name.IsEmpty()) {
		ss += e->name + wxT(": ");
	}
	if (!e->ort.IsEmpty()) {
		ss += e->ort + wxT(", ");
	}
	ss += e->datum + wxT(" (") + R::WOCHENTAGE[Util::wxString_to_wxDateTime(e->datum).GetWeekDay()] + wxT("), ") + e->zeit_beginn
			+ wxT(", ") + printDienste(e);
	return ss;
}
