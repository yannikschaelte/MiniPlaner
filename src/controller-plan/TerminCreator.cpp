/* 
 * File:   TerminCreator.cpp
 * Author: Yannik
 * 
 * Created on August 28, 2015, 1:26 PM
 */

#include "TerminCreator.h"
#include <algorithm>
#include "../Util.h"

TerminCreator::PTerminHolder::PTerminHolder(PTermin* _termin, Einzeltermin* _e) {
	termin = _termin;
	e = _e;
	s = (Serientermin*) NULL;
}

TerminCreator::PTerminHolder::PTerminHolder(PTermin* _termin, Serientermin* _s) {
	termin = _termin;
	s = _s;
	e = (Einzeltermin*) NULL;
}

bool TerminCreator::PTerminHolder::cmp(const PTerminHolder& p1, const PTerminHolder& p2) {
	return PTermin::cmp(p1.termin, p2.termin);
}

void TerminCreator::createLists(wxDateTime datum_beginn, wxDateTime datum_ende,
		std::vector<Dienst*>* dlist,
		std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist, std::vector<TGruppe*>* tglist,
		std::vector<Messdiener*>* mlist, std::vector<MGruppe*>* mglist, std::vector<Fehlzeit*>* flist,
		std::vector<Dienst*>* pdlist, std::vector<PTerminHolder>* pthlist, std::vector<PMessdiener*>* pmlist, std::vector<PMGruppe*>* pmglist, std::vector<PFehlzeit*>* pflist) {
	//prepare lists
	pdlist->clear();
	pthlist->clear();
	pmlist->clear();
	pmglist->clear();
	pflist->clear();
	//get new services
	createDienste(dlist, pdlist);
	//create intermediate objects
	createOrderedPTerminOriginList(datum_beginn, datum_ende, elist, slist, pthlist);
	addTGruppen(tglist, pthlist);

	std::vector<std::pair<PMessdiener*, Messdiener*> > pmhlist;
	createPMessdienerOriginList(mlist, &pmhlist);
	addMGruppen(mglist, &pmhlist, pmglist);
	//translate services (dienst_ids need to be set)
	for (std::vector<PTerminHolder>::iterator iter = pthlist->begin(); iter != pthlist->end(); iter++) {
		for (std::vector<std::pair<Dienst*, int> >::iterator iter_d = (*iter).termin->list_dienst_num.begin(); iter_d != (*iter).termin->list_dienst_num.end(); iter_d++) {
			(*iter_d).first = pdlist->at((*iter_d).first->_id);
		}
	}
	for (std::vector<std::pair<PMessdiener*, Messdiener*> >::iterator iter = pmhlist.begin(); iter != pmhlist.end(); iter++) {
		for (int i = 0; i < (int) iter->first->dienste.size(); i++) {
			iter->first->dienste.at(i) = pdlist->at(iter->first->dienste.at(i)->_id);
		}
	}
	//create needed objects from intermediate objects
	for (std::vector<std::pair<PMessdiener*, Messdiener*> >::iterator iter = pmhlist.begin(); iter != pmhlist.end(); iter++) {
		pmlist->push_back(iter->first);
	}
	//create list of Zeitraum-Fehlzeiten, needed for distribution of minis later
	createFehlzeitList(datum_beginn, datum_ende, pmlist, flist, pflist);
}

void TerminCreator::createDienste(std::vector<Dienst*>* dlist, std::vector<Dienst*>* pdlist) {
	for (std::vector<Dienst*>::iterator iter = dlist->begin(); iter != dlist->end(); iter++) {
		Dienst* d = new Dienst((**iter).name);
		pdlist->push_back(d);
	}
}

