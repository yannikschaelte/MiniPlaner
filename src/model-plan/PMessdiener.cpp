/* 
 * File:   PMessdiener.cpp
 * Author: Yannik
 * 
 * Created on August 27, 2015, 2:45 PM
 */

#include "PMessdiener.h"
#include "PMGruppe.h"

PMessdiener::PMessdiener(wxString _name, wxString _vorname, std::vector<Dienst*> _dienste)
: name(_name), vorname(_vorname), dienste(_dienste) {
	num = 0;
	gruppe = NULL;
}

PMessdiener::PMessdiener(wxString _name, wxString _vorname, std::vector<Dienst*> _dienste, int _num)
: name(_name), vorname(_vorname), dienste(_dienste), num(_num) {
	gruppe = NULL;
}

bool PMessdiener::cmp(const PMessdiener* m1, const PMessdiener* m2) {
	if (m1->name.IsSameAs(m2->name)) {
		return m1->vorname.Cmp(m2->vorname) < 0;
	}
	return m1->name.Cmp(m2->name) < 0;
}

wxString PMessdiener::printDienste(const PMessdiener* m) {
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