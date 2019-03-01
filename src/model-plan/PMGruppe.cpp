/* 
 * File:   PMGruppe.cpp
 * Author: Yannik
 * 
 * Created on September 7, 2015, 9:33 PM
 */

#include "PMGruppe.h"

PMGruppe::PMGruppe(int _modus, std::vector<PMessdiener*> _list)
: modus(_modus), list(_list) {

}

wxString PMGruppe::printShort(PMGruppe* mg) {
	PMessdiener m = *(mg->list.at(0));
	wxString s = m.vorname + wxT(" ") + m.name;
	std::vector<PMessdiener*>::iterator iter = mg->list.begin();
	iter++;
	for (; iter != mg->list.end(); iter++) {
		s += wxT(", ") + (**iter).vorname + wxT(" ") + (**iter).name;
	}
	return s;
}