void TerminCreator::createOrderedPTerminOriginList(wxDateTime datum_beginn, wxDateTime datum_ende,
		std::vector<Einzeltermin*>* elist, std::vector<Serientermin*>* slist,
		std::vector<PTerminHolder>* pthlist) {
	//Einzeltermine
	for (std::vector<Einzeltermin*>::iterator iter = elist->begin(); iter != elist->end(); iter++) {
		Einzeltermin t = **iter;
		wxDateTime datum = Util::wxString_to_wxDateTime(t.datum);
		if (!datum_beginn.IsLaterThan(datum) && !datum_ende.IsEarlierThan(datum)) {
			PTermin* termin = new PTermin(t.name, t.ort, Util::wxString_to_wxDateTime(t.datum), t.zeit_beginn, t.bem, t.dienste);
			pthlist->push_back(PTerminHolder(termin, *iter));
		}
	}
	//Serientermine
	for (std::vector<Serientermin*>::iterator iter = slist->begin(); iter != slist->end(); iter++) {
		Serientermin t = **iter;
		wxDateTime beginn = datum_beginn;
		if (!t.datum_beginn.IsEmpty()) {
			wxDateTime t_datum_beginn = Util::wxString_to_wxDateTime(t.datum_beginn);
			if (t_datum_beginn.IsLaterThan(datum_beginn)) {
				beginn = t_datum_beginn;
			}
		}
		wxDateTime ende = datum_ende;
		if (!t.datum_ende.IsEmpty()) {
			wxDateTime t_datum_ende = Util::wxString_to_wxDateTime(t.datum_ende);
			if (t_datum_ende.IsEarlierThan(datum_ende)) {
				ende = t_datum_ende;
			}
		}
		switch (t.modus) {
			case Serientermin::TAEGLICH:
			{
				wxDateTime current_day(beginn);
				while (!current_day.IsLaterThan(ende)) {
					pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					current_day.Add(wxDateSpan(0, 0, 0, 1));
				}
			}
				break;
			case Serientermin::WOECHENTLICH:
			{
				int wday = t.wochentag;
				int cur_wday = beginn.GetWeekDay();
				wxDateTime current_day(beginn);
				current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
				while (!current_day.IsLaterThan(ende)) {
					pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					current_day.Add(wxDateSpan(0, 0, 0, 7));
				}
			}
				break;
			case Serientermin::GERADE_KW:
			{
				int wday = t.wochentag;
				int cur_wday = beginn.GetWeekDay();
				wxDateTime current_day(beginn);
				current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
				while (!current_day.IsLaterThan(ende)) {
					//std:: week starts with monday
					if (current_day.GetWeekOfYear() % 2 == 0) {
						pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					}
					current_day.Add(wxDateSpan(0, 0, 0, 7));
				}
			}
				break;
			case Serientermin::UNGERADE_KW:
			{
				int wday = t.wochentag;
				int cur_wday = beginn.GetWeekDay();
				wxDateTime current_day(beginn);
				current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
				while (!current_day.IsLaterThan(ende)) {
					if (current_day.GetWeekOfYear() % 2 != 0) {
						pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					}
					current_day.Add(wxDateSpan(0, 0, 0, 7));
				}
			}
				break;
			case Serientermin::N_WOECHENTLICH:
			{
				wxDateTime current_day(Util::wxString_to_wxDateTime(t.datum_beginn));
				int wday = t.wochentag;
				int cur_wday = current_day.GetWeekDay();
				current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
				while (!current_day.IsLaterThan(ende)) {
					if (!current_day.IsEarlierThan(beginn)) {
						pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					}
					current_day.Add(wxDateSpan(0, 0, 0, t.n * 7));
				}
			}
				break;
			case Serientermin::W_IM_MONAT:
			{
				int wday = t.wochentag;
				wxDateTime current_day(beginn);
				if (t.n < 5) {
					current_day.SetDay(1);
					int cur_wday = current_day.GetWeekDay();
					current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
					int month = current_day.GetMonth();
					current_day.Add(wxDateSpan(0, 0, 0, 7 * t.n));
					while (!current_day.IsLaterThan(ende)) {
						if (month == current_day.GetMonth()) {
							pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
							current_day.Add(wxDateSpan(0, 1, 0, 0));
						}
						current_day.SetDay(1);
						cur_wday = current_day.GetWeekDay();
						current_day.Add(wxDateSpan(0, 0, 0, (wday < cur_wday) ? wday - cur_wday + 7 : wday - cur_wday));
						month = current_day.GetMonth();
						current_day.Add(wxDateSpan(0, 0, 0, 7 * t.n));
					}
				} else {
					//get first day
					current_day.SetDay(1);
					current_day.Add(wxDateSpan(0, 1, 0, 0));
					current_day.Add(wxDateSpan(0, 0, 0, -1));
					int cur_wday = current_day.GetWeekDay();
					current_day.Add(wxDateSpan(0, 0, 0, (wday <= cur_wday) ? wday - cur_wday : wday - cur_wday - 7));
					if (t.n == 5) {//vorletzter [Wochentag]
						current_day.Add(wxDateSpan(0, 0, -1, 0));
					}
					while (!current_day.IsLaterThan(ende)) {
						if (!current_day.IsEarlierThan(beginn)) {
							pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
						}
						//one month up
						current_day.Add(wxDateSpan(0, 1, 0, 0));
						//get day
						current_day.SetDay(1);
						current_day.Add(wxDateSpan(0, 1, 0, 0));
						current_day.Add(wxDateSpan(0, 0, 0, -1));
						int cur_wday = current_day.GetWeekDay();
						current_day.Add(wxDateSpan(0, 0, 0, (wday <= cur_wday) ? wday - cur_wday : wday - cur_wday - 7));
						if (t.n == 5) {//vorletzter [Wochentag]
							current_day.Add(wxDateSpan(0, 0, -1, 0));
						}
					}
				}
			}
				break;
			case Serientermin::MONATLICH:
			{
				int mday = t.n;
				wxDateTime current_day(beginn);
				wxDateTime current_day2(current_day);
				current_day2.SetDay(1);
				current_day2.Add(wxDateSpan(0, 1, 0, 0));
				current_day2.Add(wxDateSpan(0, 0, 0, -1));
				bool mHasDay = true;
				if (current_day2.GetDay() < mday) {
					mHasDay = false;
				} else {
					current_day.SetDay(mday);
				}
				while (!current_day.IsLaterThan(ende)) {
					if (!current_day.IsEarlierThan(beginn) && mHasDay) {
						pthlist->push_back(PTerminHolder(new PTermin(t.name, t.ort, current_day, t.zeit_beginn, t.bem, t.dienste), *iter));
					}
					current_day.Add(wxDateSpan(0, 1, 0, 0));
					//get new day if possible
					wxDateTime current_day2(current_day);
					current_day2.SetDay(1);
					current_day2.Add(wxDateSpan(0, 1, 0, 0));
					current_day2.Add(wxDateSpan(0, 0, 0, -1));
					mHasDay = true;
					if (current_day2.GetDay() < mday) {
						mHasDay = false;
					} else {
						current_day.SetDay(mday);
					}
				}
			}
				break;
		}
		std::sort(pthlist->begin(), pthlist->end(), PTerminHolder::cmp);
	}
}

