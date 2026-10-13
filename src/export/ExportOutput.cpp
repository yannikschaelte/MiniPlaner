#include "ExportOutput.h"
#include <wx/clipbrd.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include "XlsxExport.h"
#include "../Paths.h"
#include "../R.h"

void ExportOutput::save(wxWindow* parent, bool toFile, const wxString& caption, const wxString& filename, const wxString& text) {
	if (!toFile) {
		if (wxTheClipboard->Open()) {
			wxTheClipboard->SetData(new wxTextDataObject(text));
			wxTheClipboard->Close();
		}
		return;
	}
	wxFileDialog dialog(parent, caption, Paths::outputDir(), filename, wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dialog.ShowModal() == wxID_CANCEL) return;
	wxFileOutputStream out(dialog.GetPath());
	if (!out.IsOk()) return;
	if (filename.EndsWith(wxT(".xlsx"))) {
		XlsxExport::write(out, text, wxFileName(filename).GetName());
	} else {
		const wxScopedCharBuffer utf8 = text.ToUTF8();
		out.Write(utf8, utf8.length());
	}
}
