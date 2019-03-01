/* 
 * File:   Serientermin.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 6:22 PM
 */

#ifndef SERIENTERMIN_H
#define	SERIENTERMIN_H

#include <wx/string.h>
#include "Dienst.h"
#include <vector>

class Serientermin {
public:
	static const int TAEGLICH = 0;
	static const int WOECHENTLICH = 1;
	static const int GERADE_KW = 2;
	static const int UNGERADE_KW = 3;
	static const int N_WOECHENTLICH = 4;
	static const int W_IM_MONAT = 5;
	static const int MONATLICH = 6;
	//Grunddaten
	wxString name;
	wxString ort;
	std::vector< std::pair<Dienst*, int> > dienste;
	wxString zeit_beginn;
	wxString datum_beginn;
	wxString datum_ende;
	int modus;
	//Modus-Daten
	int wochentag;
	int n;
	wxString bem;
	int _id;
	
	Serientermin();
	Serientermin(wxString _name, wxString _ort, std::vector< std::pair<Dienst*, int> > _dienste,
			wxString _zeit_beginn, wxString _datum_beginn, wxString _datum_ende, int _modus, int _wochentag, int _n, wxString _bem);
	static bool cmp(const Serientermin* s1, const Serientermin* s2);
	static bool equal(const Serientermin* s1, const Serientermin* s2);
	static wxString printDienste(const Serientermin* s);
	static wxString printModus(const Serientermin* s);
	static wxString printShort(const Serientermin* s);
private:

};

#endif	/* SERIENTERMIN_H */