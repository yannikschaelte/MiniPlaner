/* 
 * File:   App.cpp
 * Author: Yannik
 * 
 * Created on August 11, 2015, 4:00 PM
 */

#include "App.h"
#include "file/DataFileHandler.h"
#include "file/PlanFileHandler.h"
#include "model-plan/Planer.h"
#include "view-plan/PlanPlanerDialog.h"
#include <algorithm>
#include <set>
#include "update/UpdateChecker.h"
#include "Util.h"

bool App::OnInit() {
	//limited access
	/**wxDateTime today = wxDateTime::Today();
	wxDateTime maximum_date(31, wxDateTime::Dec, 2015);
	if (today.IsLaterThan(maximum_date)) {
		wxMessageDialog dialog(NULL, wxT("Diese Test-Version war nur zeitlich begrenzt verfügbar."), wxMessageBoxCaptionStr, wxOK | wxCENTRE | wxICON_ERROR);
		dialog.ShowModal();
		return false;
	}**/

	single_instance_checker = new wxSingleInstanceChecker;
	if (single_instance_checker->IsAnotherRunning()) {
		delete single_instance_checker;
		return false;
	}

	DataFileHandler::prepareFiles();
	DataFileHandler::implementUpdates();
	DataFileHandler::loadSettings();
	DataFileHandler::loadDienste(&list_dienst);
	updateIntNumDienste();
	DataFileHandler::loadMinis(&list_dienst, &list_mini);
	updateIntNumMinis();
	DataFileHandler::loadEinzeltermine(&list_dienst, &list_einzeltermin);
	updateIntNumEinzeltermine();
	DataFileHandler::loadSerientermine(&list_dienst, &list_serientermin);
	updateIntNumSerientermine();
	DataFileHandler::loadMGruppen(&list_mini, &list_mgruppe);
	DataFileHandler::loadTGruppen(&list_einzeltermin, &list_serientermin, &list_tgruppe);
	DataFileHandler::loadFehlzeiten(&list_mini, &list_einzeltermin, &list_serientermin, &list_fehlzeit);
	DataFileHandler::loadPlanerInfos(&list_planer);
	initOrte();
	initPLZOrte();
	wxDialog::EnableLayoutAdaptation(true);
	frame = new MainFrame(this);
	UpdateChecker::checkUpdate(frame);
	return true;
}

int App::OnExit() {
	for (std::vector<Dienst*>::iterator iter = list_dienst.begin(); iter != list_dienst.end(); iter++) {
		delete *iter;
	}
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		delete *iter;
	}
	for (std::vector<MGruppe*>::iterator iter = list_mgruppe.begin(); iter != list_mgruppe.end(); iter++) {
		delete *iter;
	}
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		delete *iter;
	}
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		delete *iter;
	}
	for (std::vector<TGruppe*>::iterator iter = list_tgruppe.begin(); iter != list_tgruppe.end(); iter++) {
		delete *iter;
	}
	for (std::vector<Fehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end(); iter++) {
		delete *iter;
	}
	DataFileHandler::saveSettings();
	delete single_instance_checker;
	single_instance_checker = 0;
	return 0;
}

bool App::addDienst(Dienst* dienst) {
	for (std::vector<Dienst*>::iterator iter = list_dienst.begin(); iter != list_dienst.end(); iter++) {
		if (Dienst::equal(*iter, dienst)) {
			return false;
		}
	}
	list_dienst.push_back(dienst);

	sortDienste();
	updateIntNumDienste();

	frame->notifyDienste(dienst->_id);

	DataFileHandler::saveDienste(&list_dienst);
	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveSerientermine(&list_serientermin);
	return true;
}

