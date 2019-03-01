/* 
 * File:   PlanerController.h
 * Author: Yannik
 *
 * Created on September 11, 2015, 2:52 PM
 */

#ifndef PLANERCONTROLLER_H
#define	PLANERCONTROLLER_H

#include "../model-plan/Planer.h"
#include "../view-plan/PlanPlanerDialog.h"
#include "../model-plan/CTermin.h"

class PlanerController {
public:
	PlanerController(Planer* _planer, PlanPlanerDialog* _view);
	~PlanerController();
	Planer* planer;

	bool edt = false;
	int simpleCheckCanCreatePlan();
	void computePlan(bool* continueComputation);
	void onClear();
	void onEntryChanged(PTermin* termin, int dienst, int mini_old_i, PMessdiener* mini_new);
	void onSave();
	void onUndo();
	void onRedo();
	void onEdtTermin(int index);
	void onDelTermin(int index);
	
	static void recalculateAvailableListsInTGruppe(PTermin* termin);
private:

	class PositionInfo {
	public:
		CTermin* termin;
		int dienst;
		int diff; //avai - needed = avai - (req - has)

		PositionInfo(CTermin* _termin, int _dienst, int _diff);
	};

	PlanPlanerDialog* view;
	//deep-copy lists, used internally
	std::vector<CTermin*> tmp_list_termin;
	std::vector<PMessdiener*> tmp_list_mini;
	std::vector<PMGruppe*> tmp_list_mgruppe;
	std::vector<PFehlzeit*> tmp_list_fehlzeit;

	//for undo-redo
	std::vector<std::vector<std::vector<PMessdiener*> > >history_list;
	std::vector<std::vector<std::vector<PMessdiener*> > >future_list;

	void computePlanMinimumSearch(bool* continueComputation);
	void computePlanChronologically(bool* continueComputation);

	void prepareMiniNumsFehlzeiten();
	void prepareMiniNumsFehlzeitenAfter(wxDateTime termin_datum);
	void addProbableMiniNum(PFehlzeit* fehlzeit);

	PositionInfo findMinimumTerminDienst();
	bool fillDienst(CTermin* termin, int dienst);
	void findMinimumMiniNum(std::unordered_set<PMessdiener*>* list_avai, std::unordered_set<PMessdiener*>* list_minimum);

	void eraseSurroundings(CTermin* termin, Dienst* dienst, std::unordered_set<PMessdiener*>* list_minimum);
	void addAllMinis(CTermin* termin, std::unordered_set<PMessdiener*>* list_gesamt, Dienst* dienst, std::unordered_set<PMessdiener*>* list_dienst);

	void prepareMGruppenHard();
	void handleMGruppen(CTermin* termin, int dienst, PMessdiener* mini);
	void handleMGruppenHard(CTermin* termin);
	bool insertMGruppeHard(CTermin* termin, std::vector<PMessdiener*> list, bool keep);

	void handleTGruppen(CTermin* termin, PMessdiener* mini);
	void handleTGruppenP(PTermin* termin, PMessdiener* mini);
	void handleTGruppenWithdrawP(PTermin* termin, PMessdiener* mini);
	void eraseFromAvailableList(CTermin* t, PMessdiener* m);
	void eraseFromAvailableListP(PTermin* t, PMessdiener* m);
	void addToAvailableListIfPossibleP(PTermin* t, PMessdiener* m);

	void initTmpLists();
	void deleteTmpLists();
	void fillRealLists();

	/**
	 * Calculate correct mini.nums from occurrences in mini_lists
	 */
	void putCorrectMiniNums();
	
	/**
	 * Adapt history / future lists.
	 */
	void handleDataChange();
	std::vector<std::vector<PMessdiener*> > copyMinisToList();
	void copyMinisFromList(std::vector<std::vector<PMessdiener*> >* list);
};

#endif	/* PLANERCONTROLLER_H */