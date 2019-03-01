/* 
 * File:   DataFileHandler.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:44 PM
 */

#ifndef DATAFILEHANDLER_H
#define	DATAFILEHANDLER_H

#include <wx/wx.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "../model-data/Messdiener.h"
#include "../model-data/Einzeltermin.h"
#include "../model-data/Serientermin.h"
#include "../model-data/MGruppe.h"
#include "../model-data/TGruppe.h"
#include "../model-data/Fehlzeit.h"
#include "../model-plan/PlanerInfo.h"

namespace DataFileHandler {
	extern const wxString RES;
	extern const wxString D;
	extern const wxString SETTINGSFILE;
	extern const wxString DIENSTEFILE;
	extern const wxString MINISFILE;
	extern const wxString EINZELTERMINEFILE;
	extern const wxString SERIENTERMINEFILE;
	extern const wxString MGRUPPENFILE;
	extern const wxString TGRUPPENFILE;
	extern const wxString FEHLZEITENFILE;
	extern const wxString PLANERINFOSFILE;
	extern void prepareFiles();
	extern void implementUpdates();
	extern void saveSettings();
	extern void loadSettings();
	extern void saveDienste(const std::vector<Dienst*>* list);
	extern void loadDienste(std::vector<Dienst*>* list);
	extern void saveMinis(const std::vector<Messdiener*>* list);
	extern void loadMinis(std::vector<Dienst*>* dlist, std::vector<Messdiener*>* list);
	extern void saveEinzeltermine(const std::vector<Einzeltermin*>* list);
	extern void loadEinzeltermine(std::vector<Dienst*>* dlist, std::vector<Einzeltermin*>* list);
	extern void saveSerientermine(const std::vector<Serientermin*>* list);
	extern void loadSerientermine(std::vector<Dienst*>* dlist, std::vector<Serientermin*>* list);
	extern void saveMGruppen(const std::vector<MGruppe*>* list);
	extern void loadMGruppen(std::vector<Messdiener*>* mlist, std::vector<MGruppe*>* list);
	extern void saveTGruppen(const std::vector<TGruppe*>* list);
	extern void loadTGruppen(std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<TGruppe*>* list);
	extern void saveFehlzeiten(const std::vector<Fehlzeit*>* list);
	extern void loadFehlzeiten(std::vector<Messdiener*>* mlist, std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<Fehlzeit*>* list);
	extern void savePlanerInfos(std::vector<PlanerInfo>* list);
	extern void loadPlanerInfos(std::vector<PlanerInfo>* list);
};

#endif	/* DATAFILEHANDLER_H */