void App::delDienst(int index) {
	Dienst* d = list_dienst.at(index);
	//handle Minis
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		for (std::vector<Dienst*>::iterator iter_d = (**iter).dienste.begin(); iter_d != (**iter).dienste.end(); iter_d++) {
			if (*iter_d == d) {
				(**iter).dienste.erase(iter_d);
				break;
			}
		}
	}
	//handle Termine
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_d = (**iter).dienste.begin(); iter_d != (**iter).dienste.end(); iter_d++) {
			if (iter_d->first == d) {
				(**iter).dienste.erase(iter_d);
				break;
			}
		}
	}
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		for (std::vector< std::pair<Dienst*, int> >::iterator iter_d = (**iter).dienste.begin(); iter_d != (**iter).dienste.end(); iter_d++) {
			if (iter_d->first == d) {
				(**iter).dienste.erase(iter_d);
				break;
			}
		}
	}
	delete d;
	list_dienst.erase(list_dienst.begin() + index);

	frame->notifyDienste();
	frame->notifyMinis();
	frame->notifyEinzeltermine();
	frame->notifySerientermine();
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();

	updateIntNumDienste();

	DataFileHandler::saveDienste(&list_dienst);
	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveSerientermine(&list_serientermin);
}

bool App::edtDienst(int index, const Dienst* d_to) {
	Dienst* d_from = list_dienst.at(index);
	for (std::vector<Dienst*>::iterator iter = list_dienst.begin(); iter != list_dienst.end(); iter++) {
		if (Dienst::equal(*iter, d_to) && *iter != d_from) {
			return false;
		}
	}
	*d_from = *d_to;

	sortDienste();
	updateIntNumDienste();

	frame->notifyDienste(d_from->_id);

	frame->notifyMinis();
	frame->notifyEinzeltermine();
	frame->notifySerientermine();
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();

	DataFileHandler::saveDienste(&list_dienst);
	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveSerientermine(&list_serientermin);
	return true;
}

bool App::addMini(Messdiener* mini) {
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		if (Messdiener::equal(*iter, mini)) {
			return false;
		}
	}
	list_mini.push_back(mini);

	sortMinis();
	updateIntNumMinis();

	frame->notifyMinis(mini->_id);

	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveMGruppen(&list_mgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addPLZOrt(mini->plz_ort);
	return true;
}

void App::delMini(int index) {
	//handle MGruppen
	Messdiener* m = list_mini.at(index);
	for (std::vector<MGruppe*>::iterator iter = list_mgruppe.begin(); iter != list_mgruppe.end();) {
		for (std::vector<Messdiener*>::iterator iter_m = (**iter).list.begin(); iter_m != (**iter).list.end(); iter_m++) {
			if (m == *iter_m) {
				(**iter).list.erase(iter_m);
				break;
			}
		}
		if ((**iter).list.size() < 2) {
			delete *iter;
			iter = list_mgruppe.erase(iter);
		} else {
			iter++;
		}
	}
	//handle Fehlzeiten
	for (std::vector<Fehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end();) {
		if (m == (**iter).mini) {
			delete *iter;
			iter = list_fehlzeit.erase(iter);
		} else {
			iter++;
		}
	}
	//erase and show
	delete m;
	list_mini.erase(list_mini.begin() + index);

	frame->notifyMinis();
	frame->notifyMGruppen();
	frame->notifyFehlzeiten();

	updateIntNumMinis();

	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveMGruppen(&list_mgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
}

bool App::edtMini(int index, const Messdiener* m_to) {
	Messdiener* m_from = list_mini.at(index);
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		if (Messdiener::equal(*iter, m_to) && *iter != m_from) {
			return false;
		}
	}
	*m_from = *m_to;

	sortMinis();
	updateIntNumMinis();

	frame->notifyMinis(m_from->_id);

	//handle MGruppen
	int mgruppe_size = list_mgruppe.size();
	for (int i = 0; i < mgruppe_size; i++) {
		MGruppe mc = *(list_mgruppe.at(i));
		std::sort(mc.list.begin(), mc.list.end(), Messdiener::cmp);
	}
	sortMGruppen();
	frame->notifyMGruppen();
	sortFehlzeiten();
	frame->notifyFehlzeiten();

	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveMGruppen(&list_mgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addPLZOrt(m_from->plz_ort);
	return true;
}

bool App::addEinzeltermin(Einzeltermin* termin) {
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		if (Einzeltermin::equal(*iter, termin)) {
			return false;
		}
	}
	list_einzeltermin.push_back(termin);

	sortEinzeltermine();
	updateIntNumEinzeltermine();

	frame->notifyEinzeltermine(termin->_id);

	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addOrt(termin->ort);
	return true;
}

