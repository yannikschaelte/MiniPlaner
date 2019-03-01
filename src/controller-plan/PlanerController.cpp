/* 
 * File:   PlanerController.cpp
 * Author: Yannik
 * 
 * Created on September 11, 2015, 2:52 PM
 */

#include "PlanerController.h"
#include <cstdlib>
#include <algorithm>
#include "../view-plan/PlanPlanerDialog.h"
#include "../file/PlanFileHandler.h"
#include "../Util.h"
#include "../view-plan/PTerminDialog.h"

PlanerController::PlanerController(Planer* _planer, PlanPlanerDialog* _view) {
	planer = _planer;
	view = _view;
}

PlanerController::~PlanerController() {
	delete planer;
}

//0: can create
//1: impossible
//2: full

int PlanerController::simpleCheckCanCreatePlan() {
	initTmpLists();
	prepareMGruppenHard();
	//check 1: overall needed minis
	int num_termine = tmp_list_termin.size();
	int num_minis = tmp_list_mini.size();
	for (int i = 0; i < num_termine; i++) {
		CTermin* termin = tmp_list_termin.at(i);
		if (termin->prev != NULL) continue;
		int num = 0;
		do {
			for (std::vector<std::pair<Dienst*, int> >::iterator iter_d = termin->list_dienst_req.begin();
					iter_d != termin->list_dienst_req.end(); iter_d++) {
				num += iter_d->second;
			}
			termin = termin->next;
		} while (termin != NULL);
		if (num > num_minis) {
			deleteTmpLists();
			return 1;
		}
	}
	//check 2: needed minis in single lists
	PositionInfo info = findMinimumTerminDienst();
	if (info.diff < 0) {
		deleteTmpLists();
		return 1;
	}
	if (info.termin == NULL) {
		deleteTmpLists();
		return 2;
	}
	return 0;
}

//compute plan -----------------------------------------------------------------

void PlanerController::computePlan(bool* continueComputation) {
	if (planer->settings.modus_algorithmus == Planer::Settings::MODUS_ALGORITHMUS_MINIMUM)
		computePlanMinimumSearch(continueComputation);
	else
		computePlanChronologically(continueComputation);
}

//approach number 1

void PlanerController::computePlanMinimumSearch(bool* continueComputation) {
	bool foundSolution = false;
	while (!foundSolution && *continueComputation) {
		if (planer->settings.modus_fehlzeiten == Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN) prepareMiniNumsFehlzeiten();
		PositionInfo info = findMinimumTerminDienst();
		bool couldFill = true;
		while (info.termin != NULL && info.diff >= 0 && couldFill && *continueComputation) {
			couldFill = fillDienst(info.termin, info.dienst);
			if (couldFill) {
				info = findMinimumTerminDienst();
			}
		}
		if (info.termin == NULL) {//alle Positionen besetzt (couldFill = false => info.termin != NULL))
			foundSolution = true;
		} else {//some diff < 0
			initTmpLists();
			prepareMGruppenHard();
		}
	}
	if (*continueComputation) {
		if (planer->settings.modus_fehlzeiten == Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN) putCorrectMiniNums();
		history_list.push_back(copyMinisToList());
		future_list.clear();
		fillRealLists();
		edt = true;
	}
	deleteTmpLists();
}

//approach number 2

void PlanerController::computePlanChronologically(bool* continueComputation) {
	bool foundSolution = false;
	while (!foundSolution && *continueComputation) {
		bool couldFill = true;
		for (std::vector<CTermin*>::iterator iter_t = tmp_list_termin.begin(); iter_t != tmp_list_termin.end() && couldFill; iter_t++) {
			if (planer->settings.modus_fehlzeiten == Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN) prepareMiniNumsFehlzeitenAfter((**iter_t).datum);
			int num_dienste = (**iter_t).list_dienst_req.size();
			for (int i = 0; i < num_dienste && couldFill; i++) {
				couldFill = fillDienst(*iter_t, i);
			}
		}
		if (!couldFill) {
			initTmpLists();
			prepareMGruppenHard();
		} else {
			foundSolution = true;
		}
	}
	if (*continueComputation) {
		if (planer->settings.modus_fehlzeiten == Planer::Settings::MODUS_FEHLZEITEN_ANRECHNEN) putCorrectMiniNums();
		history_list.push_back(copyMinisToList());
		future_list.clear();
		fillRealLists();
		edt = true;
	}
	deleteTmpLists();
}

// for termin-minimum search ---------------------------------------------------

