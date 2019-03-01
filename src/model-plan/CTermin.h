/* 
 * File:   CTermin.h
 * Author: Yannik
 *
 * Created on September 26, 2015, 10:40 PM
 */

#ifndef CTERMIN_H
#define	CTERMIN_H

#include <vector>
#include <unordered_set>
#include <wx/datetime.h>
#include "../model-plan/PMessdiener.h"
#include "../model-data/Dienst.h"

/**
 * Termin for computation.
 */
class CTermin {
public:
	std::vector<std::pair<Dienst*, std::unordered_set<PMessdiener*> > > list_dienst_minis;
	std::vector<std::pair<Dienst*, int> > list_dienst_req;
	std::vector<std::pair<Dienst*, std::unordered_set<PMessdiener*> > > list_dienst_minis_available;
	
	wxDateTime datum;

	CTermin* next;
	CTermin* prev;
	int _id;
	
	CTermin();
private:

};

#endif	/* CTERMIN_H */

