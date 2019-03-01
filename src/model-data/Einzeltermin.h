/* 
 * File:   Einzeltermin.h
 * Author: Yannik
 *
 * Created on August 12, 2015, 6:22 PM
 */

#ifndef EINZELTERMIN_H
#define	EINZELTERMIN_H

#include <wx/string.h>
#include "Dienst.h"
#include <vector>

class Einzeltermin {
public:
	wxString name;
	wxString ort;
	wxString datum;
	wxString zeit_beginn;
	std::vector< std::pair<Dienst*, int> > dienste;
	wxString bem;
	int _id;
	
	Einzeltermin();
	Einzeltermin(wxString _name, wxString _ort, wxString _datum, wxString _zeit_beginn, std::vector< std::pair<Dienst*, int> > _dienste, wxString _bem);
	static bool cmp(const Einzeltermin* e1, const Einzeltermin* e2);
	static bool equal(const Einzeltermin* e1, const Einzeltermin* e2);
	static wxString printDienste(const Einzeltermin* e);
	static wxString printShort(const Einzeltermin* e);
private:

};

#endif	/* EINZELTERMIN_H */

