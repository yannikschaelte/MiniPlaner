/* 
 * File:   HTMLExport.h
 * Author: Yannik
 *
 * Created on October 1, 2015, 10:51 AM
 */

#ifndef HTMLEXPORT_H
#define	HTMLEXPORT_H

#include "ExportLayout.h"
#include "../model-plan/Planer.h"

namespace HTMLExport {
	wxString createHTML(ExportLayout* layout, Planer* planer, bool pv);
	void addHead(wxString* page);
	int getCols(ExportLayout* layout);
};

#endif	/* HTMLEXPORT_H */

