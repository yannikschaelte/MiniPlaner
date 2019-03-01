/* 
 * File:   PTermin.cpp
 * Author: Yannik
 * 
 * Created on August 27, 2015, 2:45 PM
 */

#include "PTermin.h"
#include "../Util.h"
#include "../R.h"

PTermin::PTermin(wxString _name, wxString _ort, wxDateTime _datum, wxString _zeit_beginn, wxString _bem, std::vector<std::pair<Dienst*, int> > _list_dienst_num)
: name(_name), ort(_ort), datum(_datum), zeit_beginn(_zeit_beginn), bem(_bem), list_dienst_num(_list_dienst_num) {
	next = (PTermin*) NULL;
	prev = (PTermin*) NULL;
}

wxString PTermin::printDienste(const PTermin* t) {
	int num_dienste = t->list_dienst_num.size();
	wxString s_dienste;
	for (int i = 0; i < num_dienste; i++) {
		s_dienste += wxString::Format(wxT("%i"), t->list_dienst_num.at(i).second) + wxT(" ") + t->list_dienst_num.at(i).first->name;
		if (i < num_dienste - 1) {
			s_dienste += wxT(", ");
		}
	}
	return s_dienste;
}

wxString PTermin::printShort(const PTermin* t) {
	wxString ss;
	if (!t->name.IsEmpty()) {
		ss += t->name + wxT(": ");
	}
	if (!t->ort.IsEmpty()) {
		ss += t->ort + wxT(", ");
	}
	ss += Util::wxDateTime_to_wxString(t->datum) + wxT(" (") + R::WOCHENTAGE[t->datum.GetWeekDay()] + wxT("), ") + t->zeit_beginn
			+ wxT(", ") + printDienste(t);
	return ss;
}

wxString PTermin::printBasics(const PTermin* t) {
	wxString ss = R::WOCHENTAGE[t->datum.GetWeekDay()] + wxT(" ") + Util::wxDateTime_to_wxString(t->datum) + wxT(" ") + t->zeit_beginn;
	if (!t->name.IsEmpty()) {
		ss += wxT(" (") + t->name + wxT(")");
	}
	if (!t->ort.IsEmpty()) {
		ss += wxT(", ") + t->ort;
	}
	return ss;
}

bool PTermin::cmp(const PTermin* t1, const PTermin* t2) {
	if (t1->datum.IsSameDate(t2->datum)) {
		return t1->zeit_beginn.Cmp(t2->zeit_beginn) < 0;
	}
	return t1->datum.IsEarlierThan(t2->datum);
}

void PTermin::sortGruppe(PTermin* t) {
	while(t->next != NULL && !PTermin::cmp(t, t->next)) {
		PTermin* t3 = t->next;
		t->next = t3->next;
		t3->next = t;
		t3->prev = t->prev;
		t->prev = t3;
	}
	while(t->prev != NULL && !PTermin::cmp(t->prev, t)) {
		PTermin* t3 = t->prev;
		t3->next = t->next;
		t->next = t3;
		t->prev = t3->prev;
		t3->prev = t;
	}
}