PlanerController::PositionInfo PlanerController::findMinimumTerminDienst() {
	PositionInfo info(NULL, 0, 0);
	for (std::vector<CTermin*>::iterator iter_t = tmp_list_termin.begin(); iter_t != tmp_list_termin.end(); iter_t++) {
		int num_dienste = (**iter_t).list_dienst_req.size();
		for (int i = 0; i < num_dienste; i++) {
			int req = (**iter_t).list_dienst_req.at(i).second;
			if (req > 0) {
				int diff = (**iter_t).list_dienst_minis_available.at(i).second.size() - req;
				if (info.termin == NULL || diff < info.diff) {
					info = PositionInfo(*iter_t, i, diff);
				}
			}
		}
	}
	return info;
}

// for fehlzeiten --------------------------------------------------------------

void PlanerController::prepareMiniNumsFehlzeiten() {
	for (std::vector<PFehlzeit*>::iterator iter_f = tmp_list_fehlzeit.begin(); iter_f != tmp_list_fehlzeit.end(); iter_f++) {
		addProbableMiniNum(*iter_f);
	}
}

void PlanerController::prepareMiniNumsFehlzeitenAfter(wxDateTime termin_datum) {
	for (std::vector<PFehlzeit*>::iterator iter_f = tmp_list_fehlzeit.begin(); iter_f != tmp_list_fehlzeit.end();) {
		if (!(**iter_f).datum_beginn.IsLaterThan(termin_datum)) {
			addProbableMiniNum(*iter_f);
			delete *iter_f;
			iter_f = tmp_list_fehlzeit.erase(iter_f);
		} else {
			iter_f++;
		}
	}
}

void PlanerController::addProbableMiniNum(PFehlzeit* fehlzeit) {
	PMessdiener* mini = fehlzeit->mini;
	float probEinsaetze = 0;
	//iterate termine and add to probEinsaetze whenever iter_f-->mini could be inserted according to its dienste
	std::vector<CTermin*>::iterator iter_t = tmp_list_termin.begin();
	while (iter_t != tmp_list_termin.end() && (**iter_t).datum.IsEarlierThan(fehlzeit->datum_beginn)) iter_t++;
	while (iter_t != tmp_list_termin.end() && !(**iter_t).datum.IsLaterThan(fehlzeit->datum_ende)) {
		int num_dienste = (**iter_t).list_dienst_req.size();
		for (int i = 0; i < num_dienste; i++) {
			if (std::find(mini->dienste.begin(), mini->dienste.end(), (**iter_t).list_dienst_req.at(i).first) != mini->dienste.end()) {//mini could possibly have been useful here
				probEinsaetze += ((float) (**iter_t).list_dienst_req.at(i).second) / ((float) ((**iter_t).list_dienst_minis_available.at(i).second.size() + 1));
			}
		}
		iter_t++;
	}
	mini->num += (int) probEinsaetze;
}

// fill a specific service -----------------------------------------------------

bool PlanerController::fillDienst(CTermin* termin, int dienst) {
	while (termin->list_dienst_req.at(dienst).second > 0) {
		//check if possible to continue
		if (termin->list_dienst_minis_available.at(dienst).second.size() == 0) {
			return false;
		}

		//get minimum list
		std::unordered_set<PMessdiener*> list_minimum;
		findMinimumMiniNum(&termin->list_dienst_minis_available.at(dienst).second, &list_minimum);
		//mind surroundings
		eraseSurroundings(termin, termin->list_dienst_minis.at(dienst).first, &list_minimum);

		//select a mini
		int index = std::rand() % list_minimum.size();
		PMessdiener* m;
		int i = 0;
		std::unordered_set<PMessdiener*>::iterator iter_m = list_minimum.begin();
		for (; i < index; i++) {
			iter_m++;
		}
		m = *iter_m;
		if (m->gruppe != NULL && m->gruppe->modus == MGruppe::NUR_GEM) {
			//might need to be inserted somewhere else
			insertMGruppeHard(termin, m->gruppe->list, true);
			//nums incremented, reqs decremented, missing:
			for (std::vector<PMessdiener*>::iterator iter_m = m->gruppe->list.begin(); iter_m != m->gruppe->list.end(); iter_m++) {
				handleTGruppen(termin, *iter_m);
			}
			//mgruppen.hard: no further checks needed
		} else {
			termin->list_dienst_minis.at(dienst).second.insert(m);
			termin->list_dienst_req.at(dienst).second--;
			m->num++;

			//erase m from lists
			handleTGruppen(termin, m);

			//insert mgruppe somewhere
			handleMGruppen(termin, dienst, m);
			//check whether some groups have become impossible to insert
			handleMGruppenHard(termin);
		}
	}
	return true;
}