void App::delEinzeltermin(int index) {
	//handle TGruppen
	Einzeltermin* t = list_einzeltermin.at(index);
	for (std::vector<TGruppe*>::iterator iter_tg = list_tgruppe.begin(); iter_tg != list_tgruppe.end();) {
		for (std::vector<Einzeltermin*>::iterator iter_t = (**iter_tg).list_einzel.begin(); iter_t != (**iter_tg).list_einzel.end(); iter_t++) {
			if (t == *iter_t) {
				(**iter_tg).list_einzel.erase(iter_t);
				break;
			}
		}
		if ((**iter_tg).list_einzel.size() + (**iter_tg).list_serie.size() < 2) {
			delete *iter_tg;
			iter_tg = list_tgruppe.erase(iter_tg);
		} else {
			iter_tg++;
		}
	}
	//handle Fehlzeiten
	for (std::vector<Fehlzeit*>::iterator iter_f = list_fehlzeit.begin(); iter_f != list_fehlzeit.end();) {
		if ((**iter_f).modus == Fehlzeit::EINZELTERMIN && t == (**iter_f).einzeltermin) {
			delete *iter_f;
			iter_f = list_fehlzeit.erase(iter_f);
		} else {
			iter_f++;
		}
	}
	delete t;
	list_einzeltermin.erase(list_einzeltermin.begin() + index);

	frame->notifyEinzeltermine();
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();

	updateIntNumEinzeltermine();

	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
}

bool App::edtEinzeltermin(int index, const Einzeltermin* t_to) {
	Einzeltermin* t_from = list_einzeltermin.at(index);
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		if (Einzeltermin::equal(*iter, t_to) && *iter != t_from) {
			return false;
		}
	}
	*t_from = *t_to;

	sortEinzeltermine();
	updateIntNumEinzeltermine();

	frame->notifyEinzeltermine(t_from->_id);

	for (int i = 0; i < (int) list_tgruppe.size(); i++) {
		TGruppe tc = *(list_tgruppe.at(i));
		std::sort(tc.list_einzel.begin(), tc.list_einzel.end(), Einzeltermin::cmp);
	}
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();


	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addOrt(t_from->ort);
	return true;
}

bool App::addSerientermin(Serientermin* termin) {
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		if (Serientermin::equal(*iter, termin)) {
			return false;
		}
	}
	list_serientermin.push_back(termin);

	sortSerientermine();
	updateIntNumSerientermine();

	frame->notifySerientermine(termin->_id);

	DataFileHandler::saveSerientermine(&list_serientermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addOrt(termin->ort);
	return true;
}

