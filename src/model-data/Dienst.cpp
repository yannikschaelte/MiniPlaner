/* 
 * File:   Dienst.cpp
 * Author: Yannik
 * 
 * Created on August 19, 2015, 11:34 AM
 */

#include <utility>

#include "Dienst.h"

Dienst::Dienst(wxString _name)
: name(_name) {

}

bool Dienst::equal(const Dienst* d1, const Dienst* d2) {
	return d1->name.IsSameAs(d2->name);
}

bool Dienst::cmp(const Dienst* d1, const Dienst* d2) {
	return d1->name.compare(d2->name) < 0 ? true : false;
}

bool Dienst::cmp2(const std::pair<Dienst*, int>& d1, const std::pair<Dienst*, int>& d2) {
	return Dienst::cmp(d1.first, d2.first);
}