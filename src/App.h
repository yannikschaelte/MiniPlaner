/* 
 * File:   App.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:00 PM
 */

#ifndef APP_H
#define	APP_H

#include <wx/wx.h>
#include <wx/snglinst.h>
#include <vector>
#include "view/MainFrame.h"
#include "model-data/Dienst.h"
#include "model-data/Messdiener.h"
#include "model-data/Einzeltermin.h"
#include "model-data/Serientermin.h"
#include "model-data/MGruppe.h"
#include "model-data/TGruppe.h"
#include "model-data/Fehlzeit.h"
#include "model-plan/PTermin.h"
#include "model-plan/PMessdiener.h"
#include "model-plan/PMGruppe.h"
#include "model-plan/PFehlzeit.h"
#include "model-plan/PlanerInfo.h"

/*
 * Zentrale Vewaltung: nimmt Änderungen an den Daten zur Kenntnis und übergibt 
 * sie an View und File System.
 */

class App : public wxApp {
public:
	std::vector<Dienst*> list_dienst;
	std::vector<Messdiener*> list_mini;
	std::vector<Einzeltermin*> list_einzeltermin;
	std::vector<Serientermin*> list_serientermin;
	std::vector<MGruppe*> list_mgruppe;
	std::vector<TGruppe*> list_tgruppe;
	std::vector<Fehlzeit*> list_fehlzeit;
	std::vector<PlanerInfo> list_planer;
	std::vector<wxString> list_ort;
	std::vector<wxString> list_plzort;
	virtual bool OnInit();
	virtual int OnExit();

	bool addDienst(Dienst* dienst);
	void delDienst(int index);
	bool edtDienst(int index, const Dienst* d_to);
	bool addMini(Messdiener* mini);
	void delMini(int index);
	bool edtMini(int index, const Messdiener* m_to);
	bool addEinzeltermin(Einzeltermin* termin);
	void delEinzeltermin(int index);
	bool edtEinzeltermin(int index, const Einzeltermin* t_to);
	bool addSerientermin(Serientermin* termin);
	void delSerientermin(int index);
	bool edtSerientermin(int index, const Serientermin* t_to);
	void addMGruppe(MGruppe* mgruppe);
	void delMGruppe(int index);
	void edtMGruppe(int index, MGruppe* mg_to);
	void addTGruppe(TGruppe* tgruppe);
	void delTGruppe(int index);
	void edtTGruppe(int index, const TGruppe* tg_to);
	bool addFehlzeit(Fehlzeit* fehlzeit);
	void delFehlzeit(int index);
	bool edtFehlzeit(int index, Fehlzeit* f_to);

	void createAndOpenPlanPlaner(wxDateTime datum_beginn, wxDateTime datum_ende, std::vector<Dienst*> list_dienst,
			std::vector<PTermin*> list_termin, std::vector<PMessdiener*> list_mini,
			std::vector<PMGruppe*> list_pmgruppe, std::vector<PFehlzeit*> list_pfehlzeit);
	void delPlanPlaner(int index);
	void edtPlanPlaner(int index);
	
	void initOrte();
	void addOrt(wxString ort);
	void initPLZOrte();
	void addPLZOrt(wxString plzort);

	void importMinis(std::vector<Messdiener*> list_import);
	void importEinzeltermine(std::vector<Einzeltermin*> list_import);
	void onLanguageChange();
private:
	wxSingleInstanceChecker* single_instance_checker;
	MainFrame* frame;
	void sortDienste();
	void sortMinis();
	void sortEinzeltermine();
	void sortSerientermine();
	void sortMGruppen();
	void sortFehlzeiten();
	void sortPlaene();
	void updateIntNumDienste();
	void updateIntNumMinis();
	void updateIntNumEinzeltermine();
	void updateIntNumSerientermine();
};

#endif	/* APP_H */