/* 
 * File:   Fehlzeit.cpp
 * Author: Yannik
 * 
 * Created on August 23, 2015, 12:40 PM
 */

#include "Fehlzeit.h"
#include "../Util.h"
#include "../R.h"

Fehlzeit::Fehlzeit() {

}

Fehlzeit::Fehlzeit(Messdiener* _mini, wxString _datum_beginn, wxString _datum_ende)
: mini(_mini), modus(ZEITRAUM), beginn(_datum_beginn), ende(_datum_ende) {
}

Fehlzeit::Fehlzeit(Messdiener* _mini, int _wochentag, wxString _zeit_beginn, wxString _zeit_ende)
: mini(_mini), modus(WOCHENTAG), wochentag(_wochentag), beginn(_zeit_beginn), ende(_zeit_ende) {

}

Fehlzeit::Fehlzeit(Messdiener* _mini, Einzeltermin* _einzeltermin)
: mini(_mini), modus(EINZELTERMIN), einzeltermin(_einzeltermin) {

}

Fehlzeit::Fehlzeit(Messdiener* _mini, Serientermin* _serientermin)
: mini(_mini), modus(SERIENTERMIN), serientermin(_serientermin) {

}

bool Fehlzeit::cmp(const Fehlzeit* f1, const Fehlzeit* f2) {
	if (Messdiener::equal(f1->mini, f2->mini)) {
		if (f1->modus == f2->modus) {
			switch (f1->modus) {
				case Fehlzeit::ZEITRAUM:
					return Util::wxString_to_wxDateTime(f1->ende).IsLaterThan(Util::wxString_to_wxDateTime(f2->ende));
				case Fehlzeit::WOCHENTAG:
					return f1->wochentag > f2->wochentag;
				case Fehlzeit::EINZELTERMIN:
					return f1->einzeltermin > f2->einzeltermin;
				default:
					return f1->serientermin > f2->serientermin;
			}
		}
		return f1->modus > f2->modus;
	}
	return Messdiener::cmp(f1->mini, f2->mini);
}

bool Fehlzeit::equal(const Fehlzeit* f1, const Fehlzeit* f2) {
	return f1->mini == f2->mini && f1->modus == f2->modus && f1->beginn.IsSameAs(f2->beginn) && f1->ende.IsSameAs(f2->ende) 
			&& f1->wochentag == f2->wochentag && f1->einzeltermin == f2->einzeltermin && f1->serientermin == f2->serientermin;
}

wxString Fehlzeit::printModus(const Fehlzeit* f) {
	wxString s;
	switch (f->modus) {
		case ZEITRAUM:
			s = f->beginn + wxT(" - ") + f->ende;
			break;
		case WOCHENTAG:
			s = R::WOECHENTLICH + wxT(": ") + R::WOCHENTAGE[f->wochentag] + wxT(" ") + f->beginn + wxT(" - ") + f->ende;
			break;
		case EINZELTERMIN:
			s = R::TERMIN + wxT(": ") + Einzeltermin::printShort(f->einzeltermin);
			break;
		case SERIENTERMIN:
			s = R::TERMIN + wxT(": ") + Serientermin::printShort(f->serientermin);
	}
	return s;
}