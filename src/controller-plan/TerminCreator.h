/* 
 * File:   TerminCreator.h
 * Author: Yannik
 *
 * Created on August 28, 2015, 1:26 PM
 */

#ifndef TERMINCREATOR_H
#define	TERMINCREATOR_H

#include <vector>
#include "../model-data/Dienst.h"
#include "../model-data/Einzeltermin.h"
#include "../model-data/Serientermin.h"
#include "../model-data/Messdiener.h"
#include "../model-data/TGruppe.h"
#include "../model-data/MGruppe.h"
#include "../model-data/Fehlzeit.h"
#include "../model-plan/PTermin.h"
#include "../model-plan/PMGruppe.h"
#include "../model-plan/PFehlzeit.h"

/**
 * Call createLists to fill dlist, mlist, mglist, pthlist.
 * Do some changes (also to services) and call fillMLists.
 * Finally call createTerminList.
 */
namespace TerminCreator {

	class PTerminHolder {
	public:
		PTermin* termin;
		Einzeltermin* e;
		Serientermin* s;
		PTerminHolder(PTermin* _termin, Einzeltermin* _e);
		PTerminHolder(PTermin* _termin, Serientermin* _s);
		static bool cmp(const PTerminHolder& p1, const PTerminHolder& p2);
	private:
	};

	void createLists(wxDateTime datum_beginn, wxDateTime datum_ende,
			std::vector<Dienst*>* dlist,
			std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<TGruppe*>* tglist,
			std::vector<Messdiener*>* mlist, std::vector<MGruppe*>* mglist, std::vector<Fehlzeit*>* flist,
			std::vector<Dienst*>* pdlist, std::vector<PTerminHolder>* pthlist, std::vector<PMessdiener*>* pmlist, std::vector<PMGruppe*>* pmglist, std::vector<PFehlzeit*>* pflist);
	void createDienste(std::vector<Dienst*>* dlist, std::vector<Dienst*>* pdlist);
	void createOrderedPTerminOriginList(wxDateTime datum_beginn, wxDateTime datum_ende,
			std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist,
			std::vector<PTerminHolder>* pthlist);
	void addTGruppen(std::vector<TGruppe*>* tglist, std::vector<PTerminHolder>* pthlist);
	void createPMessdienerOriginList(std::vector<Messdiener*>* mlist, std::vector<std::pair<PMessdiener*, Messdiener*> >* pmhlist);
	void addMGruppen(std::vector<MGruppe*>* mglist, std::vector<std::pair<PMessdiener*, Messdiener*> >* pmhlist, std::vector<PMGruppe*>* pmglist);
	void fillMLists(std::vector<PTerminHolder>* pthlist, std::vector<PMessdiener*>* pmlist, std::vector<Fehlzeit*>* flist, std::vector<Dienst*>* pdlist);
	void createTerminList(std::vector<PTerminHolder>* pthlist, std::vector<PTermin*>* ptlist);
	void createFehlzeitList(wxDateTime datum_beginn, wxDateTime datum_ende, std::vector<PMessdiener*>* pmlist, std::vector<Fehlzeit*>* flist, std::vector<PFehlzeit*>* pflist);
};

#endif	/* TERMINCREATOR_H */