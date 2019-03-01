/* 
 * File:   ExportLayout.h
 * Author: Yannik
 *
 * Created on October 1, 2015, 10:53 AM
 */

#ifndef EXPORTLAYOUT_H
#define	EXPORTLAYOUT_H

#include <wx/string.h>
#include "../model-plan/PMessdiener.h"

class ExportLayout {
public:
	wxString title;
	bool showDienste;
	int modus_minis;
	int n;
	int modus_basics;
	int modus_namen;

	static const int MODUS_MINIS_CELLS = 0;
	static const int MODUS_MINIS_ROW = 1;
	static const int MODUS_BASICS_LEFT = 0;
	static const int MODUS_BASICS_ABOVE = 1;
	static const int MODUS_NAMEN_VORNAME_NACHNAME = 0;
	static const int MODUS_NAMEN_V_NACHNAME = 1;
	static const int MODUS_NAMEN_VORNAME_N = 2;
	static const int MODUS_NAMEN_VORNAME = 3;

	wxString createName(PMessdiener* mini);
};

#endif	/* EXPORTLAYOUT_H */