void App::delSerientermin(int index) {
	//handle TGruppen
	Serientermin* t = list_serientermin.at(index);
	for (std::vector<TGruppe*>::iterator iter_tg = list_tgruppe.begin(); iter_tg != list_tgruppe.end();) {
		for (std::vector<Serientermin*>::iterator iter_t = (**iter_tg).list_serie.begin(); iter_t != (**iter_tg).list_serie.end(); iter_t++) {
			if (t == *iter_t) {
				(**iter_tg).list_serie.erase(iter_t);
				break;
			}
		}
		if ((**iter_tg).list_einzel.size() + (**iter_tg).list_serie.size() < 2) {
			delete *iter_tg;
			iter_tg = list_tgruppe.erase(iter_tg);
		} else {
			iter_tg++;
		}
	}
	//handle Fehlzeiten
	for (std::vector<Fehlzeit*>::iterator iter_f = list_fehlzeit.begin(); iter_f != list_fehlzeit.end();) {
		if ((**iter_f).modus == Fehlzeit::SERIENTERMIN && t == (**iter_f).serientermin) {
			delete *iter_f;
			iter_f = list_fehlzeit.erase(iter_f);
		} else {
			iter_f++;
		}
	}
	delete t;
	list_serientermin.erase(list_serientermin.begin() + index);

	frame->notifySerientermine();
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();

	updateIntNumSerientermine();

	DataFileHandler::saveSerientermine(&list_serientermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
}

bool App::edtSerientermin(int index, const Serientermin* t_to) {
	Serientermin* t_from = list_serientermin.at(index);
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		if (Serientermin::equal(*iter, t_to) && *iter != t_from) {
			return false;
		}
	}
	*t_from = *t_to;

	sortSerientermine();
	updateIntNumSerientermine();

	frame->notifySerientermine(t_from->_id);

	for (int i = 0; i < (int) list_tgruppe.size(); i++) {
		TGruppe tc = *(list_tgruppe.at(i));
		std::sort(tc.list_serie.begin(), tc.list_serie.end(), Serientermin::cmp);
	}
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();

	DataFileHandler::saveSerientermine(&list_serientermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	addOrt(t_from->ort);
	return true;
}

void App::addMGruppe(MGruppe* mgruppe) {
	list_mgruppe.push_back(mgruppe);
	sortMGruppen();

	int i = 0;
	while (list_mgruppe.at(i) != mgruppe) i++;

	frame->notifyMGruppen(i);
	DataFileHandler::saveMGruppen(&list_mgruppe);
}

void App::delMGruppe(int index) {
	delete list_mgruppe.at(index);
	list_mgruppe.erase(list_mgruppe.begin() + index);
	frame->notifyMGruppen();
	DataFileHandler::saveMGruppen(&list_mgruppe);
}

void App::edtMGruppe(int index, MGruppe* mg_to) {
	MGruppe* mg_from = list_mgruppe.at(index);
	*mg_from = *mg_to;
	sortMGruppen();

	int i = 0;
	while (list_mgruppe.at(i) != mg_from) i++;

	frame->notifyMGruppen(i);
	DataFileHandler::saveMGruppen(&list_mgruppe);
}

void App::addTGruppe(TGruppe* tgruppe) {
	list_tgruppe.push_back(tgruppe);

	int i = 0;
	while (list_tgruppe.at(i) != tgruppe) i++;

	frame->notifyTGruppen(i);
	DataFileHandler::saveTGruppen(&list_tgruppe);
}

void App::delTGruppe(int index) {
	delete list_tgruppe.at(index);
	list_tgruppe.erase(list_tgruppe.begin() + index);
	frame->notifyTGruppen();
	DataFileHandler::saveTGruppen(&list_tgruppe);
}

void App::edtTGruppe(int index, const TGruppe* tg_to) {
	TGruppe* tg_from = list_tgruppe.at(index);
	*tg_from = *tg_to;

	int i = 0;
	while (list_tgruppe.at(i) != tg_from) i++;

	frame->notifyTGruppen(i);
	DataFileHandler::saveTGruppen(&list_tgruppe);
}

bool App::addFehlzeit(Fehlzeit* fehlzeit) {
	for (std::vector<Fehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end(); iter++) {
		if (Fehlzeit::equal(*iter, fehlzeit)) {
			return false;
		}
	}
	list_fehlzeit.push_back(fehlzeit);
	sortFehlzeiten();

	int i = 0;
	while (list_fehlzeit.at(i) != fehlzeit) i++;

	frame->notifyFehlzeiten(i);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	return true;
}

void App::delFehlzeit(int index) {
	delete list_fehlzeit.at(index);
	list_fehlzeit.erase(list_fehlzeit.begin() + index);
	frame->notifyFehlzeiten();
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
}

bool App::edtFehlzeit(int index, Fehlzeit* f_to) {
	Fehlzeit* f_from = list_fehlzeit.at(index);
	for (std::vector<Fehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end(); iter++) {
		if (Fehlzeit::equal(*iter, f_to) && *iter != f_from) {
			return false;
		}
	}
	*f_from = *f_to;
	sortFehlzeiten();

	int i = 0;
	while (list_fehlzeit.at(i) != f_from) i++;

	frame->notifyFehlzeiten(i);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	return true;
}

void App::createAndOpenPlanPlaner(wxDateTime datum_beginn, wxDateTime datum_ende, std::vector<Dienst*> list_dienst,
		std::vector<PTermin*> list_termin, std::vector<PMessdiener*> list_mini,
		std::vector<PMGruppe*> list_pmgruppe, std::vector<PFehlzeit*> list_pfehlzeit) {
	PlanerInfo info = PlanFileHandler::createDir(datum_beginn, datum_ende);
	list_planer.push_back(info);
	sortPlaene();

	int i = 0;
	while (!list_planer.at(i).datum_beginn.IsSameDate(info.datum_beginn)
			|| !list_planer.at(i).datum_ende.IsSameDate(info.datum_ende)
			|| list_planer.at(i).counter != info.counter) i++;

	frame->notifyPlaene(i);
	wxWindowDisabler disabler;
	DataFileHandler::savePlanerInfos(&list_planer);
	Planer* planer = new Planer(datum_beginn, datum_ende, list_dienst, list_termin, list_mini, list_pmgruppe, list_pfehlzeit, info.counter);
	PlanFileHandler::savePlaner(planer);
	new PlanPlanerDialog(NULL, planer);
}

void App::delPlanPlaner(int index) {
	PlanerInfo info = list_planer.at(index);
	list_planer.erase(list_planer.begin() + index);
	frame->notifyPlaene();
	DataFileHandler::savePlanerInfos(&list_planer);
	PlanFileHandler::deleteDir(info);
}

void App::edtPlanPlaner(int index) {
	wxWindowDisabler disabler;
	PlanerInfo info = list_planer.at(index);
	Planer* planer = new Planer(info.datum_beginn, info.datum_ende, info.counter);
	PlanFileHandler::loadPlaner(planer);
	new PlanPlanerDialog(NULL, planer);
}

void App::importMinis(std::vector<Messdiener*> list_import) {
	int num_import = list_import.size();
	wxString st_contained;
	for (int i = 0; i < num_import; i++) {
		Messdiener* m = list_import.at(i);
		bool contained = false;
		for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end() && !contained; iter++) {
			if (Messdiener::equal(*iter, m)) {
				contained = true;
			}
		}
		if (contained) {
			st_contained += m->name + wxT(", ") + m->vorname + wxT("\n");
			delete m;
		} else {
			m->dienste = list_dienst;
			list_mini.push_back(m);
		}
	}
	sortMinis();
	frame->notifyMinis();

	updateIntNumMinis();

	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveMGruppen(&list_mgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	if (st_contained.length() > 0) {
		wxMessageDialog dialog(frame, R::MSG_IMPORT_NOT_POSSIBLE + wxT("\n") + st_contained, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		dialog.ShowModal();
	}
	initPLZOrte();
}

void App::importEinzeltermine(std::vector<Einzeltermin*> list_import) {
	int num_import = list_import.size();
	wxString st_contained;
	for (int i = 0; i < num_import; i++) {
		Einzeltermin* t = list_import.at(i);
		bool contained = false;
		for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end() && !contained; iter++) {
			if (Einzeltermin::equal(*iter, t)) {
				contained = true;
			}
		}
		if (contained) {
			st_contained += Einzeltermin::printShort(t) + wxT("\n");
			delete t;
		} else {
			list_einzeltermin.push_back(t);
		}
	}

	sortEinzeltermine();
	updateIntNumEinzeltermine();

	frame->notifyEinzeltermine();

	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveTGruppen(&list_tgruppe);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
	if (st_contained.length() > 0) {
		wxMessageDialog dialog(frame, R::MSG_IMPORT_NOT_POSSIBLE + wxT("\n") + st_contained, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		dialog.ShowModal();
	}
	initOrte();
}

void App::initOrte() {
	list_ort.clear();
	std::set<wxString> set_ort;
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		set_ort.insert((**iter).ort);
	}
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		set_ort.insert((**iter).ort);
	}
	for (std::set<wxString>::iterator iter = set_ort.begin(); iter != set_ort.end(); iter++) {
		list_ort.push_back(*iter);
	}
	std::sort(list_ort.begin(), list_ort.end());
}