void PlanerController::findMinimumMiniNum(std::unordered_set<PMessdiener*>* list_avai, std::unordered_set<PMessdiener*>* list_minimum) {
	int minimum = -1;
	for (std::unordered_set<PMessdiener*>::iterator iter = list_avai->begin(); iter != list_avai->end(); iter++) {
		if ((**iter).num < minimum || minimum == -1) {
			list_minimum->clear();
			list_minimum->insert(*iter);
			minimum = (**iter).num;
		} else if ((**iter).num == minimum) {
			list_minimum->insert(*iter);
		}
	}
}

void PlanerController::eraseSurroundings(CTermin* termin, Dienst* dienst, std::unordered_set<PMessdiener*>* list_minimum) {
	int random = rand() % 61;
	const int steps = 4;
	const int num_termine = tmp_list_termin.size();
	std::unordered_set<PMessdiener*> list_dienst[steps];
	std::unordered_set<PMessdiener*> list_gesamt[steps];
	for (int i = 0; i < steps; i++) {
		if (random < 61 - (i + 1)) {
			if (termin->_id > i)
				addAllMinis(tmp_list_termin.at(termin->_id - (i + 1)), &list_gesamt[i], dienst, &list_dienst[i]);
			if (termin->_id < num_termine - (i + 1))
				addAllMinis(tmp_list_termin.at(termin->_id + (i + 1)), &list_gesamt[i], dienst, &list_dienst[i]);
		}
		if (i < steps - 1) {
			list_gesamt[i + 1] = list_gesamt[i];
			list_dienst[i + 1] = list_dienst[i];
		}
	}

	std::unordered_set<PMessdiener*> list_minimum_tmp;
	for (int i = steps - 1; i >= 0; i--) {
		list_minimum_tmp = *list_minimum;
		for (std::unordered_set<PMessdiener*>::iterator iter_m = list_gesamt[i].begin(); iter_m != list_gesamt[i].end(); iter_m++) {
			list_minimum_tmp.erase(*iter_m);
		}
		if (list_minimum_tmp.size() > 0) *list_minimum = list_minimum_tmp;
		return;
	}
	for (int i = steps - 1; i >= 0; i--) {
		list_minimum_tmp = *list_minimum;
		for (std::unordered_set<PMessdiener*>::iterator iter_m = list_dienst[i].begin(); iter_m != list_dienst[i].end(); iter_m++) {
			list_minimum_tmp.erase(*iter_m);
		}
		if (list_minimum_tmp.size() > 0) *list_minimum = list_minimum_tmp;
		return;
	}
}

/**
 * Used by eraseSurroundings().
 * @param termin
 * @param list_gesamt
 * @param dienst
 * @param list_dienst
 */
void PlanerController::addAllMinis(CTermin* termin, std::unordered_set<PMessdiener*>* list_gesamt, Dienst* dienst, std::unordered_set<PMessdiener*>* list_dienst) {
	int num_dienste = termin->list_dienst_req.size();
	for (int j = 0; j < num_dienste; j++) {
		for (std::unordered_set<PMessdiener*>::iterator iter_m = termin->list_dienst_minis.at(j).second.begin(); iter_m != termin->list_dienst_minis.at(j).second.end(); iter_m++) {
			list_gesamt->insert(*iter_m);
			if (termin->list_dienst_minis.at(j).first == dienst) {
				list_dienst->insert(*iter_m);
			}
		}
	}
}

//handle mgruppen --------------------------------------------------------------

void PlanerController::prepareMGruppenHard() {
	for (std::vector<PMGruppe*>::iterator iter_mg = tmp_list_mgruppe.begin(); iter_mg != tmp_list_mgruppe.end(); iter_mg++) {
		if ((**iter_mg).modus == MGruppe::NUR_GEM) {
			for (std::vector<CTermin*>::iterator iter_t = tmp_list_termin.begin(); iter_t != tmp_list_termin.end(); iter_t++) {
				if (!insertMGruppeHard(*iter_t, (**iter_mg).list, false)) {
					//not possible to insert mg in here
					for (std::vector<PMessdiener*>::iterator iter_m = (**iter_mg).list.begin(); iter_m != (**iter_mg).list.end(); iter_m++) {
						eraseFromAvailableList(*iter_t, *iter_m);
					}
				}
			}
		}
	}
}

