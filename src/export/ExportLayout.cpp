#include "ExportLayout.h"

wxString ExportLayout::createName(PMessdiener* mini) {
	if(mini == NULL) return wxT("-");
	switch (modus_namen) {
		case MODUS_NAMEN_VORNAME_N:
			return mini->vorname + wxT(" ") + mini->name.Mid(0, 1) + wxT(".");
		case MODUS_NAMEN_VORNAME_NACHNAME:
			return mini->vorname + wxT(" ") + mini->name;
		case MODUS_NAMEN_V_NACHNAME:
			return mini->vorname.Mid(0, 1) + wxT(". ") + mini->name;
		default:
			return mini->vorname;
	}
}
