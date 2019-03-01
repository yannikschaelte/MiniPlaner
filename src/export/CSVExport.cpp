/* 
 * File:   CSVExport.cpp
 * Author: Yannik
 * 
 * Created on October 1, 2015, 11:01 AM
 */

#include "CSVExport.h"

wxString CSVExport::createCSV(ExportLayout* layout, Planer* planer) {
	wxString page = wxT("sep=") + D + N;

	//add title
	if (!layout->title.IsEmpty()) {
		page += layout->title + N + N;
	}

	//add termine
	for (std::vector<PTermin*>::iterator iter_t = planer->list_termin.begin(); iter_t != planer->list_termin.end(); iter_t++) {
		//basics
		if (layout->modus_basics == ExportLayout::MODUS_BASICS_ABOVE) {
			page += PTermin::printBasics(*iter_t) + N;
			if (!(**iter_t).bem.IsEmpty()) {
				page += (**iter_t).bem + N;
			}
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					page += (**iter_t).list_dienst_num.at(j).first->name + D;
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + D;
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								page += N;
								if (k != num_dienst_minis - 1) {
									page += D;
								}
							}
						}
						if (num_dienst_minis == 0) page += N;
					} else {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += N;
					}	
				}
			} else {//do not show dienste
				if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
					int col = 0;
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + D;
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								page += N;
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
						}
					}
					if (num_dienste != 0) page += N;
				}
			}
			page += N;
		} else {//MODUS_BASICS_LEFT
			bool bemDrawn = false;
			page += PTermin::printBasics(*iter_t) + D;
			int row = 0;
			int num_dienste = (**iter_t).list_dienst_num.size();
			if (layout->showDienste) {
				for (int j = 0; j < num_dienste; j++) {
					if (row != 0) {
						if (row == 1) {
							page += (**iter_t).bem;
							bemDrawn = true;
						}
						page += D;
					}
					page += (**iter_t).list_dienst_num.at(j).first->name + D;
					int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
					if (layout->modus_minis == ExportLayout::MODUS_MINIS_CELLS) {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + D;
							if (k == num_dienst_minis - 1 || k % layout->n == layout->n - 1) {
								page += N;
								if (k != num_dienst_minis - 1) {
									if (row == 0) {
										page += (**iter_t).bem;
										bemDrawn = true;
									}
									page += D + D;
								}
								row++;
							}
						}
						if (num_dienst_minis == 0) page += N;
					} else {
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (k != num_dienst_minis - 1) page += wxT(", ");
						}
						page += N;
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
								if (row == 1) {
									page += (**iter_t).bem;
									bemDrawn = true;
								}
								page += D;
							}
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k)) + D;
							if (col == layout->n - 1 || (j == num_dienste - 1 && k == num_dienst_minis - 1)) {
								page += N;
								row++;
							}
							col = (col + 1) % layout->n;
						}
					}
				} else {
					int num_dienste = (**iter_t).list_dienst_num.size();
					for (int j = 0; j < num_dienste; j++) {
						int num_dienst_minis = (**iter_t).list_dienst_num.at(j).second;
						for (int k = 0; k < num_dienst_minis; k++) {
							page += layout->createName((**iter_t).list_dienst_minis.at(j).second.at(k));
							if (j != num_dienste - 1 || k != num_dienst_minis - 1) page += wxT(", ");
						}
					}
					page += N;
					if (!(**iter_t).bem.IsEmpty()) {
						page += (**iter_t).bem;
						if (num_dienste != 0) page += N;
						bemDrawn = true;
						row++;
					}
				}
			}
			if (num_dienste == 0) page += N;
			if (!bemDrawn && !(**iter_t).bem.IsEmpty()) page += (**iter_t).bem + N;
			page += N;
		}
	}
	return page;
}