void PlanerController::handleMGruppen(CTermin* termin, int dienst, PMessdiener * mini) {
	if (mini->gruppe != NULL) {
		std::vector<PMessdiener*> mgruppe = mini->gruppe->list;
		for (std::vector<PMessdiener*>::iterator iter_m = mgruppe.begin(); iter_m != mgruppe.end(); iter_m++) {
			if (*iter_m != mini) {
				//try to insert into same service-list
				if (termin->list_dienst_req.at(dienst).second > 0
						&& termin->list_dienst_minis_available.at(dienst).second.find(*iter_m) != termin->list_dienst_minis_available.at(dienst).second.end()) {
					termin->list_dienst_minis.at(dienst).second.insert(*iter_m);
					termin->list_dienst_req.at(dienst).second--;
					(**iter_m).num++;
					handleTGruppen(termin, *iter_m);
				} else {//try to insert somewhere else
					int num_dienste = termin->list_dienst_req.size();
					for (int j = 0; j < num_dienste; j++) {
						if (j != dienst && termin->list_dienst_req.at(j).second > 0
								&& termin->list_dienst_minis_available.at(j).second.find(*iter_m) != termin->list_dienst_minis_available.at(j).second.end()) {
							termin->list_dienst_minis.at(j).second.insert(*iter_m);
							termin->list_dienst_req.at(j).second--;
							(**iter_m).num++;
							handleTGruppen(termin, *iter_m);
							break;
						}
					}
				}
			}
		}
	}
}

void PlanerController::handleMGruppenHard(CTermin* termin) {
	for (std::vector<PMGruppe*>::iterator iter_mg = tmp_list_mgruppe.begin(); iter_mg != tmp_list_mgruppe.end(); iter_mg++) {
		if ((**iter_mg).modus == MGruppe::NUR_GEM) {
			if (!insertMGruppeHard(termin, (**iter_mg).list, false)) {
				//not possible to insert mg in here
				for (std::vector<PMessdiener*>::iterator iter_m = (**iter_mg).list.begin(); iter_m != (**iter_mg).list.end(); iter_m++) {
					eraseFromAvailableList(termin, *iter_m);
				}
			}
			CTermin* t = termin;
			while (t->next != NULL) {
				t = t->next;
				if (!insertMGruppeHard(t, (**iter_mg).list, false)) {
					//not possible to insert mg in here
					for (std::vector<PMessdiener*>::iterator iter_m = (**iter_mg).list.begin(); iter_m != (**iter_mg).list.end(); iter_m++) {
						eraseFromAvailableList(t, *iter_m);
					}
				}
			}
			t = termin;
			while (t->prev != NULL) {
				t = t->prev;
				if (!insertMGruppeHard(t, (**iter_mg).list, false)) {
					//not possible to insert mg in here
					for (std::vector<PMessdiener*>::iterator iter_m = (**iter_mg).list.begin(); iter_m != (**iter_mg).list.end(); iter_m++) {
						eraseFromAvailableList(t, *iter_m);
					}
				}
			}
		}
	}
}

/**
 * To be called with keep = true only when succeeded with keep = false.
 * @param termin
 * @param list
 * @param keep: keep result in system or remove when finished
 */
bool PlanerController::insertMGruppeHard(CTermin* termin, std::vector<PMessdiener*> list, bool keep) {
	if (list.empty()) return true;
	PMessdiener* m = list.front();
	list.erase(list.begin());
	//check if already contained
	bool inside = false;
	for (std::vector<std::pair<Dienst*, std::unordered_set<PMessdiener*> > >::iterator iter_d = termin->list_dienst_minis.begin();
			iter_d != termin->list_dienst_minis.end(); iter_d++) {
		if (iter_d->second.find(m) != iter_d->second.end()) {
			inside = true;
			break;
		}
	}
	if (inside) return true;
	int num_dienste = termin->list_dienst_req.size();
	for (int i = 0; i < num_dienste; i++) {
		if (termin->list_dienst_minis_available.at(i).second.find(m) == termin->list_dienst_minis_available.at(i).second.end()) continue;
		if (termin->list_dienst_req.at(i).second == 0) continue;
		termin->list_dienst_minis_available.at(i).second.erase(m);
		termin->list_dienst_minis.at(i).second.insert(m);
		termin->list_dienst_req.at(i).second--;
		if (insertMGruppeHard(termin, list, keep)) {
			if (keep) {
				m->num++;
			} else {
				termin->list_dienst_minis_available.at(i).second.insert(m);
				termin->list_dienst_minis.at(i).second.erase(m);
				termin->list_dienst_req.at(i).second++;
			}
			return true;
		}
		termin->list_dienst_minis_available.at(i).second.insert(m);
		termin->list_dienst_minis.at(i).second.erase(m);
		termin->list_dienst_req.at(i).second++;

	}
	return false;
}

//handle tgruppen --------------------------------------------------------------

/**
 * erase (inserted) mini from all lists in tgruppe(termin).
 * @param termin
 * @param mini
 */
void PlanerController::handleTGruppen(CTermin* termin, PMessdiener * mini) {
	eraseFromAvailableList(termin, mini);
	CTermin* t = termin;
	while (t->next != NULL) {
		t = t->next;
		eraseFromAvailableList(t, mini);
	}
	t = termin;
	while (t->prev != NULL) {
		t = t->prev;
		eraseFromAvailableList(t, mini);
	}
}

