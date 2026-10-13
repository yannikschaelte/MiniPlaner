#include "XlsxExport.h"
#include <wx/zipstrm.h>
#include <wx/tokenzr.h>

namespace {
	wxString escape(wxString s) {
		s.Replace(wxT("&"), wxT("&amp;"));
		s.Replace(wxT("<"), wxT("&lt;"));
		s.Replace(wxT(">"), wxT("&gt;"));
		return s;
	}

	/** Excel sheet names: at most 31 characters, none of []:*?/\ */
	wxString sheetName(wxString s) {
		for (const wxUniChar c : wxString(wxT("[]:*?/\\"))) s.Replace(wxString(c), wxT(" "));
		s = s.Left(31);
		return s.IsEmpty() ? wxString(wxT("Sheet1")) : s;
	}

	/** 0-based column index to letters: 0 -> A, 26 -> AA. */
	wxString columnName(int col) {
		wxString name;
		for (col++; col > 0; col = (col - 1) / 26) name = wxUniChar('A' + (col - 1) % 26) + name;
		return name;
	}

	wxString sheetXml(const wxString& table) {
		wxString rows = table;
		wxUniChar sep = '\t';
		if (rows.StartsWith(wxT("sep="))) {
			sep = rows.Length() > 4 ? rows[4] : sep;
			rows = rows.AfterFirst('\n');
		}
		wxString xml = wxT("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
				"<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\"><sheetData>");
		wxStringTokenizer lines(rows, wxT("\n"), wxTOKEN_RET_EMPTY_ALL);
		for (int r = 1; lines.HasMoreTokens(); r++) {
			wxString line = lines.GetNextToken();
			line.Replace(wxT("\r"), wxEmptyString);
			xml += wxString::Format(wxT("<row r=\"%i\">"), r);
			wxStringTokenizer cells(line, wxString(sep), wxTOKEN_RET_EMPTY_ALL);
			for (int c = 0; cells.HasMoreTokens(); c++) {
				wxString cell = cells.GetNextToken();
				if (cell.IsEmpty()) continue;
				xml += wxString::Format(wxT("<c r=\"%s%i\" t=\"inlineStr\"><is><t xml:space=\"preserve\">"), columnName(c), r)
						+ escape(cell) + wxT("</t></is></c>");
			}
			xml += wxT("</row>");
		}
		return xml + wxT("</sheetData></worksheet>");
	}

	void add(wxZipOutputStream& zip, const wxString& name, const wxString& content) {
		zip.PutNextEntry(name);
		const wxScopedCharBuffer utf8 = content.ToUTF8();
		zip.Write(utf8, utf8.length());
	}
}

bool XlsxExport::write(wxOutputStream& out, const wxString& table, const wxString& sheet) {
	const wxString header = wxT("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>");
	const wxString relNs = wxT("http://schemas.openxmlformats.org/package/2006/relationships");
	const wxString docRel = wxT("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
	wxZipOutputStream zip(out);
	add(zip, wxT("[Content_Types].xml"), header +
			wxT("<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
			"<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
			"<Default Extension=\"xml\" ContentType=\"application/xml\"/>"
			"<Override PartName=\"/xl/workbook.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>"
			"<Override PartName=\"/xl/worksheets/sheet1.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>"
			"</Types>"));
	add(zip, wxT("_rels/.rels"), header + wxT("<Relationships xmlns=\"") + relNs + wxT("\">"
			"<Relationship Id=\"rId1\" Type=\"") + docRel + wxT("/officeDocument\" Target=\"xl/workbook.xml\"/></Relationships>"));
	add(zip, wxT("xl/workbook.xml"), header + wxT("<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"")
			+ docRel + wxT("\"><sheets><sheet name=\"") + escape(sheetName(sheet)) + wxT("\" sheetId=\"1\" r:id=\"rId1\"/></sheets></workbook>"));
	add(zip, wxT("xl/_rels/workbook.xml.rels"), header + wxT("<Relationships xmlns=\"") + relNs + wxT("\">"
			"<Relationship Id=\"rId1\" Type=\"") + docRel + wxT("/worksheet\" Target=\"worksheets/sheet1.xml\"/></Relationships>"));
	add(zip, wxT("xl/worksheets/sheet1.xml"), sheetXml(table));
	return zip.Close();
}