void TerminCreator::addTGruppen(std::vector<TGruppe*>* tglist, std::vector<PTerminHolder>* pthlist) {
	//first date used later on, so prepare for that case
	if (pthlist->empty()) {
		return;
	}
	for (std::vector<TGruppe*>::iterator tgiter = tglist->begin(); tgiter != tglist->end(); tgiter++) {
		if ((**tgiter).list_serie.empty()) {
			//alle Termine der TGruppe bilden eine PTGruppe
			std::vector<PTerminHolder>::iterator pthiter = pthlist->begin();
			std::vector<PTermin*> current_list;
			for (std::vector<PTerminHolder>::iterator pthiter = pthlist->begin(); pthiter != pthlist->end(); pthiter++) {
				if (std::find((**tgiter).list_einzel.begin(), (**tgiter).list_einzel.end(), pthiter->e) != (**tgiter).list_einzel.end()) {
					current_list.push_back(pthiter->termin);
				}
			}
			for (int i = 1; i < (int) current_list.size(); i++) {
				current_list.at(i - 1)->next = current_list.at(i);
				current_list.at(i)->prev = current_list.at(i - 1);
			}
		} else {//week by week
			int wday = (**tgiter).wochentag;
			wxDateTime current_day(pthlist->at(0).termin->datum);
			int cur_wday = current_day.GetWeekDay();
			current_day.Add(wxDateSpan(0, 0, 0, (wday <= cur_wday) ? wday - cur_wday : wday - cur_wday - 7));
			wxDateTime week_later(current_day);
			week_later.Add(wxDateSpan(0, 0, 0, 7));
			std::vector<PTerminHolder>::iterator pthiter = pthlist->begin();
			while (!current_day.IsLaterThan(pthlist->back().termin->datum)) {
				std::vector<PTermin*> current_list;
				while (pthiter != pthlist->end() && pthiter->termin->datum.IsEarlierThan(week_later)) {
					if (pthiter->e != NULL) {
						if (std::find((**tgiter).list_einzel.begin(), (**tgiter).list_einzel.end(), pthiter->e) != (**tgiter).list_einzel.end()) {
							current_list.push_back(pthiter->termin);
						}
					} else {//pthiter->s != NULL
						if (std::find((**tgiter).list_serie.begin(), (**tgiter).list_serie.end(), pthiter->s) != (**tgiter).list_serie.end()) {
							current_list.push_back(pthiter->termin);
						}
					}
					pthiter++;
				}
				for (int i = 1; i < (int) current_list.size(); i++) {
					current_list.at(i - 1)->next = current_list.at(i);
					current_list.at(i)->prev = current_list.at(i - 1);
				}
				current_day.Add(wxDateSpan(0, 0, 1, 0));
				week_later.Add(wxDateSpan(0, 0, 1, 0));
			}
		}
	}
}