void PlanerController::handleTGruppenP(PTermin* termin, PMessdiener * mini) {
	eraseFromAvailableListP(termin, mini);
	PTermin* t = termin;
	while (t->next != NULL) {
		t = t->next;
		eraseFromAvailableListP(t, mini);
	}
	t = termin;
	while (t->prev != NULL) {
		t = t->prev;
		eraseFromAvailableListP(t, mini);
	}
}

void PlanerController::handleTGruppenWithdrawP(PTermin* termin, PMessdiener * mini) {
	addToAvailableListIfPossibleP(termin, mini);
	PTermin* t = termin;
	while (t->next != NULL) {
		t = t->next;
		addToAvailableListIfPossibleP(t, mini);
	}
	t = termin;
	while (t->prev != NULL) {
		t = t->prev;
		addToAvailableListIfPossibleP(t, mini);
	}
}

void PlanerController::eraseFromAvailableList(CTermin* t, PMessdiener * m) {
	for (std::vector<std::pair<Dienst*, std::unordered_set<PMessdiener*> > >::iterator iter_d = t->list_dienst_minis_available.begin(); iter_d != t->list_dienst_minis_available.end(); iter_d++) {
		iter_d->second.erase(m);
	}
}

void PlanerController::addToAvailableListIfPossibleP(PTermin* t, PMessdiener * m) {
	int num_dienste = t->list_dienst_num.size();
	for (int j = 0; j < num_dienste; j++) {
		if (std::find(t->list_dienst_minis_possible.at(j).second.begin(), t->list_dienst_minis_possible.at(j).second.end(), m)
				!= t->list_dienst_minis_possible.at(j).second.end()) {
			if (std::find(t->list_dienst_minis_available.at(j).second.begin(), t->list_dienst_minis_available.at(j).second.end(), m)
					== t->list_dienst_minis_available.at(j).second.end()) {
				t->list_dienst_minis_available.at(j).second.push_back(m);
				std::sort(t->list_dienst_minis_available.at(j).second.begin(), t->list_dienst_minis_available.at(j).second.end(), PMessdiener::cmp);
			}
		}
	}
}

void PlanerController::eraseFromAvailableListP(PTermin* t, PMessdiener * m) {
	for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_d = t->list_dienst_minis_available.begin(); iter_d != t->list_dienst_minis_available.end(); iter_d++) {
		Util::erase_from_minivec(&iter_d->second, m);
	}
}

//connection to real lists -----------------------------------------------------

