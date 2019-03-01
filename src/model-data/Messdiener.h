/* 
 * File:   Messdiener.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 6:47 PM
 */

#ifndef MESSDIENER_H
#define	MESSDIENER_H

#include <wx/string.h>
#include <vector>
#include "Dienst.h"

class Messdiener {
public:
	static bool cmp(const Messdiener* m1, const Messdiener* m2);
	static bool equal(const Messdiener* m1, const Messdiener* m2);
	static wxString printDienste(const Messdiener* m);
	Messdiener();
	Messdiener(const wxString& _name, const wxString& _vorname, std::vector<Dienst*> _dienste, const wxString& _geburtstag,
			const wxString& _strasse_nr, const wxString& _plz_ort, const wxString& _tel,
			const wxString& _mobile, const wxString& _email, const wxString& _bem);

	wxString name;
	wxString vorname;
	std::vector<Dienst*> dienste;
	wxString geburtstag;
	wxString strasse_nr;
	wxString plz_ort;
	wxString tel;
	wxString mobile;
	wxString email;
	wxString bem;
	int _id;
private:

};

#endif	/* MESSDIENER_H */