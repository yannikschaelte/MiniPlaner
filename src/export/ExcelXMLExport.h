/* 
 * File:   ExcelXMLExport.h
 * Author: Yannik
 *
 * Created on October 1, 2015, 11:01 AM
 */

#ifndef EXCELXMLEXPORT_H
#define	EXCELXMLEXPORT_H

#include "ExportLayout.h"
#include "../model-plan/Planer.h"

namespace ExcelXMLExport {
	wxString createExcelXML(ExportLayout* layout, Planer* planer);
	int getCols(ExportLayout* layout);
};

#endif	/* EXCELXMLEXPORT_H */

