/* 
 * File:   Messdiener.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 6:47 PM
 */

#include "Messdiener.h"

Messdiener::Messdiener() {

}

Messdiener::Messdiener(const wxString& _name, const wxString& _vorname, std::vector<Dienst*> _dienste, const wxString& _geburtstag,
		const wxString& _strasse_nr, const wxString& _plz_ort, const wxString& _tel,
		const wxString& _mobile, const wxString& _email, const wxString& _bem)
: name(_name), vorname(_vorname), dienste(_dienste), geburtstag(_geburtstag), strasse_nr(_strasse_nr),
plz_ort(_plz_ort), tel(_tel), mobile(_mobile), email(_email), bem(_bem) {

}

bool Messdiener::cmp(const Messdiener* m1, const Messdiener* m2) {
	if (m1->name.IsSameAs(m2->name)) {
		return m1->vorname.Cmp(m2->vorname) < 0;
	}
	return m1->name.Cmp(m2->name) < 0;
}

bool Messdiener::equal(const Messdiener* m1, const Messdiener* m2) {
	return m1->name.IsSameAs(m2->name) && m1->vorname.IsSameAs(m2->vorname);
}

wxString Messdiener::printDienste(const Messdiener* m) {
	int num_dienste = m->dienste.size();
	wxString s_dienste;
	for (int i = 0; i < num_dienste; i++) {
		s_dienste += m->dienste.at(i)->name;
		if (i < num_dienste - 1) {
			s_dienste += wxT(", ");
		}
	}
	return s_dienste;
}