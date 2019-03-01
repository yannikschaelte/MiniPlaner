/* 
 * File:   PlanerDialog.h
 * Author: Yannik
 *
 * Created on August 25, 2015, 7:56 PM
 */

#ifndef TERMINEPLANERDIALOG_H
#define	TERMINEPLANERDIALOG_H

#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/datetime.h>
#include <vector>
#include "../model-data/Dienst.h"
#include "../controller-plan/TerminCreator.h"
#include "../model-plan/PTermin.h"
#include "../model-plan/PMessdiener.h"
#include "../model-plan/PFehlzeit.h"
class App;

class TerminePlanerDialog : public wxDialog {
public:
	static const int MODUS_ZEITRAUM = 0;
	static const int MODUS_TERMINE = 1;
	TerminePlanerDialog(wxWindow* parent, App* _app, bool* _edt,
			wxDateTime* _datum_beginn,
			wxDateTime* _datum_ende,
			std::vector<Dienst*>* _list_dienst,
			std::vector<PTermin*>* _list_termin,
			std::vector<PMessdiener*>* _list_mini,
			std::vector<PMGruppe*>* _list_mgruppe,
			std::vector<PFehlzeit*>* _list_fehlzeit);
private:
	App* app;
	int modus;
	wxDateTime* datum_beginn;
	wxDateTime* datum_ende;
	bool* edt;
	std::vector<Dienst*>* list_dienst;
	std::vector<PTermin*>* list_termin;
	std::vector<PMessdiener*>* list_mini;
	std::vector<PMGruppe*>* list_mgruppe;
	std::vector<PFehlzeit*>* list_fehlzeit;
	bool deleteContents;

	//Zeitraum
	wxPanel* pl_zeitraum;
	wxStaticText* st_beginn;
	wxCalendarCtrl* cl_beginn;
	wxStaticText* st_ende;
	wxCalendarCtrl* cl_ende;

	//Termine
	wxNotebook* nb_termine;
	wxPanel* nb_pl_termine;
	wxPanel* nb_pl_tgruppen;
	wxListView* lv_termine;
	wxButton* bt_termine_edt;
	wxButton* bt_termine_del;
	wxListView* lv_tgruppen;

	wxButton* bt_back;
	wxButton* bt_cont;
	wxButton* bt_cancel;

	void initComponents();
	void setModusZeitraum();
	void setModusTermine();
	void notifyTermine(int index = -1);
	void notifyTGruppen();
	void edtTermin(int index);
	void delTermin(int index);
	DECLARE_EVENT_TABLE();
	void onBtBack(wxCommandEvent&);
	void onBtCont(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
	void onBtEdt(wxCommandEvent&);
	void onBtDel(wxCommandEvent&);
	void onLIActivated(wxListEvent& evt);
	void onLIKey(wxListEvent& evt);
	void onClose(wxCloseEvent& evt);
};

#endif	/* TERMINEPLANERDIALOG_H */