void App::addOrt(wxString ort) {
	if (std::find(list_ort.begin(), list_ort.end(), ort) == list_ort.end()) list_ort.push_back(ort);
	std::sort(list_ort.begin(), list_ort.end());
}

void App::initPLZOrte() {
	list_plzort.clear();
	std::set<wxString> set_plzort;
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		set_plzort.insert((**iter).plz_ort);
	}
	for (std::set<wxString>::iterator iter = set_plzort.begin(); iter != set_plzort.end(); iter++) {
		list_plzort.push_back(*iter);
	}
	std::sort(list_plzort.begin(), list_plzort.end());
}

void App::addPLZOrt(wxString plzort) {
	if (std::find(list_plzort.begin(), list_plzort.end(), plzort) == list_plzort.end()) list_plzort.push_back(plzort);
	std::sort(list_plzort.begin(), list_plzort.end());
}

void App::onLanguageChange() {
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		if (!(**iter).geburtstag.IsEmpty()) {
			(**iter).geburtstag = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).geburtstag));
		}
	}
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		if (!(**iter).datum.IsEmpty()) {
			(**iter).datum = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).datum));
		}
	}
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		if (!(**iter).datum_beginn.IsEmpty()) {
			(**iter).datum_beginn = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).datum_beginn));
		}
		if (!(**iter).datum_ende.IsEmpty()) {
			(**iter).datum_ende = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).datum_ende));
		}
	}
	for (std::vector<Fehlzeit*>::iterator iter = list_fehlzeit.begin(); iter != list_fehlzeit.end(); iter++) {
		if ((**iter).modus == Fehlzeit::ZEITRAUM) {
			if (!(**iter).beginn.IsEmpty()) {
				(**iter).beginn = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).beginn));
			}
			if (!(**iter).ende.IsEmpty()) {
				(**iter).ende = Util::wxDateTime_to_wxString(Util::wxString_to_wxDateTime((**iter).ende));
			}
		}
	}
	frame->notifyMinis();
	frame->notifyMGruppen();
	frame->notifyEinzeltermine();
	frame->notifySerientermine();
	frame->notifyTGruppen();
	frame->notifyFehlzeiten();
	frame->notifyPlaene();
	DataFileHandler::saveMinis(&list_mini);
	DataFileHandler::saveEinzeltermine(&list_einzeltermin);
	DataFileHandler::saveSerientermine(&list_serientermin);
	DataFileHandler::saveFehlzeiten(&list_fehlzeit);
}

