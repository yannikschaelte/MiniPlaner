/* 
 * File:   UpdateChecker.h
 * Author: Yannik
 *
 * Created on October 12, 2015, 12:22 PM
 */

#ifndef UPDATECHECKER_H
#define	UPDATECHECKER_H

#include <wx/wx.h>
#include <wx/url.h>

namespace UpdateChecker {
	void checkUpdate(wxWindow* parent);
	
	class UpdateDialog : public wxDialog {
	public:
		UpdateDialog(wxWindow* parent);
	private:
		wxButton* bt_download;
		wxButton* bt_ok;
		DECLARE_EVENT_TABLE();
		void onBtOk(wxCommandEvent&);
		void onBtDownload(wxCommandEvent&);
	};
}

#endif	/* UPDATECHECKER_H */