void TerminCreator::createPMessdienerOriginList(std::vector<Messdiener*>* mlist, std::vector<std::pair<PMessdiener*, Messdiener*> >* pmhlist) {
	for (std::vector<Messdiener*>::iterator iter = mlist->begin(); iter != mlist->end(); iter++) {
		pmhlist->push_back(std::make_pair(new PMessdiener((**iter).name, (**iter).vorname, (**iter).dienste), *iter));
	}
}

void TerminCreator::addMGruppen(std::vector<MGruppe*>* mglist, std::vector<std::pair<PMessdiener*, Messdiener*> >* pmhlist, std::vector<PMGruppe*>* pmglist) {
	for (std::vector<MGruppe*>::iterator iter = mglist->begin(); iter != mglist->end(); iter++) {
		std::vector<PMessdiener*> gruppe;
		for (std::vector<Messdiener*>::iterator iter_m = (**iter).list.begin(); iter_m != (**iter).list.end(); iter_m++) {
			gruppe.push_back(pmhlist->at((**iter_m)._id).first);
		}
		PMGruppe* pmgruppe = new PMGruppe((**iter).modus, gruppe);
		pmglist->push_back(pmgruppe);
		for (std::vector<Messdiener*>::iterator iter_m = (**iter).list.begin(); iter_m != (**iter).list.end(); iter_m++) {
			pmhlist->at((*iter_m)->_id).first->gruppe = pmgruppe;
		}
	}
}

