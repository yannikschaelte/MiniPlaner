/* 
 * File:   PMiniChoiceDialog.cpp
 * Author: Yannik
 * 
 * Created on September 26, 2015, 10:24 AM
 */

#include "PMiniChoiceDialog.h"
#include <wx/event.h>
#include <algorithm>
#include "../controller-plan/PlanerController.h"
#include "PlanPlanerDialog.h"
#include "../R.h"

PMiniChoiceDialog::PMiniChoiceDialog(PlanPlanerDialog* _parent, PlanerController* _controller, PTermin* _termin, int _dienst, int _mini)
: wxDialog(_parent, R::ID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0), parent(_parent), controller(_controller), termin(_termin), dienst(_dienst), mini(_mini) {
	//DONE: _parent instead of parent !!!
	lv_minis = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem col;
	col.SetText(wxString::Format(wxT("%i  "), termin->_id + 1) + PTermin::printBasics(termin) + wxT(": ") + termin->list_dienst_num.at(dienst).first->name);
	lv_minis->InsertColumn(0, col);

	tmp_list = termin->list_dienst_minis_available.at(dienst).second;
	int num_minis = tmp_list.size();
	PMessdiener* m = termin->list_dienst_minis.at(dienst).second.at(mini);
	if (m != (PMessdiener*) NULL) {
		tmp_list.push_back(m);
		std::sort(tmp_list.begin(), tmp_list.end(), PMessdiener::cmp);
		num_minis++;
	}
	tmp_list.push_back((PMessdiener*) NULL);

	for (int i = 0; i < num_minis; i++) {
		wxListItem item;
		item.SetId(i);
		lv_minis->InsertItem(item);
		lv_minis->SetItem(i, 0, tmp_list.at(i)->vorname + wxT(" ") + tmp_list.at(i)->name);
	}
	wxListItem item;
	item.SetId(num_minis);
	lv_minis->InsertItem(item);
	lv_minis->SetItem(num_minis, 0, wxT("-"));

	lv_minis->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);

	//make selection
	if (m != (PMessdiener*) NULL) {
		int index = 0;
		while (tmp_list.at(index) != m) index++;
		lv_minis->Select(index, true);
	} else {
		lv_minis->Select(num_minis, true);
	}

	//set location
	wxPoint parent_point = parent->GetPosition();
	wxSize parent_size = parent->GetSize();
	wxSize own_size = GetSize();
	SetPosition(wxPoint(parent_point.x + 20, parent_point.y + parent_size.y - own_size.y - 20));

	lv_minis->Bind(wxEVT_KILL_FOCUS, &PMiniChoiceDialog::onKillFocus, this);
}

BEGIN_EVENT_TABLE(PMiniChoiceDialog, wxDialog)
EVT_LIST_ITEM_SELECTED(R::ID_LC, PMiniChoiceDialog::onLISelected)
EVT_CLOSE(PMiniChoiceDialog::onClose)
END_EVENT_TABLE()

void PMiniChoiceDialog::onKillFocus(wxFocusEvent&) {
	parent->unHighlightPMiniChoiceDialog(termin, dienst, mini);
	delete this;
}

void PMiniChoiceDialog::onClose(wxCloseEvent& evt) {
	evt.Veto();
}

void PMiniChoiceDialog::onLISelected(wxListEvent& evt) {
	int i = -1;
	for (;;) {
		i = lv_minis->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		controller->onEntryChanged(termin, dienst, mini, tmp_list.at(i));
	}
}
