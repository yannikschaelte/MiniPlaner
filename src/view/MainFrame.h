/* 
 * File:   MainFrame.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:00 PM
 */

#ifndef MAINFRAME_H
#define	MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include "../view-data/DienstePanel.h"
#include "../view-data/MinisPanel.h"
#include "../view-data/TerminePanel.h"
#include "../view-data/MGruppenPanel.h"
#include "../view-data/TGruppenPanel.h"
#include "../view-data/FehlzeitenPanel.h"
#include "../view-plan/PlaenePanel.h"
#include "AboutPanel.h"
class App;

class MainFrame : public wxFrame {
public:
	MainFrame(App* _app);
	void notifyDienste(int index = -1);
	void notifyMinis(int index = -1);
	void notifyEinzeltermine(int index = -1);
	void notifySerientermine(int index = -1);
	void notifyMGruppen(int index = -1);
	void notifyTGruppen(int index = -1);
	void notifyFehlzeiten(int index = -1);
	void notifyPlaene(int index = -1);
private:
	void loadGUISettings();
	void saveGUISettings();
	virtual void OnClose(wxCloseEvent&);
	
	wxBoxSizer* sizer_r;
	wxPanel* pl_tabs;
	std::vector<std::pair<wxPanel*, wxStaticText*> > list_tabs;
	std::vector<wxPanel*> list_pls;
	int sel;
	
	App* app;
	DienstePanel* dienste_panel;
	MinisPanel* minis_panel;
	TerminePanel* termine_panel;
	MGruppenPanel* m_gruppen_panel;
	TGruppenPanel* t_gruppen_panel;
	FehlzeitenPanel* fehlzeiten_panel;
	PlaenePanel* plaene_panel;
	AboutPanel* about_panel;
	DECLARE_EVENT_TABLE();
	void onLBSel(wxMouseEvent& evt);
	void handleLBSel(int index);
};

#endif	/* MAINFRAME_H */