void TerminCreator::fillMLists(std::vector<PTerminHolder>* pthlist, std::vector<PMessdiener*>* pmlist,
		std::vector<Fehlzeit*>* flist, std::vector<Dienst*>* pdlist) {
	//fill lists according to abilities
	std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > > list_dienst_minis;
	for (std::vector<Dienst*>::iterator iter_d = pdlist->begin(); iter_d != pdlist->end(); iter_d++) {
		std::vector<PMessdiener*> m_liste;
		for (std::vector<PMessdiener*>::iterator iter_m = pmlist->begin(); iter_m != pmlist->end(); iter_m++) {
			if (std::find((**iter_m).dienste.begin(), (**iter_m).dienste.end(), *iter_d) != (**iter_m).dienste.end()) {
				m_liste.push_back(*iter_m);
			}
		}
		list_dienst_minis.push_back(std::make_pair(*iter_d, m_liste));
	}
	//fill list_dienst_minis (with ZEROs) and list_dienst_minis_possible (according to above abilities)
	for (std::vector<PTerminHolder>::iterator iter_t = pthlist->begin(); iter_t != pthlist->end(); iter_t++) {
		for (std::vector<std::pair<Dienst*, int> >::iterator iter_d = iter_t->termin->list_dienst_num.begin(); iter_d != iter_t->termin->list_dienst_num.end(); iter_d++) {
			std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_list = list_dienst_minis.begin();
			for (; iter_list->first != iter_d->first; iter_list++) {
			}
			iter_t->termin->list_dienst_minis_possible.push_back(*iter_list);
			//fill in same order and initiate with NULL pointers (needed later and for file)
			std::vector<PMessdiener*> mset;
			mset.reserve(iter_d->second);
			for (int i = 0; i < iter_d->second; i++) {
				mset.push_back(NULL);
			}
			iter_t->termin->list_dienst_minis.push_back(std::make_pair(iter_list->first, mset));
		}
	}
	//iterate fehlzeiten and delete accordingly
	for (std::vector<Fehlzeit*>::iterator iter_f = flist->begin(); iter_f != flist->end(); iter_f++) {
		switch ((**iter_f).modus) {
			case Fehlzeit::ZEITRAUM:
			{
				wxDateTime beginn = Util::wxString_to_wxDateTime((**iter_f).beginn);
				wxDateTime ende = Util::wxString_to_wxDateTime((**iter_f).ende);
				std::vector<PTerminHolder>::iterator iter_t = pthlist->begin();
				while (iter_t != pthlist->end() && iter_t->termin->datum.IsEarlierThan(beginn)) {
					iter_t++;
				}
				while (iter_t != pthlist->end() && !iter_t->termin->datum.IsLaterThan(ende)) {
					for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = iter_t->termin->list_dienst_minis_possible.begin();
							iter_poss != iter_t->termin->list_dienst_minis_possible.end(); iter_poss++) {
						Util::erase_from_minivec(&iter_poss->second, pmlist->at((**iter_f).mini->_id));
					}
					iter_t++;
				}
				break;
			}
			case Fehlzeit::WOCHENTAG:
			{
				int wday = (**iter_f).wochentag;
				wxString zeit_beginn = (**iter_f).beginn;
				wxString zeit_ende = (**iter_f).ende;
				for (std::vector<PTerminHolder>::iterator iter_t = pthlist->begin(); iter_t != pthlist->end(); iter_t++) {
					if (iter_t->termin->datum.GetWeekDay() == wday && iter_t->termin->zeit_beginn >= zeit_beginn && iter_t->termin->zeit_beginn <= zeit_ende) {
						for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = iter_t->termin->list_dienst_minis_possible.begin();
								iter_poss != iter_t->termin->list_dienst_minis_possible.end(); iter_poss++) {
							Util::erase_from_minivec(&iter_poss->second, pmlist->at((**iter_f).mini->_id));
						}
					}
				}
				break;
			}
			case Fehlzeit::EINZELTERMIN:
			{
				for (std::vector<PTerminHolder>::iterator iter_t = pthlist->begin(); iter_t != pthlist->end(); iter_t++) {
					if (iter_t->e == (**iter_f).einzeltermin) {
						for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = iter_t->termin->list_dienst_minis_possible.begin();
								iter_poss != iter_t->termin->list_dienst_minis_possible.end(); iter_poss++) {
							Util::erase_from_minivec(&iter_poss->second, pmlist->at((**iter_f).mini->_id));
						}
					}
				}
				break;
			}
			case Fehlzeit::SERIENTERMIN:
			{
				for (std::vector<PTerminHolder>::iterator iter_t = pthlist->begin(); iter_t != pthlist->end(); iter_t++) {
					if (iter_t->s == (**iter_f).serientermin) {
						for (std::vector<std::pair<Dienst*, std::vector<PMessdiener*> > >::iterator iter_poss = iter_t->termin->list_dienst_minis_possible.begin();
								iter_poss != iter_t->termin->list_dienst_minis_possible.end(); iter_poss++) {
							Util::erase_from_minivec(&iter_poss->second, pmlist->at((**iter_f).mini->_id));
						}
					}
				}
				break;
			}
		}
	}
	//initiate available lists, same as possible lists
	for (std::vector<PTerminHolder>::iterator iter_t = pthlist->begin(); iter_t != pthlist->end(); iter_t++) {
		iter_t->termin->list_dienst_minis_available = iter_t->termin->list_dienst_minis_possible;
	}
}

void TerminCreator::createTerminList(std::vector<PTerminHolder>* pthlist, std::vector<PTermin*>* ptlist) {
	for (std::vector<PTerminHolder>::iterator iter = pthlist->begin(); iter != pthlist->end(); iter++) {
		ptlist->push_back(iter->termin);
	}
}

void TerminCreator::createFehlzeitList(wxDateTime datum_beginn, wxDateTime datum_ende, std::vector<PMessdiener*>* pmlist, std::vector<Fehlzeit*>* flist, std::vector<PFehlzeit*>* pflist) {
	for (std::vector<Fehlzeit*>::iterator iter_f = flist->begin(); iter_f != flist->end(); iter_f++) {
		if ((**iter_f).modus != Fehlzeit::ZEITRAUM) continue;
		wxDateTime f_datum_beginn = Util::wxString_to_wxDateTime((**iter_f).beginn);
		wxDateTime f_datum_ende = Util::wxString_to_wxDateTime((**iter_f).ende);
		if (f_datum_beginn.IsLaterThan(datum_ende) || f_datum_ende.IsEarlierThan(datum_beginn)) continue;
		pflist->push_back(new PFehlzeit(pmlist->at((**iter_f).mini->_id), f_datum_beginn, f_datum_ende));
	}
}