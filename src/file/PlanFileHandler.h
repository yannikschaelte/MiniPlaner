/* 
 * File:   PlanFileHandler.h
 * Author: Yannik
 *
 * Created on August 27, 2015, 9:06 PM
 */

#ifndef PLANFILEHANDLER_H
#define	PLANFILEHANDLER_H

#include "DataFileHandler.h"
#include "../model-plan/Planer.h"
#include "../model-plan/PlanerInfo.h"
#include "../controller-plan/PlanerController.h"

namespace PlanFileHandler {
	extern const wxString RES;
	extern const wxString D;
	extern const wxString DIENSTEFILE;
	extern const wxString MINISFILE;
	extern const wxString TERMINEFILE;
	extern const wxString MGRUPPENFILE;
	extern const wxString FEHLZEITENFILE;
	extern const wxString SETTINGSFILE;
	extern PlanerInfo createDir(wxDateTime datum_beginn, wxDateTime datum_ende);
	extern void deleteDir(PlanerInfo info);
	extern void savePlaner(Planer* planer);
	extern void loadPlaner(Planer* planer);
};

#endif	/* PLANFILEHANDLER_H */