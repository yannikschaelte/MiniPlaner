/* 
 * File:   ExcelXMLExport.cpp
 * Author: Yannik
 * 
 * Created on October 1, 2015, 11:01 AM
 */

#include "ExcelXMLExport.h"
#include "../R.h"

wxString ExcelXMLExport::createExcelXML(ExportLayout* layout, Planer* planer) {
	wxString page = wxT("<?xml version=\"1.0\" encoding=\"utf-8\"?>"
			"<?mso-application progid=\"Excel.Sheet\"?>"
			"<Workbook"
			" xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\""
			" xmlns:o=\"urn:schemas-microsoft-com:office:office\""
			" xmlns:x=\"urn:schemas-microsoft-com:office:excel\""
			" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\""
			" xmlns:html=\"http://www.w3.org/TR/REC-html40\">");
	page += wxT("<DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">"
			"<Author>Yannik Schälte</Author>"
			"<Version>2.0</Version>"
			"</DocumentProperties>");
	page += wxT("<Styles>"
			"<Style ss:ID=\"Default\" ss:Name=\"Normal\">"
			"<Alignment ss:Vertical=\"Bottom\" />"
			"</Style>"
			"<Style ss:ID=\"s21\">"
			"<Font x:Family=\"Swiss\" ss:Bold=\"1\" />"
			"</Style>"
			"<Style ss:ID=\"s22\">"
			"<Font x:Family=\"Swiss\" ss:Italic=\"1\" />"
			"</Style>"
			"<Style ss:ID=\"s23\">"
			"<Font x:Family=\"Swiss\" ss:Size=\"16\" ss:Bold=\"1\" />"
			"</Style>"
			"</Styles>");
	page += wxT("<Worksheet ss:Name=\"") + R::MESSDIENERPLAN + wxT("\">"
			"<Table>");

	//plan in rows and columns
	int cols = getCols(layout) - 1;

	//add title
	if (!layout->title.IsEmpty()) {
		page += wxT("<Row><Cell ss:MergeAcross=\"") + wxString::Format(wxT("%i"), cols) + wxT("\" ss:StyleID=\"s23\"><Data ss:Type=\"String\">") + layout->title + wxT("</Data></Cell></Row>");
		page += wxT("<Row></Row>");
	}

	//add termine
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
		//basics
		if (layout->modus_basics == ExportLayout::MODUS_BASICS_ABOVE) {
			page += wxT("<Row><Cell ss:MergeAcross=\"") + wxString::Format(wxT("%i"), cols) + wxT("\" ss:StyleID=\"s21\"><Data ss:Type=\"String\">") + PTermin::printBasics(*iter_t) + wxT("</Data></Cell></Row>");
			if (!(**iter_t).bem.IsEmpty()) {
				page += wxT("<Row><Cell ss:MergeAcross=\"") + wxString::Format(wxT("%i"), cols) + wxT("\"><Data ss:Type=\"String\">") + (**iter_t).bem + wxT("</Data></Cell></Row>");
			}
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					page += wxT("<Row><Cell ss:StyleID=\"s22\"><Data ss:Type=\"String\">") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</Data></Cell>");
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += wxT("<Cell><Data ss:Type=\"String\">") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</Data></Cell>");
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								page += wxT("</Row>");
								if (k != num_dienst_minis - 1) {
									page += wxT("<Row><Cell></Cell>");
								}
							}
						}
					} else {
						page += wxT("<Cell><Data ss:Type=\"String\">");
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += wxT("</Data></Cell></Row>");
					}
				}
			} else {//do not show dienste
				if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
					int col = 0;
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							if (col == 0) {
								page += wxT("<Row>");
							}
							page += wxT("<Cell><Data ss:Type=\"String\">") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</Data></Cell>");
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								page += wxT("</Row>");
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					int num_dienste = (**iter_t).list_dienst_num.size();
					if (num_dienste > 0) {
						page += wxT("<Row><Cell><Data ss:Type=\"String\">");
						for (int j = 0; j < num_dienste; j++) {
							int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
							for (int k = 0; k < num_dienst_minis; k++) {
								page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
								if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
							}
						}
						page += wxT("</Data></Cell></Row>");
					}
				}
			}
			page += wxT("<Row></Row>");
		} else {//MODUS_BASICS_LEFT
			bool bemDrawn = false;
			page += wxT("<Row><Cell ss:StyleID=\"s21\"><Data ss:Type=\"String\">") + PTermin::printBasics(*iter_t) + wxT("</Data></Cell>");
			int row = 0;
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					if (row != 0) {
						page += wxT("<Row><Cell><Data ss:Type=\"String\">");
						if (row == 1) {
							page += (**iter_t).bem;
							bemDrawn = true;
						}
						page += wxT("</Data></Cell>");
					}
					page += wxT("<Cell ss:StyleID=\"s22\"><Data ss:Type=\"String\">") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</Data></Cell>");
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += wxT("<Cell><Data ss:Type=\"String\">") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</Data></Cell>");
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								page += wxT("</Row>");
								if (k != num_dienst_minis - 1) {
									page += wxT("<Row><Cell><Data ss:Type=\"String\">");
									if (row == 0) {
										page += (**iter_t).bem;
										bemDrawn = true;
									}
									page += wxT("</Data></Cell><Cell></Cell>");
								}
								row++;
							}
						}
					} else {
						page += wxT("<Cell><Data ss:Type=\"String\">");
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += wxT("</Data></Cell></Row>");
						row++;
					}
				}
			} else {//do not show dienste
				if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
					int col = 0;
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							if (col == 0 && row != 0) {
								page += wxT("<Row><Cell><Data ss:Type=\"String\">");
								if (row == 1) {
									page += (**iter_t).bem;
									bemDrawn = true;
								}
								page += wxT("</Data></Cell>");
							}
							page += wxT("<Cell><Data ss:Type=\"String\">") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</Data></Cell>");
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								page += wxT("</Row>");
								row++;
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					page += wxT("<Cell><Data ss:Type=\"String\">");
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
						}
					}
					page += wxT("</Data></Cell>");
					if (num_dienste != 0) {
						page += wxT("</Row>");
						if (!(**iter_t).bem.IsEmpty()) {
							page += wxT("<Row><Cell><Data ss:Type=\"String\">") + (**iter_t).bem + wxT("</Data></Cell></Row>");
							bemDrawn = true;
							row++;
						}
					}
				}
			}
			if (num_dienste == 0) page += wxT("</Row>");
			if (!bemDrawn && !(**iter_t).bem.IsEmpty()) page += wxT("<Row><Cell><Data ss:Type=\"String\">") + (**iter_t).bem + wxT("</Data></Cell></Row>");
			page += wxT("<Row><Cell></Cell></Row>");
		}
	}

	page += wxT("</Table>");
	page += wxT("</Worksheet>");
	page += wxT("</Workbook>");
	return page;
}

int ExcelXMLExport::getCols(ExportLayout* layout) {
	int cols = 0;
	if (layout->modus_basics == ExportLayout::MODUS_BASICS_ABOVE) {
		if (layout->showDienste) {
			if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
				cols = 1 + layout->n;
			} else {
				cols = 2;
			}
		} else if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
			cols = layout->n;
		} else {
			cols = 1;
		}
	} else {
		if (layout->showDienste) {
			if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
				cols = 2 + layout->n;
			} else {
				cols = 3;
			}
		} else if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
			cols = 1 + layout->n;
		} else {
			cols = 2;
		}
	}
	return cols;
}