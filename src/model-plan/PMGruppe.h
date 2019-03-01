/* 
 * File:   PMGruppe.h
 * Author: Yannik
 *
 * Created on September 7, 2015, 9:33 PM
 */

#ifndef PMGRUPPE_H
#define	PMGRUPPE_H

#include "PMessdiener.h"
#include <vector>

class PMGruppe {
public:
	int modus;
	std::vector<PMessdiener*> list;
	
	int _id;
	
	PMGruppe(int _modus, std::vector<PMessdiener*> _list);
	static wxString printShort(PMGruppe* m);
private:

};

#endif	/* PMGRUPPE_H */

