/* 
 * File:   PMiniChoiceDialog.h
 * Author: Yannik
 *
 * Created on September 26, 2015, 10:24 AM
 */

#ifndef PMINICHOICEDIALOG_H
#define	PMINICHOICEDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../model-plan/PTermin.h"
#include "../model-plan/PMessdiener.h"
class PlanerController;
class PlanPlanerDialog;

class PMiniChoiceDialog : public wxDialog {
public:
	PMiniChoiceDialog(PlanPlanerDialog* _parent, PlanerController* _controller, PTermin* _termin, int _dienst, int _mini);
private:
	PlanPlanerDialog* parent;
	PlanerController* controller;
	PTermin* termin;
	int dienst;
	int mini;
	std::vector<PMessdiener*> tmp_list;

	wxListView* lv_minis;
	DECLARE_EVENT_TABLE();
	void onKillFocus(wxFocusEvent&);
	void onLISelected(wxListEvent& evt);
	void onClose(wxCloseEvent& evt);
};

#endif	/* PMINICHOICEDIALOG_H */

