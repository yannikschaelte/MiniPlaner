/* 
 * File:   TGruppe.h
 * Author: Yannik
 *
 * Created on August 16, 2015, 6:37 AM
 */

#ifndef TGRUPPE_H
#define	TGRUPPE_H

#include <wx/string.h>
#include <vector>
#include "Einzeltermin.h"
#include "Serientermin.h"

class TGruppe {
public:
	int wochentag;
	std::vector<Einzeltermin*> list_einzel;
	std::vector<Serientermin*> list_serie;
	
	TGruppe(int _wochentag, std::vector<Einzeltermin*> _list_einzel, std::vector<Serientermin*> _list_serie);
	static wxString printModus(const TGruppe* tgruppe);
private:
};

#endif	/* TGRUPPE_H */