void PlanerController::initTmpLists() {
	int num_termine = planer->list_termin.size();
	if (tmp_list_termin.size() == 0 && tmp_list_mgruppe.size() == 0 && tmp_list_mini.size() == 0 && tmp_list_fehlzeit.size() == 0) {//first initialization
		for (std::vector<PMessdiener*>::iterator iter_m = planer->list_mini.begin(); iter_m != planer->list_mini.end(); iter_m++) {
			tmp_list_mini.push_back(new PMessdiener(**iter_m));
		}
		for (std::vector<PMGruppe*>::iterator iter_mg = planer->list_mgruppe.begin(); iter_mg != planer->list_mgruppe.end(); iter_mg++) {
			tmp_list_mgruppe.push_back(new PMGruppe(**iter_mg));
		}
		for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
			tmp_list_termin.push_back(new CTermin());
		}
		//adapt links
		for (std::vector<PMessdiener*>::iterator iter_m = tmp_list_mini.begin(); iter_m != tmp_list_mini.end(); iter_m++) {
			if ((**iter_m).gruppe != NULL) {
				(**iter_m).gruppe = tmp_list_mgruppe.at((**iter_m).gruppe->_id);
			}
		}
		for (std::vector<PMGruppe*>::iterator iter_mg = tmp_list_mgruppe.begin(); iter_mg != tmp_list_mgruppe.end(); iter_mg++) {
			int num_minis = (**iter_mg).list.size();
			for (int i = 0; i < num_minis; i++) {
				(**iter_mg).list.at(i) = tmp_list_mini.at((**iter_mg).list.at(i)->_id);
			}
		}
		for (int i = 0; i < num_termine; i++) {
			PTermin* pt = planer->list_termin.at(i);
			CTermin* ct = tmp_list_termin.at(i);
			ct->_id = pt->_id;
			ct->datum = pt->datum;
			if (pt->prev != NULL) {
				ct->prev = tmp_list_termin.at(pt->prev->_id);
			}
			if (pt->next != NULL) {
				ct->next = tmp_list_termin.at(pt->next->_id);
			}
		}
	} else {
		for (std::vector<PMessdiener*>::iterator iter_m = tmp_list_mini.begin(); iter_m != tmp_list_mini.end(); iter_m++) {
			(**iter_m).num = planer->list_mini.at((**iter_m)._id)->num;
		}
		for (int i = 0; i < num_termine; i++) {
			tmp_list_termin.at(i)->list_dienst_minis.clear();
			tmp_list_termin.at(i)->list_dienst_minis_available.clear();
			tmp_list_termin.at(i)->list_dienst_req.clear();
		}
		for (std::vector<PFehlzeit*>::iterator iter_f = tmp_list_fehlzeit.begin(); iter_f != tmp_list_fehlzeit.end(); iter_f++) {
			delete *iter_f;
		}
		tmp_list_fehlzeit.clear();
	}
	//Fehlzeiten
	for (std::vector<PFehlzeit*>::iterator iter_f = planer->list_fehlzeit.begin(); iter_f != planer->list_fehlzeit.end(); iter_f++) {
		tmp_list_fehlzeit.push_back(new PFehlzeit(**iter_f));
	}
	for (std::vector<PFehlzeit*>::iterator iter_f = tmp_list_fehlzeit.begin(); iter_f != tmp_list_fehlzeit.end(); iter_f++) {
		(**iter_f).mini = tmp_list_mini.at((**iter_f).mini->_id);
	}
	//Termin-Listen
	for (int i = 0; i < num_termine; i++) {
		PTermin* pt = planer->list_termin.at(i);
		CTermin* ct = tmp_list_termin.at(i);
		int num_dienste = pt->list_dienst_num.size();
		for (int j = 0; j < num_dienste; j++) {
			Dienst* d = pt->list_dienst_num.at(j).first;
			//available list
			std::unordered_set<PMessdiener*> mini_avai;
			for (std::vector<PMessdiener*>::iterator iter_m = pt->list_dienst_minis_available.at(j).second.begin();
					iter_m != pt->list_dienst_minis_available.at(j).second.end(); iter_m++) {
				mini_avai.insert(tmp_list_mini.at((**iter_m)._id));
			}
			ct->list_dienst_minis_available.push_back(std::make_pair(d, mini_avai));
			//minis list and req
			std::unordered_set<PMessdiener*> minis;
			int req = pt->list_dienst_num.at(j).second;
			for (std::vector<PMessdiener*>::iterator iter_m = pt->list_dienst_minis.at(j).second.begin();
					iter_m != pt->list_dienst_minis.at(j).second.end(); iter_m++) {
				if (*iter_m != NULL) {
					minis.insert(tmp_list_mini.at((**iter_m)._id));
					req--;
				}
			}
			ct->list_dienst_minis.push_back(std::make_pair(d, minis));
			ct->list_dienst_req.push_back(std::make_pair(d, req));
		}
	}
}

void PlanerController::deleteTmpLists() {
	for (std::vector<CTermin*>::iterator iter = tmp_list_termin.begin(); iter != tmp_list_termin.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PMGruppe*>::iterator iter = tmp_list_mgruppe.begin(); iter != tmp_list_mgruppe.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PMessdiener*>::iterator iter = tmp_list_mini.begin(); iter != tmp_list_mini.end(); iter++) {
		delete *iter;
	}
	for (std::vector<PFehlzeit*>::iterator iter = tmp_list_fehlzeit.begin(); iter != tmp_list_fehlzeit.end(); iter++) {
		delete *iter;
	}
	tmp_list_termin.clear();
	tmp_list_mgruppe.clear();
	tmp_list_mini.clear();
	tmp_list_fehlzeit.clear();
}

void PlanerController::fillRealLists() {
	int num_minis = tmp_list_mini.size();
	for (int i = 0; i < num_minis; i++) {
		planer->list_mini.at(i)->num = tmp_list_mini.at(i)->num;
	}
	int num_termine = tmp_list_termin.size();
	for (int i = 0; i < num_termine; i++) {
		PTermin* pt = planer->list_termin.at(i);
		CTermin* ct = tmp_list_termin.at(i);
		int num_dienste = pt->list_dienst_num.size();
		for (int j = 0; j < num_dienste; j++) {
			//minis list
			for (std::unordered_set<PMessdiener*>::iterator iter_m = ct->list_dienst_minis.at(j).second.begin();
					iter_m != ct->list_dienst_minis.at(j).second.end(); iter_m++) {
				if (std::find(pt->list_dienst_minis.at(j).second.begin(), pt->list_dienst_minis.at(j).second.end(), planer->list_mini.at((**iter_m)._id))
						== pt->list_dienst_minis.at(j).second.end()) {
					for (std::vector<PMessdiener*>::iterator iter_m_vec = pt->list_dienst_minis.at(j).second.begin();
							iter_m_vec != pt->list_dienst_minis.at(j).second.end(); iter_m_vec++) {
						if (*iter_m_vec == NULL) {
							iter_m_vec = pt->list_dienst_minis.at(j).second.erase(iter_m_vec);
							pt->list_dienst_minis.at(j).second.insert(iter_m_vec, planer->list_mini.at((**iter_m)._id));
							break;
						}
					}
				}
			}
		}
	}
	//available lists: for each termin->dienst: avai = poss; for each mini in tgruppe->dienste->minis: erase mini from avai
	for (std::vector<PTermin*>::iterator iter = planer->list_termin.begin(); iter != planer->list_termin.end(); iter++) {
		if ((**iter).prev == (PTermin *) NULL) {
			recalculateAvailableListsInTGruppe(*iter);
		}
	}
	//Fehlzeiten: nothing to be done
}

