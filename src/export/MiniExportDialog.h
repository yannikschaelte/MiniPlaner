/* 
 * File:   MiniExportDialog.h
 * Author: Yannik
 *
 * Created on October 2, 2015, 7:46 PM
 */

#ifndef MINIEXPORTDIALOG_H
#define	MINIEXPORTDIALOG_H

#include <wx/wx.h>
#include <vector>
#include "../R.h"
#include "../model-data/Messdiener.h"
#include "../file/DataFileHandler.h"

class MiniExportDialog : public wxDialog {
public:
	MiniExportDialog(wxWindow* parent, std::vector<Messdiener*>* _list_mini);
private:
	const wxString D = DataFileHandler::D;
	const wxString N = wxT("\n");
	std::vector<Messdiener*>* list_mini;
	wxRadioButton* rb_file;
	wxRadioButton* rb_clipboard;
	wxCheckBox* cb_num;
	wxCheckBox* cb_cols[R::MINI_ATTS_NUM];
	
	wxButton* bt_html;
	wxButton* bt_csv;
	wxButton* bt_excel_xml;

	wxString createHTML();
	wxString createCSV();
	wxString createExcelXML();
	DECLARE_EVENT_TABLE();
	void onBtHTML(wxCommandEvent&);
	void onBtCSV(wxCommandEvent&);
	void onBtExcelXML(wxCommandEvent&);
};

#endif	/* MINIEXPORTDIALOG_H */

