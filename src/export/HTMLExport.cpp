/* 
 * File:   HTMLExport.cpp
 * Author: Yannik
 * 
 * Created on October 1, 2015, 10:51 AM
 */

#include "HTMLExport.h"
#include "../R.h"

wxString HTMLExport::createHTML(ExportLayout* layout, Planer* planer, bool pv) {
	wxString page = wxT("<!DOCTYPE html>\n<html>");
	if (!pv) addHead(&page);
	page += wxT("\n	<body>\n		<table>");
	int cols = getCols(layout);

	//add title
	if (!layout->title.IsEmpty()) {
		if (pv) page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\"><h2>") + layout->title + wxT("</h2></td></tr>");
		else page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\" class=\"ptitle\">") + layout->title + wxT("</td></tr>");
	}

	//add termine
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
		//basics
		if (layout->modus_basics == ExportLayout::MODUS_BASICS_ABOVE) {
			if (pv) page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\"><b>") + PTermin::printBasics(*iter_t) + wxT("</b></td></tr>");
			else page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\" class=\"phead\">") + PTermin::printBasics(*iter_t) + wxT("</td></tr>");
			if (!(**iter_t).bem.IsEmpty()) {
				page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\">") + (**iter_t).bem + wxT("</td></tr>");
			}
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					if (pv) page += wxT("\n			<tr><td><i>") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</i></td>");
					else page += wxT("\n			<tr><td class=\"pdienst\">") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</td>");
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += wxT("<td>") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</td>");
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								for (int l = k % layout->n; l < layout->n - 1; l++) {
									page += wxT("<td></td>");
								}
								page += wxT("</tr>");
								if (k != num_dienst_minis - 1) {
									page += wxT("\n			<tr><td></td>");
								}
							}
						}
					} else {
						page += wxT("<td>");
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += wxT("</td></tr>");
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
								page += wxT("\n			<tr>");
							}
							page += wxT("<td>") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</td>");
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								for (int l = k % layout->n; l < layout->n - 1; l++) {
									page += wxT("<td></td>");
								}
								page += wxT("</tr>");
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					if (num_dienste > 0) {
						page += wxT("\n			<tr><td>");
						int num_dienste = (**iter_t).list_dienst_num.size();
						for (int j = 0; j < num_dienste; j++) {
							int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
							for (int k = 0; k < num_dienst_minis; k++) {
								page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
								if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
							}
						}
						page += wxT("</td></tr>");
					}
				}
			}
			page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\"><br/></td></tr>");
		} else {//MODUS_BASICS_LEFT
			bool bemDrawn = false;
			if (pv) page += wxT("\n			<tr><td><b>") + PTermin::printBasics(*iter_t) + wxT("</b></td>");
			else page += wxT("\n			<tr><td class=\"phead\">") + PTermin::printBasics(*iter_t) + wxT("</td>");
			int row = 0;
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					if (row != 0) {
						page += wxT("\n			<tr><td>");
						if (row == 1) {
							page += (**iter_t).bem;
							bemDrawn = true;
						}
						page += wxT("</td>");
					}
					if (pv) page += wxT("<td><i>") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</i></td>");
					else page += wxT("<td class=\"pdienst\">") + (**iter_t).list_dienst_num.at(j).first->name + wxT("</td>");
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += wxT("<td>") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</td>");
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								for (int l = k % layout->n; l < layout->n - 1; l++) {
									page += wxT("<td></td>");
								}
								page += wxT("</tr>");
								if (k != num_dienst_minis - 1) {
									page += wxT("\n			<tr><td>");
									if (row == 0) {
										page += (**iter_t).bem;
										bemDrawn = true;
									}
									page += wxT("</td><td></td>");
								}
								row++;
							}
						}
					} else {
						page += wxT("<td>");
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += wxT("</td></tr>");
						row++;
					}
				}
			} else {//do not show dienste
				if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
					int col = 0;
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							if (col == 0 && row != 0) {
								page += wxT("\n			<tr><td>");
								if (row == 1) {
									page += (**iter_t).bem;
									bemDrawn = true;
								}
								page += wxT("</td>");
							}
							page += wxT("<td>") + layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + wxT("</td>");
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								for (int l = col; l < layout->n - 1; l++) {
									page += wxT("<td></td>");
								}
								page += wxT("</tr>");
								row++;
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					page += wxT("<td>");
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
						}
					}
					page += wxT("</td>");
					if (num_dienste != 0) {
						page += wxT("</tr>");
						if (!(**iter_t).bem.IsEmpty()) {
							page += wxT("\n			<tr><td>") + (**iter_t).bem + wxT("</td></tr>");
							bemDrawn = true;
							row++;
						}
					}
				}
			}
			if (num_dienste == 0) {
				for (int l = 1; l < cols; l++) {
					page += wxT("<td></td>");
				}
				page += wxT("</tr>");
			}
			if (!bemDrawn && !(**iter_t).bem.IsEmpty()) page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\">") + (**iter_t).bem + wxT("</td></tr>");
			page += wxT("\n			<tr><td colspan=\"") + wxString::Format(wxT("%i"), cols) + wxT("\"><br/></td></tr>");
		}
	}
	page += wxT("\n		</table>\n	</body>\n</html>");
	return page;
}

void HTMLExport::addHead(wxString* page) {
	*page += wxT("\n	<head>\n		<title>") + R::MESSDIENERPLAN + wxT("</title>"
			"\n		<meta charset=\"utf-8\"/>"
			"\n		<meta name=\"description\" content=\"MiniPlaner Messdienerplan\"/>"
			"\n		<meta name=\"keywords\" content=\"MiniPlaner, Messdienerplan, Programm\"/>"
			"\n		<meta name=\"author\" content=\"Yannik Schälte\"/>"
			"\n		<style>"
			"\n		td {padding: 3px; vertical-align: top;}"
			"\n		.ptitle {font-size: x-large; font-weight: bold; padding-top:30px; padding-bottom:30px;}"
			"\n		.phead {font-weight: bold;}"
			"\n		.pdienst {font-style: italic;}"
			"\n		</style>"
			"\n	</head>");
}

int HTMLExport::getCols(ExportLayout* layout) {
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