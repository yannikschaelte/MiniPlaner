/* 
 * File:   CSVExport.h
 * Author: Yannik
 *
 * Created on October 1, 2015, 11:01 AM
 */

#ifndef CSVEXPORT_H
#define	CSVEXPORT_H

#include "ExportLayout.h"
#include "../model-plan/Planer.h"
#include "../file/DataFileHandler.h"

namespace CSVExport {
	inline const wxString& D = DataFileHandler::D;  // reference: avoids static-init-order crash
	const wxString N = wxT("\n");
	wxString createCSV(ExportLayout* layout, Planer* planer);
};

#endif	/* CSVEXPORT_H */