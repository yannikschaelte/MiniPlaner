/* 
 * File:   Serientermin.cpp
 * Author: Yannik
 * 
 * Created on August 12, 2015, 6:22 PM
 */

#include "Serientermin.h"
#include "../R.h"
#include "../Util.h"

Serientermin::Serientermin() {

}

Serientermin::Serientermin(wxString _name, wxString _ort, std::vector< std::pair<Dienst*, int> > _dienste, wxString _zeit_beginn, wxString _datum_beginn, wxString _datum_ende,
		int _modus, int _wochentag, int _n, wxString _bem)
: name(_name), ort(_ort), dienste(_dienste), zeit_beginn(_zeit_beginn), datum_beginn(_datum_beginn), datum_ende(_datum_ende),
modus(_modus), wochentag(_wochentag), n(_n), bem(_bem) {

}

bool Serientermin::cmp(const Serientermin* s1, const Serientermin* s2) {
	if (s1->modus == s2->modus) {
		if (s1->wochentag == s2->wochentag) {
			return s1->zeit_beginn.Cmp(s2->zeit_beginn) < 0;
		}
		return s1->wochentag < s2->wochentag;
	}
	return s1->modus < s2->modus;
}

bool Serientermin::equal(const Serientermin* s1, const Serientermin* s2) {
	return s1->ort.IsSameAs(s2->ort) && s1->datum_beginn.IsSameAs(s2->datum_beginn) && s1->datum_ende.IsSameAs(s2->datum_ende)
			&& s1->modus == s2->modus && s1->n == s2->n
			&& s1->wochentag == s2->wochentag && s1->zeit_beginn.IsSameAs(s2->zeit_beginn);
}

wxString Serientermin::printDienste(const Serientermin* s) {
	int num_dienste = s->dienste.size();
	wxString s_dienste;
	for (int i = 0; i < num_dienste; i++) {
		s_dienste += wxString::Format(wxT("%i"), s->dienste.at(i).second) + wxT(" ") + s->dienste.at(i).first->name;
		if (i < num_dienste - 1) {
			s_dienste += wxT(", ");
		}
	}
	return s_dienste;
}

wxString Serientermin::printModus(const Serientermin* s) {
	wxString t_modus = R::TMODI[s->modus];
	switch (s->modus) {
		case TAEGLICH:
			break;
		case WOECHENTLICH:
			t_modus += wxT(": ") + R::WOCHENTAGE[s->wochentag];
			break;
		case GERADE_KW:
			t_modus += wxT(": ") + R::WOCHENTAGE[s->wochentag];
			break;
		case UNGERADE_KW:
			t_modus += wxT(": ") + R::WOCHENTAGE[s->wochentag];
			break;
		case N_WOECHENTLICH:
			t_modus = wxString::Format(wxT("%i"), s->n) + wxT("-wöchentlich am ") + R::WOCHENTAGE[s->wochentag] + wxT(", ab (inkl.) der Woche nach [Anfangsdatum]");
			break;
		case W_IM_MONAT:
			if (s->n < 5) {
				t_modus = wxString::Format(wxT("%i"), s->n + 1) + wxT(".");
			} else if (s->n == 5) {
				t_modus = R::VORLETZTER;
			} else {
				t_modus = R::LETZTER;
			}
			t_modus += wxT(" ") + R::WOCHENTAGE[s->wochentag] + wxT(" im Monat");
			break;
		case MONATLICH:
			t_modus += wxT(": ") + wxString::Format(wxT("%i"), s->n) + wxT(".");
			break;
	}
	return t_modus;
}

wxString Serientermin::printShort(const Serientermin* s) {
	wxString ss;
	if (!s->name.IsEmpty()) {
		ss += s->name + wxT(": ");
	}
	if (!s->ort.IsEmpty()) {
		ss += s->ort + wxT(", ");
	}
	ss += printModus(s) + wxT(", ") + s->zeit_beginn;
	if (!s->datum_beginn.IsEmpty()) {
		if (!s->datum_ende.IsEmpty()) {
			ss += wxT(", ") + s->datum_beginn + wxT(" bis ") + s->datum_ende;
		} else {
			ss += wxT(", ab ") + s->datum_beginn;
		}
	} else {
		if (!s->datum_ende.IsEmpty()) {
			ss += wxT(", bis ") + s->datum_ende;
		}
	}
	ss += wxT(", ") + printDienste(s);
	return ss;
}
