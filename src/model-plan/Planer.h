/* 
 * File:   Planer.h
 * Author: Yannik
 *
 * Created on September 11, 2015, 10:32 AM
 */

#ifndef PLANER_H
#define	PLANER_H

#include <wx/string.h>
#include <wx/datetime.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "PTermin.h"
#include "PMessdiener.h"
#include "PMGruppe.h"
#include "PFehlzeit.h"

class Planer {
public:
	wxDateTime datum_beginn;
	wxDateTime datum_ende;
	std::vector<Dienst*> list_dienst;
	std::vector<PTermin*> list_termin;
	std::vector<PMessdiener*> list_mini;
	std::vector<PMGruppe*> list_mgruppe;
	std::vector<PFehlzeit*> list_fehlzeit;

	class Settings {
	public:
		const static int MODUS_FEHLZEITEN_ANRECHNEN = 0;
		const static int MODUS_FEHLZEITEN_KOMPENSIEREN = 1;
		const static int MODUS_ALGORITHMUS_MINIMUM = 0;
		const static int MODUS_ALGORITHMUS_CHRONOLOGISCH = 1;
		int modus_fehlzeiten = MODUS_FEHLZEITEN_KOMPENSIEREN;
		int modus_algorithmus = MODUS_ALGORITHMUS_CHRONOLOGISCH;
	} settings;

	int counter;
	Planer(wxDateTime _datum_beginn, wxDateTime _datum_ende, int _counter);
	Planer(wxDateTime _datum_beginn, wxDateTime _datum_ende, std::vector<Dienst*> _list_dienst,
			std::vector<PTermin*> _list_termin, std::vector<PMessdiener*> _list_mini, std::vector<PMGruppe*> _list_mgruppe, std::vector<PFehlzeit*> _list_fehlzeit,
			int _counter);
	~Planer();
	wxString printShort();
	wxString getDir();
private:
};

#endif	/* PLANER_H */

