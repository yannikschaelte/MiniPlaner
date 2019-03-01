/* 
 * File:   PlanerSettingsDialog.h
 * Author: Yannik
 *
 * Created on October 7, 2015, 4:16 PM
 */

#ifndef PLANERSETTINGSDIALOG_H
#define	PLANERSETTINGSDIALOG_H

#include <wx/wx.h>
#include "../model-plan/Planer.h"

class PlanerSettingsDialog : public wxDialog {
public:
	PlanerSettingsDialog(wxWindow* parent, Planer::Settings* _settings, bool* _edt);
private:
	Planer::Settings* settings;
	bool* edt;

	wxRadioButton* rb_anrechnen;
	wxRadioButton* rb_kompensieren;

	wxRadioButton* rb_alg_minimum;
	wxRadioButton* rb_alg_chrono;

	wxButton* bt_ok;
	wxButton* bt_cancel;

	DECLARE_EVENT_TABLE();
	void onBtOk(wxCommandEvent&);
	void onBtCancel(wxCommandEvent&);
};

#endif	/* PLANERSETTINGSDIALOG_H */