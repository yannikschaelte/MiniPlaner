#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <wx/wx.h>

/** Language selection and management of the user data (demo data, reset). */
class SettingsPanel : public wxPanel {
public:
	SettingsPanel(wxWindow* parent);
private:
	/** Run a data operation after confirmation, then close so the data is reloaded on restart. */
	void changeData(const wxString& question, void (*operation)());
	void onLanguage(wxCommandEvent& evt);
};

#endif /* SETTINGSPANEL_H */
