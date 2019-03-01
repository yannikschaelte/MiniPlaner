/* 
 * File:   PMessdiener.h
 * Author: Yannik
 *
 * Created on August 27, 2015, 2:45 PM
 */

#ifndef PMESSDIENER_H
#define	PMESSDIENER_H

#include <wx/string.h>
#include <vector>
#include "../model-data/Dienst.h"
class PMGruppe;

class PMessdiener {
public:
	wxString name;
	wxString vorname;
	std::vector<Dienst*> dienste;
	PMGruppe* gruppe;
	int num;
	
	int _id;
	
	PMessdiener(wxString _name, wxString _vorname, std::vector<Dienst*> _dienste);
	PMessdiener(wxString _name, wxString _vorname, std::vector<Dienst*> _dienste, int _num);
	static bool cmp(const PMessdiener* m1, const PMessdiener* m2);
	static wxString printDienste(const PMessdiener* m);
private:

};

#endif	/* PMESSDIENER_H */

