/* 
 * File:   PlaenePanel.cpp
 * Author: Yannik
 * 
 * Created on August 25, 2015, 12:40 PM
 */

#include "PlaenePanel.h"
#include <wx/snglinst.h>
#include "../R.h"
#include "../App.h"
#include "TerminePlanerDialog.h"
#include "../Util.h"
#include "../view-data/DeleteDialog.h"
#include "../export/PlanerMiniInterfaceDialog.h"

PlaenePanel::PlaenePanel(wxWindow* parent, App* _app)
: wxPanel(parent, R::ID_ANY) {
	app = _app;
	sizer = new wxBoxSizer(wxHORIZONTAL);
	lv_plaene = new wxListView(this, R::ID_LC, wxDefaultPosition, wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem cols[2];
	cols[0].SetText(wxT(""));
	cols[1].SetText(R::ZEITRAUM);
	lv_plaene->InsertColumn(0, cols[0]);
	lv_plaene->InsertColumn(1, cols[1]);
	notifyPlaene();
	sizer->Add(lv_plaene, 1, wxEXPAND, 0);

	sizer_r = new wxBoxSizer(wxVERTICAL);
	bt_add = new wxButton(this, R::ID_BT_ADD, R::ADD);
	sizer_r->Add(bt_add, 0, 0, 0);
	bt_edt = new wxButton(this, R::ID_BT_EDT, R::OEFFNEN);
	sizer_r->Add(bt_edt, 0, 0, 0);
	bt_del = new wxButton(this, R::ID_BT_DEL, R::DEL);
	sizer_r->Add(bt_del, 0, 0, 0);
	sizer_r->Add(new wxPanel(this), 1, wxEXPAND, 0);
	bt_extras = new wxButton(this, R::ID_BT_COMPUTE, R::EXTRAS);
	sizer_r->Add(bt_extras, 0, 0, 0);
	sizer->Add(sizer_r, 0, wxEXPAND, 0);
	
	SetSizer(sizer);
}

void PlaenePanel::notifyPlaene(int index) {
	lv_plaene->DeleteAllItems();
	int num = app->list_planer.size();
	for (int i = 0; i < num; i++) {
		wxListItem item;
		item.SetId(i);
		lv_plaene->InsertItem(item);
		lv_plaene->SetItem(i, 0, wxString::Format(wxT("%i"), i + 1));
		lv_plaene->SetItem(i, 1, app->list_planer.at(i).printShort());
	}
	if (index != -1) lv_plaene->Select(index, true);
	lv_plaene->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
	lv_plaene->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

BEGIN_EVENT_TABLE(PlaenePanel, wxPanel)
EVT_BUTTON(R::ID_BT_ADD, PlaenePanel::onBtAdd)
EVT_BUTTON(R::ID_BT_DEL, PlaenePanel::onBtDel)
EVT_BUTTON(R::ID_BT_EDT, PlaenePanel::onBtEdt)
EVT_LIST_ITEM_ACTIVATED(R::ID_LC, PlaenePanel::onLIActivated)
EVT_LIST_KEY_DOWN(R::ID_LC, PlaenePanel::onLIKey)
EVT_BUTTON(R::ID_BT_COMPUTE, PlaenePanel::onBtExtras)
END_EVENT_TABLE()

void PlaenePanel::onBtAdd(wxCommandEvent&) {
	wxDateTime datum_beginn;
	wxDateTime datum_ende;
	std::vector<Dienst*> list_dienst;
	std::vector<PTermin*> list_termin;
	std::vector<PMessdiener*> list_mini;
	std::vector<PMGruppe*> list_mgruppe;
	std::vector<PFehlzeit*> list_fehlzeit;
	bool edt = false;
	TerminePlanerDialog* dialog = new TerminePlanerDialog(this, app, &edt, &datum_beginn, &datum_ende, &list_dienst, &list_termin, &list_mini, &list_mgruppe, &list_fehlzeit);
	dialog->ShowModal();
	delete dialog;
	if (edt) {
		app->createAndOpenPlanPlaner(datum_beginn, datum_ende, list_dienst, list_termin, list_mini, list_mgruppe, list_fehlzeit);
	}
}

void PlaenePanel::onBtEdt(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_plaene->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		app->edtPlanPlaner(i);
		break;
	}
}

void PlaenePanel::onBtDel(wxCommandEvent&) {
	int i = -1;
	for (;;) {
		i = lv_plaene->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (i == -1) {
			break;
		}
		//check if the corresponding window is opened
		wxSingleInstanceChecker* single_instance_checker = new wxSingleInstanceChecker;
		single_instance_checker->Create(app->list_planer.at(i).getDir());
		if (!single_instance_checker->IsAnotherRunning()) {
			//make sure decision and delete
			bool del = false;
			DeleteDialog dialog(this, &del);
			dialog.ShowModal();
			if (del) app->delPlanPlaner(i);
		}
		delete single_instance_checker;
		single_instance_checker = 0;
		break;
	}
}

void PlaenePanel::onLIActivated(wxListEvent& evt) {
	app->edtPlanPlaner(evt.GetItem().GetId());
}

void PlaenePanel::onLIKey(wxListEvent& evt) {
	if (evt.GetKeyCode() == WXK_DELETE) {
		int i = -1;
		for (;;) {
			i = lv_plaene->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (i == -1) {
				break;
			}
			//check if the corresponding window is opened
			wxSingleInstanceChecker* single_instance_checker = new wxSingleInstanceChecker;
			single_instance_checker->Create(app->list_planer.at(i).getDir());
			if (!single_instance_checker->IsAnotherRunning()) {
				//make sure decision and delete
				bool del = false;
				DeleteDialog dialog(this, &del);
				dialog.ShowModal();
				if (del) app->delPlanPlaner(i);
			}
			delete single_instance_checker;
			single_instance_checker = 0;
			break;
		}
	}
}

void PlaenePanel::onBtExtras(wxCommandEvent&) {
	wxDateTime datum_beginn;
	wxDateTime datum_ende;
	std::vector<Dienst*> list_dienst;
	std::vector<PTermin*> list_termin;
	std::vector<PMessdiener*> list_mini;
	std::vector<PMGruppe*> list_mgruppe;
	std::vector<PFehlzeit*> list_fehlzeit;
	bool edt = false;
	PlanerMiniInterfaceDialog* dialog = new PlanerMiniInterfaceDialog(this, app, &edt, &datum_beginn, &datum_ende, &list_dienst, &list_termin, &list_mini, &list_mgruppe, &list_fehlzeit);
	dialog->ShowModal();
	delete dialog;
	if (edt) {
		app->createAndOpenPlanPlaner(datum_beginn, datum_ende, list_dienst, list_termin, list_mini, list_mgruppe, list_fehlzeit);
	}
}