void PlanerController::putCorrectMiniNums() {
	for (std::vector<PMessdiener*>::iterator iter_m = tmp_list_mini.begin(); iter_m != tmp_list_mini.end(); iter_m++) {
		(**iter_m).num = 0;
	}
	for (std::vector<CTermin*>::iterator iter_t = tmp_list_termin.begin(); iter_t != tmp_list_termin.end(); iter_t++) {
		for (std::vector<std::pair<Dienst*, std::unordered_set<PMessdiener*> > >::iterator iter_d = (**iter_t).list_dienst_minis.begin();
				iter_d != (**iter_t).list_dienst_minis.end(); iter_d++) {
			for (std::unordered_set<PMessdiener*>::iterator iter_m = iter_d->second.begin(); iter_m != iter_d->second.end(); iter_m++) {
				(**iter_m).num++;
			}
		}
	}
}

// stuff -----------------------------------------------------------------------

void PlanerController::onClear() {
	bool someNotEmpty = false;
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end() && !someNotEmpty; iter_t++) {
		int num_dienste = (**iter_t).list_dienst_num.size();
		for (int j = 0; j < num_dienste && !someNotEmpty; j++) {
			int num_minis = (**iter_t).list_dienst_minis.at(j).second.size();
			for (int k = 0; k < num_minis; k++) {
				if ((**iter_t).list_dienst_minis.at(j).second.at(k) != NULL) {
					someNotEmpty = true;
				}
			}
		}
	}
	if (someNotEmpty) {
		handleDataChange();
		for (std::vector<PMessdiener*>::iterator iter_m = planer->list_mini.begin(); iter_m != planer->list_mini.end(); iter_m++) {
			(**iter_m).num = 0;
		}
		for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
			//available list
			(**iter_t).list_dienst_minis_available = (**iter_t).list_dienst_minis_possible;
			//minis list
			int num_dienste = (**iter_t).list_dienst_num.size();
			for (int j = 0; j < num_dienste; j++) {
				int num_minis = (**iter_t).list_dienst_num.at(j).second;
				for (int k = 0; k < num_minis; k++) {
					(**iter_t).list_dienst_minis.at(j).second.at(k) = NULL;
				}
			}
		}
		edt = true;
		view->notifySave(true);
		view->notifyMinis();
		view->unHighlight();
		view->notifyMaskeAndPreview();
	}
}

void PlanerController::onEntryChanged(PTermin* termin, int dienst, int mini_old_i, PMessdiener* mini_new) {
	PMessdiener* mini_old = termin->list_dienst_minis.at(dienst).second.at(mini_old_i);
	if (mini_old != mini_new) {
		handleDataChange();
		termin->list_dienst_minis.at(dienst).second.at(mini_old_i) = mini_new;
		if (mini_new != NULL) {
			mini_new->num++;
			handleTGruppenP(termin, mini_new);
		}
		if (mini_old != NULL) {
			mini_old->num--;
			handleTGruppenWithdrawP(termin, mini_old);
		}
		view->notifyMinis();
		view->notifyMaskeAndPreview();
		view->highlightPMiniChoiceDialog(termin, dienst, mini_old_i);
		edt = true;
		view->notifySave(true);
	}
}

void PlanerController::onSave() {
	PlanFileHandler::savePlaner(planer);
	edt = false;
	view->notifySave(false);
}

void PlanerController::onUndo() {
	if (!history_list.empty()) {
		future_list.push_back(copyMinisToList());
		copyMinisFromList(&history_list.back());
		history_list.erase(history_list.begin() + history_list.size() - 1);
		view->notifyMinis();
		view->notifyMaskeAndPreview();
		edt = true;
		view->notifySave(true);
		view->notifyHistory(!history_list.empty());
		view->notifyFuture(true);
		view->unHighlight();
	}
}

