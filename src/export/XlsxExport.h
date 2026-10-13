#ifndef XLSXEXPORT_H
#define	XLSXEXPORT_H

#include <wx/stream.h>
#include <wx/string.h>

namespace XlsxExport {
	/**
	 * Writes a minimal single-sheet .xlsx workbook.
	 * \a table is delimited text as produced by the CSV exports: optional "sep=X" first line, one row per line.
	 */
	bool write(wxOutputStream& out, const wxString& table, const wxString& sheet);
}

#endif	/* XLSXEXPORT_H */
