/* 
 * File:   Fehlzeit.h
 * Author: Yannik
 *
 * Created on August 23, 2015, 12:40 PM
 */

#ifndef FEHLZEIT_H
#define	FEHLZEIT_H

#include <wx/string.h>
#include "Messdiener.h"
#include "Einzeltermin.h"
#include "Serientermin.h"

class Fehlzeit {
public:
	static const int ZEITRAUM = 0;
	static const int WOCHENTAG = 1;
	static const int EINZELTERMIN = 2;
	static const int SERIENTERMIN = 3;
	static bool cmp(const Fehlzeit* f1, const Fehlzeit* f2);
	static bool equal(const Fehlzeit* f1, const Fehlzeit* f2);
	static wxString printModus(const Fehlzeit* f);
	Messdiener* mini;
	int modus = 0;
	int wochentag = 0;
	wxString beginn; //date or time
	wxString ende; //date or time
	Einzeltermin* einzeltermin = NULL;
	Serientermin* serientermin = NULL;
	
	Fehlzeit();
	Fehlzeit(Messdiener* _mini, wxString _datum_beginn, wxString _datum_ende);
	Fehlzeit(Messdiener* _mini, int _wochentag, wxString _zeit_beginn, wxString _zeit_ende);
	Fehlzeit(Messdiener* _mini, Einzeltermin* _einzeltermin);
	Fehlzeit(Messdiener* _mini, Serientermin* _serientermin);
private:

};

#endif	/* FEHLZEIT_H */