void PlanerController::onRedo() {
	if (!future_list.empty()) {
		history_list.push_back(copyMinisToList());
		copyMinisFromList(&future_list.back());
		future_list.erase(future_list.begin() + future_list.size() - 1);
		view->notifyMinis();
		view->notifyMaskeAndPreview();
		edt = true;
		view->notifySave(true);
		view->notifyHistory(true);
		view->notifyFuture(!future_list.empty());
		view->unHighlight();
	}
}

void PlanerController::handleDataChange() {
	history_list.push_back(copyMinisToList());
	future_list.clear();
	view->notifyHistory(true);
	view->notifyFuture(false);
}

std::vector<std::vector<PMessdiener*> > PlanerController::copyMinisToList() {
	std::vector<std::vector<PMessdiener*> >list;
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
		int num_dienste = (**iter_t).list_dienst_num.size();
		for (int j = 0; j < num_dienste; j++) {
			list.push_back((**iter_t).list_dienst_minis.at(j).second);
			list.push_back((**iter_t).list_dienst_minis_available.at(j).second);
		}
	}
	return list;
}

void PlanerController::copyMinisFromList(std::vector<std::vector<PMessdiener*> >* list) {
	int counter = 0;
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
		int num_dienste = (**iter_t).list_dienst_num.size();
		for (int j = 0; j < num_dienste; j++) {
			(**iter_t).list_dienst_minis.at(j).second = list->at(counter++);
			(**iter_t).list_dienst_minis_available.at(j).second = list->at(counter++);
		}
	}
	Util::setMiniNums(&planer->list_mini, &planer->list_termin);
}

void PlanerController::recalculateAvailableListsInTGruppe(PTermin* termin) {
	std::vector<PTermin*> tgruppe;
	tgruppe.push_back(termin);
	PTermin* t = termin;
	while (t->next != NULL) {
		t = t->next;
		tgruppe.push_back(t);
	}
	t = termin;
	while (t->prev != NULL) {
		t = t->prev;
		tgruppe.push_back(t);
	}
	int num_tgruppe = tgruppe.size();
	for (int i = 0; i < num_tgruppe; i++) {
		PTermin* t = tgruppe.at(i);
		int num_dienste = t->list_dienst_num.size();
		t->list_dienst_minis_available = t->list_dienst_minis_possible;
		for (int j = 0; j < num_dienste; j++) {
			//erase all that are used somewhere
			for (int i2 = 0; i2 < num_tgruppe; i2++) {
				PTermin* t2 = tgruppe.at(i2);
				int num_dienste2 = t2->list_dienst_num.size();
				for (int j2 = 0; j2 < num_dienste2; j2++) {
					for (std::vector<PMessdiener*>::iterator iter_m = t2->list_dienst_minis.at(j2).second.begin(); 
							iter_m != t2->list_dienst_minis.at(j2).second.end(); 
							iter_m++) {
						if (*iter_m != NULL) Util::erase_from_minivec(&t->list_dienst_minis_available.at(j).second, *iter_m);
					}
				}
			}
		}
	}
}

void PlanerController::onEdtTermin(int index) {
	PTermin* termin = planer->list_termin.at(index);
	bool edt_termin = false;
	PTerminDialog* dialog = new PTerminDialog(view, termin, &planer->list_termin, &planer->list_dienst, &planer->list_mini, &edt_termin);
	dialog->ShowModal();
	delete dialog;
	if (edt_termin) {
		int j = 0;
		while (planer->list_termin.at(j) != termin) j++;
		view->notifyTermine(j);
		view->notifyTGruppen();
		view->notifyMinis();
		view->redrawMaske();
		view->notifyMaskeAndPreview();
		history_list.clear();
		future_list.clear();
		view->notifyHistory(false);
		view->notifyFuture(false);
		edt = true;
		view->notifySave(true);
	}
}

void PlanerController::onDelTermin(int index) {
	PTermin* t = planer->list_termin.at(index);
	if (t->prev != NULL) {
		t->prev->next = t->next;
	}
	if (t->next != NULL) {
		t->next->prev = t->prev;
	}
	delete t;
	planer->list_termin.erase(planer->list_termin.begin() + index);
	int counter = 0;
	for (std::vector<PTermin*>::iterator iter = planer->list_termin.begin(); iter != planer->list_termin.end(); iter++) {
		(**iter)._id = counter++;
	}
	Util::setMiniNums(&planer->list_mini, &planer->list_termin);
	view->notifyTermine();
	view->notifyTGruppen();
	view->notifyMinis();
	view->redrawMaske();
	view->notifyMaskeAndPreview();
	history_list.clear();
	future_list.clear();
	view->notifyHistory(false);
	view->notifyFuture(false);
	edt = true;
	view->notifySave(true);
}

PlanerController::PositionInfo::PositionInfo(CTermin* _termin, int _dienst, int _diff)
: termin(_termin), dienst(_dienst), diff(_diff) {
}