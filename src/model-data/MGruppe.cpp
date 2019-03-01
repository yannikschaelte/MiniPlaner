/* 
 * File:   MGruppe.cpp
 * Author: Yannik
 * 
 * Created on August 13, 2015, 11:50 AM
 */

#include "MGruppe.h"
#include <algorithm>

MGruppe::MGruppe(int _modus, std::vector<Messdiener*> _list)
: modus(_modus), list(_list) {
}

bool MGruppe::cmp(const MGruppe* m1, const MGruppe* m2) {
	return Messdiener::cmp(m1->list.front(), m2->list.front());
}

wxString MGruppe::printShort(MGruppe* mg) {
	Messdiener m = *(mg->list.at(0));
	wxString s = m.vorname + wxT(" ") + m.name;
	std::vector<Messdiener*>::iterator iter = mg->list.begin();
	iter++;
	for (; iter != mg->list.end(); iter++) {
		s += wxT(", ") + (**iter).vorname + wxT(" ") + (**iter).name;
	}
	return s;
}