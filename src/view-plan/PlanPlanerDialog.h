/* 
 * File:   PlanPlanerDialog.h
 * Author: Yannik
 *
 * Created on September 11, 2015, 9:38 AM
 */

#ifndef PLANPLANERDIALOG_H
#define	PLANPLANERDIALOG_H

#include <wx/wx.h>
#include <wx/snglinst.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/display.h>
#include <wx/scrolwin.h>
#include <wx/gbsizer.h>
#include <wx/event.h>
#include <wx/colour.h>
#include <wx/arrstr.h>
#include <wx/notebook.h>
#include <wx/thread.h>
#include <wx/notebook.h>
#include <wx/html/htmlwin.h>
#include <vector>
#include "../model-plan/Planer.h"
#include "../export/ExportLayout.h"
#include "PMiniChoiceDialog.h"
class PlanerController;

class PlanPlanerDialog : public wxFrame, wxThreadHelper {
public:
	PlanPlanerDialog(wxWindow* parent, Planer* planer);

	void notifyMinis();
	void notifyMGruppen();
	void notifyTermine(int index = -1);
	void notifyTGruppen();
	void notifyMaskeAndPreview();
	void notifyMaske();
	void notifyPreview();
	void notifySave(bool canSave);
	void notifyHistory(bool enabled);
	void notifyFuture(bool enabled);
	void highlightPMiniChoiceDialog(PTermin* termin, int dienst, int mini_i);
	void unHighlightPMiniChoiceDialog(PTermin* termin, int dienst, int mini_i);
	void unHighlight();
	void redrawMaske();
protected:
	virtual wxThread::ExitCode Entry();
private:
	wxSingleInstanceChecker* single_instance_checker;

	PlanerController* controller;

	std::vector<std::vector<std::vector<wxStaticText*> > > tview_choices;
	std::vector<std::vector<std::vector<wxPanel*> > > tview_pls;
	PMessdiener* tview_mini_high = NULL;
	bool continueComputation = false;
	const wxColour colour_default = *wxWHITE;
	const wxColour colour_highlight = wxColour(255, 255, 153, 255);
	const wxColour colour_selection = wxColour(255, 230, 130, 255);

	wxListView* lv_minis;
	wxListView* lv_mgruppen;
	wxListView* lv_termine;
	wxButton* bt_termine_edt;
	wxButton* bt_termine_del;
	wxListView* lv_tgruppen;

	wxNotebook* nb_termine;
	wxScrolled<wxPanel>* pl_maske;
	wxGridBagSizer* sizer_maske;
	bool maskeShown = false;
	bool maskeUpToDate = true;
	bool previewUpToDate = true;
	wxHtmlWindow* html_preview;
	ExportLayout layout;
	const static int MODUS_MASKE = 0;
	const static int MODUS_PREVIEW = 1;
	int modus = MODUS_PREVIEW;

	wxButton* bt_options;
	wxButton* bt_compute;
	wxButton* bt_stop;
	wxButton* bt_undo;
	wxButton* bt_redo;
	wxButton* bt_clear;
	wxButton* bt_save;

	wxButton* bt_settings;
	wxRadioButton* rb_file;
	wxRadioButton* rb_clipboard;
	wxButton* bt_html;
	wxButton* bt_csv;
	wxButton* bt_excel_xml;

	void initComponents();
	void initPreview();
	void initMaske();
	void highlight(PMessdiener* mini);
	
	DECLARE_EVENT_TABLE();

	void onClose(wxCloseEvent& evt);
	void onOptions(wxCommandEvent&);
	void onCompute(wxCommandEvent&);
	void onThreadDone(wxThreadEvent& evt);
	void onStop(wxCommandEvent&);
	void onUndo(wxCommandEvent&);
	void onRedo(wxCommandEvent&);
	void onClear(wxCommandEvent&);
	void onShowPMiniChoiceDialog(wxMouseEvent& evt);
	void onHighlight(wxMouseEvent& evt);
	void onMinisViewHighlight(wxListEvent& evt);
	void onSave(wxCommandEvent&);
	void onNBPageChange(wxBookCtrlEvent& evt);

	void onBtTermineEdt(wxCommandEvent&);
	void onBtTermineDel(wxCommandEvent&);
	void onLITermineActivated(wxListEvent& evt);
	void onBtLayout(wxCommandEvent&);
	void onBtHTML(wxCommandEvent&);
	void onBtCSV(wxCommandEvent&);
	void onBtExcelXML(wxCommandEvent&);
};

#endif	/* PLANPLANERDIALOG_H */