void App::sortDienste() {
	std::sort(list_dienst.begin(), list_dienst.end(), Dienst::cmp);
}

void App::sortMinis() {
	std::sort(list_mini.begin(), list_mini.end(), Messdiener::cmp);
}

void App::sortEinzeltermine() {
	std::sort(list_einzeltermin.begin(), list_einzeltermin.end(), Einzeltermin::cmp);
}

void App::sortSerientermine() {
	std::sort(list_serientermin.begin(), list_serientermin.end(), Serientermin::cmp);
}

void App::sortMGruppen() {
	std::sort(list_mgruppe.begin(), list_mgruppe.end(), MGruppe::cmp);
}

void App::sortFehlzeiten() {
	std::sort(list_fehlzeit.begin(), list_fehlzeit.end(), Fehlzeit::cmp);
}

void App::sortPlaene() {
	std::sort(list_planer.begin(), list_planer.end(), PlanerInfo::cmp);
}

void App::updateIntNumDienste() {
	int counter = 0;
	for (std::vector<Dienst*>::iterator iter = list_dienst.begin(); iter != list_dienst.end(); iter++) {
		(**iter)._id = counter++;
	}
}

void App::updateIntNumMinis() {
	int counter = 0;
	for (std::vector<Messdiener*>::iterator iter = list_mini.begin(); iter != list_mini.end(); iter++) {
		(**iter)._id = counter++;
	}
}

void App::updateIntNumEinzeltermine() {
	int counter = 0;
	for (std::vector<Einzeltermin*>::iterator iter = list_einzeltermin.begin(); iter != list_einzeltermin.end(); iter++) {
		(**iter)._id = counter++;
	}
}

void App::updateIntNumSerientermine() {
	int counter = 0;
	for (std::vector<Serientermin*>::iterator iter = list_serientermin.begin(); iter != list_serientermin.end(); iter++) {
		(**iter)._id = counter++;
	}
}