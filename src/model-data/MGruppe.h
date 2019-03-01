/* 
 * File:   MGruppe.h
 * Author: Yannik
 *
 * Created on August 13, 2015, 11:50 AM
 */

#ifndef MGRUPPE_H
#define	MGRUPPE_H

#include <vector>
#include "Messdiener.h"

class MGruppe {
public:
	static const int BEV_GEM = 0; //bevorzugt gemeinsam
	static const int NUR_GEM = 1; //nur gemeinsam
	int modus = 0;
	std::vector<Messdiener*> list;
	
	MGruppe(int _modus, std::vector<Messdiener*> _list);
	static bool cmp(const MGruppe* m1, const MGruppe* m2);
	static wxString printShort(MGruppe* m);
private:
};

#endif	/* MGRUPPE_H */