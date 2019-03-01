/* 
 * File:   PTermin.h
 * Author: Yannik
 *
 * Created on August 27, 2015, 2:45 PM
 */

#ifndef PTERMIN_H
#define	PTERMIN_H

#include <wx/string.h>
#include <wx/datetime.h>
#include <vector>
#include "PMessdiener.h"
#include "../model-data/Dienst.h"

class PTermin {
public:
	wxString name;
	wxString ort;
	wxDateTime datum;
	wxString zeit_beginn;
	wxString bem;
	
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis;
	std::vector<std::pair<Dienst*, int> > list_dienst_num;
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis_possible; //in total
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis_available; //can still be distributed
	
	PTermin* next;
	PTermin* prev;
	
	int _id;

	PTermin(wxString _name, wxString _ort, wxDateTime _datum, wxString _zeit_beginn, wxString _bem, std::vector<std::pair<Dienst*, int> > _list_dienst_num);
	static wxString printDienste(const PTermin* t);
	static wxString printShort(const PTermin* t);
	static wxString printBasics(const PTermin* t);
	static bool cmp(const PTermin* t1, const PTermin* t2);
	static void sortGruppe(PTermin* t);
private:

};

#endif	/* PTERMIN_H */

