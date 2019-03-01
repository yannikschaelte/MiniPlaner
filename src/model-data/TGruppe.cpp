/* 
 * File:   TGruppe.cpp
 * Author: Yannik
 * 
 * Created on August 16, 2015, 6:37 AM
 */

#include "TGruppe.h"
#include "../R.h"

TGruppe::TGruppe(int _wochentag, std::vector<Einzeltermin*> _list_einzel, std::vector<Serientermin*> _list_serie)
: wochentag(_wochentag), list_einzel(_list_einzel), list_serie(_list_serie) {
}

wxString TGruppe::printModus(const TGruppe* tgruppe) {
	if (tgruppe->list_serie.size() > 0) {
		return R::PERIODISCH + R::WOCHENTAGE[tgruppe->wochentag];
	} else {
		return R::NICHT_PERIODISCH;
	}
}
