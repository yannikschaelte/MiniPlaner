#ifndef EXPORTOUTPUT_H
#define	EXPORTOUTPUT_H

#include <wx/window.h>
#include <wx/string.h>

namespace ExportOutput {
	/**
	 * Saves \a text to a file chosen by the user, or copies it to the clipboard.
	 * A \a filename ending in ".xlsx" is written as an Excel workbook (\a text is then tab-separated data);
	 * the clipboard always receives plain text, which Excel pastes as cells.
	 */
	void save(wxWindow* parent, bool toFile, const wxString& caption, const wxString& filename, const wxString& text);
}

#endif	/* EXPORTOUTPUT_H */
