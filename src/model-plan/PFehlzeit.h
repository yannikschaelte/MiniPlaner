/* 
 * File:   PFehlzeit.h
 * Author: Yannik
 *
 * Created on October 6, 2015, 11:14 PM
 */

#ifndef PFEHLZEIT_H
#define	PFEHLZEIT_H

#include <wx/datetime.h>
#include "PMessdiener.h"

class PFehlzeit {
public:
	PFehlzeit(PMessdiener* _mini, wxDateTime _datum_beginn, wxDateTime _datum_ende);
	PMessdiener* mini;
	wxDateTime datum_beginn;
	wxDateTime datum_ende;
	
	int _id;
private:

};

#endif	/* PFEHLZEIT_H */

