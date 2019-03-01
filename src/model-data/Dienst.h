/* 
 * File:   Dienst.h
 * Author: Yannik
 *
 * Created on August 19, 2015, 11:33 AM
 */

#ifndef DIENST_H
#define	DIENST_H

#include <wx/string.h>

class Dienst {
public:
	wxString name;
	int _id;
	Dienst(wxString _name);
	static bool equal(const Dienst* d1, const Dienst* d2);
	static bool cmp(const Dienst* d1, const Dienst* d2);
	static bool cmp2(const std::pair<Dienst*, int>& d1, const std::pair<Dienst*, int>& d2);
private:
};

#endif	/* DIENST_H */