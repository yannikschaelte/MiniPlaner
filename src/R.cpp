/* 
 * File:   R.cpp
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:18 PM
 */

#include "R.h"

//Allgemein
wxString R::MINI_PLANER = wxT("MiniPlaner");
wxString R::DIENST_DIALOG = wxT("Dienst-Dialog");
wxString R::MINI_DIALOG = wxT("Mini-Dialog");
wxString R::EINZELTERMIN_DIALOG = wxT("Einzeltermin-Dialog");
wxString R::SERIENTERMIN_DIALOG = wxT("Serientermin-Dialog");
wxString R::TERMIN_DIENST_DIALOG = wxT("Termin-Dienst-Dialog");
wxString R::MGRUPPE_DIALOG = wxT("Minigruppe-Dialog");
wxString R::TGRUPPE_DIALOG = wxT("Terminverbund-Dialog");
wxString R::FEHLZEIT_DIALOG = wxT("Fehlzeit-Dialog");
wxString R::PLAN_DIALOG = wxT("Planer");
wxString R::TERMIN_DIALOG = wxT("Termin-Dialog");
wxString R::EXPORT_LAYOUT_DIALOG = wxT("Export-Layout-Dialog");
wxString R::MINI_EXPORT_DIALOG = wxT("Mini-Export-Dialog");
wxString R::MINI_IMPORT_DIALOG = wxT("Mini-Import-Dialog");
wxString R::MINI_EXTRAS_DIALOG = wxT("Mini-Extras-Dialog");
wxString R::EINZELTERMIN_IMPORT_DIALOG = wxT("Einzeltermin-Import-Dialog");
wxString R::SPEICHERN_DIALOG = wxT("");
wxString R::LOESCHEN_DIALOG = wxT("");
wxString R::PLANER_SETTINGS_DIALOG = wxT("Algorithmus-Einstellungen-Dialog");

wxString R::HILFE = wxT("Hilfe");
wxString R::UEBER = wxT("Über");
wxString R::SPRACHE = wxT("Sprache der Benutzeroberfläche");
wxString R::KONTAKT_MSG = wxT("Bei Fragen, Programmfehlern, Problemen oder Ideen dürfen Sie sich jederzeit gern melden.");
wxString R::EXTRAS = wxT("Extras");
wxString R::SEMIKOLON = wxT("Semikolon");
wxString R::KOMMA = wxT("Komma");
wxString R::LEERZEICHEN = wxT("Leerzeichen");
wxString R::ANDERES = wxT("Anderes: ");

wxString R::OK = wxT("OK");
wxString R::CANCEL = wxT("Abbrechen");
wxString R::ADD = wxT("Neu");
wxString R::DEL = wxT("Entfernen");
wxString R::EDT = wxT("Ändern");
wxString R::JA = wxT("Ja");
wxString R::NEIN = wxT("Nein");

wxString R::DIENSTE = wxT("Dienste");
wxString R::MINI = wxT("Mini");
wxString R::MINIS = wxT("Minis");
wxString R::MGRUPPEN = wxT("M.-Gruppen");
wxString R::TERMINE = wxT("Termine");
wxString R::TGRUPPEN = wxT("T.-Verbünde");
wxString R::FEHLZEITEN = wxT("Fehlzeiten");
wxString R::PLAENE = wxT("Pläne");
//Adresse
wxString R::STRASSE_NR = wxT("Straße Nr.");
wxString R::PLZ_ORT = wxT("PLZ Ort");
wxString R::TEL = wxT("Telefon");
wxString R::MOBILE = wxT("Mobil");
wxString R::EMAIL = wxT("E-Mail");
//Messdiener
wxString R::NAME = wxT("Name");
wxString R::NACHNAME = wxT("Nachname");
wxString R::VORNAME = wxT("Vorname");
wxString R::GEBURTSTAG = wxT("Geburtsdatum");
wxString R::BEM = wxT("Bem.");
wxString R::MINI_ATTS[] = {R::NACHNAME, R::VORNAME, R::DIENSTE, R::GEBURTSTAG, R::STRASSE_NR, R::PLZ_ORT, R::TEL, R::MOBILE, R::EMAIL, R::BEM};
//Termine
wxString R::EINZELTERMINE = wxT("Einzeltermine");
wxString R::SERIENTERMINE = wxT("Serientermine");
wxString R::ANZAHL = wxT("Anzahl");
wxString R::ORT = wxT("Ort");
wxString R::DATUM = wxT("Datum");
wxString R::ZEIT = wxT("Zeit");
wxString R::MODUS = wxT("Modus");
wxString R::DATUM_BEGINN = wxT("Anfangsdatum (inkl.)");
wxString R::DATUM_ENDE = wxT("Enddatum (inkl.)");
wxString R::TEINZEL_ATTS[] = {NAME, ORT, DATUM, ZEIT, DIENSTE, BEM};
wxString R::TSERIE_ATTS[] = {NAME, ORT, MODUS, ZEIT, DIENSTE, DATUM_BEGINN, DATUM_ENDE, BEM};

wxString R::SONNTAG = wxT("So.");
wxString R::MONTAG = wxT("Mo.");
wxString R::DIENSTAG = wxT("Di.");
wxString R::MITTWOCH = wxT("Mi.");
wxString R::DONNERSTAG = wxT("Do.");
wxString R::FREITAG = wxT("Fr.");
wxString R::SAMSTAG = wxT("Sa.");
wxString R::WOCHENTAGE[] = {SONNTAG, MONTAG, DIENSTAG, MITTWOCH, DONNERSTAG, FREITAG, SAMSTAG};
//Modus
wxString R::TAEGLICH = wxT("täglich");
wxString R::WOECHENTLICH = wxT("wöchentlich");
wxString R::GERADE_KW = wxT("in geraden KWs");
wxString R::UNGERADE_KW = wxT("in ungeraden KWs");
wxString R::N_WOECHENTLICH = wxT("[n]-wöchentlich ab (inkl.) der Woche nach [Anfangsdatum]");
wxString R::W_IM_MONAT = wxT("[n-ter] [Wochentag] im Monat");
wxString R::MONATLICH = wxT("monatlich");
wxString R::TMODI[] = {TAEGLICH, WOECHENTLICH, GERADE_KW, UNGERADE_KW, N_WOECHENTLICH, W_IM_MONAT, MONATLICH};
wxString R::LETZTER = wxT("letzter");
wxString R::VORLETZTER = wxT("vorletzter");
wxString R::WOCHENTAG = wxT("Wochentag");
wxString R::TAG = wxT("Tag");
wxString R::DATUM_AB = wxT("Anfangsdatum (inkl.)");
wxString R::DATUM_BIS = wxT("Enddatum (inkl.)");
//Gruppen
wxString R::GRUPPE = wxT("Gruppe");
wxString R::RESTLISTE = wxT("restliche Minis");
wxString R::BEV_GEM = wxT("vorzugsweise gemeinsam");
wxString R::NUR_GEM = wxT("ausschließlich gemeinsam");
wxString R::MGMODI[] = {BEV_GEM, NUR_GEM};
wxString R::RESTTERMINE = wxT("restliche Termine");
wxString R::TGRUPPE = wxT("Verbund");
wxString R::PERIODISCH = wxT("wöchentlich: 7-Tage-Periode, beginnend ab (inkl.) ");
wxString R::NICHT_PERIODISCH = wxT("nicht-periodisch");
wxString R::TGMODI[] = {PERIODISCH, NICHT_PERIODISCH};
//Dienste
wxString R::DIENST = wxT("Dienst");
wxString R::ALLGEMEIN = wxT("Normal");
//Fehlzeiten
wxString R::FEHLZEIT = wxT("Fehlzeit");
wxString R::ZEITRAUM = wxT("Zeitraum");
wxString R::TERMIN = wxT("Termin");
wxString R::FEHLZEIT_MODI[] = {ZEITRAUM, WOCHENTAG, TERMIN};
wxString R::VON = wxT("von");
wxString R::BIS = wxT("bis");
//Pläne
wxString R::OEFFNEN = wxT("Öffnen");
wxString R::ZURUECK = wxT("Zurück");
wxString R::WEITER = wxT("Weiter");
wxString R::EINSAETZE = wxT("Einsätze");
wxString R::MASKE = wxT("Eingabemaske");
wxString R::AUTOMATISCH = wxT("Automatisch");
wxString R::STOPPEN = wxT("Stoppen");
wxString R::LEEREN = wxT("Leeren");
wxString R::EXPORT = wxT("Export");
wxString R::SPEICHERN = wxT("Speichern");
wxString R::DATEN = wxT("Daten");
wxString R::EINSTELLUNGEN = wxT("Einstellungen");
wxString R::FEHLZEITEN_ANRECHNEN = wxT("Fehl-Zeiträume werden intern bei Einsatzhäufigkeiten anteilig angerechnet");
wxString R::FEHLZEITEN_KOMPENSIEREN = wxT("Fehl-Zeiträume werden zu einer anderen Zeit kompensiert, falls möglich");
wxString R::ALG_MINIMUM = wxT("Algorithmus 1 (mit erweiterter Minimumssuche, evtl. schneller)");
wxString R::ALG_CHRONO = wxT("Algorithmus 2 (evtl. gleichmäßigere Abstände zwischen Einsätzen)");
//Export
wxString R::MESSDIENERPLAN = wxT("Ministrantenplan");
wxString R::MESSDIENERPLAN_SH = R::MESSDIENERPLAN;
wxString R::LAYOUT = wxT("Layout");
wxString R::VORSCHAU = wxT("Vorschau");
wxString R::MINIS_LAYOUT = wxT("Anordnung Minis");
wxString R::MINIS_LAYOUT_MODI[] = {wxT("in [n] Spalten"), wxT("kommasepariert")};
wxString R::BASICS_LAYOUT = wxT("Position Terminbeschreibung");
wxString R::BASICS_LAYOUT_MODI[] = {wxT("links"), wxT("oben")};
wxString R::NAMEN_LAYOUT = wxT("Format Namen");
wxString R::NAMEN_LAYOUT_MODI[] = {wxT("Vorname Nachname"), wxT("V. Nachname"), wxT("Vorname N."), wxT("Vorname")};
wxString R::DATEI_AUSGABE = wxT("Als Datei speichern");
wxString R::CLIPBOARD_AUSGABE = wxT("In Zwischenablage kopieren");
wxString R::TITEL = wxT("Überschrift");
wxString R::DIENSTE_ZEIGEN = wxT("Unterteilung nach Diensten");
wxString R::SPEICHERN_HTML = wxT("Im HTML-Format speichern");
wxString R::SPEICHERN_CSV = wxT("Im Tab-separierten CSV-Format speichern");
wxString R::SPEICHERN_EXCEL_XML = wxT("Im Excel-XML-Format speichern");
wxString R::SPALTEN = wxT("Spalten");
wxString R::NUM = wxT("Nr.");
wxString R::MESSDIENERLISTE = wxT("Ministrantenliste");
wxString R::MESSDIENERLISTE_SH = R::MESSDIENERLISTE;
//Import
wxString R::IMPORT = wxT("Import");
wxString R::IMPORTIEREN = wxT("Importieren");
wxString R::SEPARATOR = wxT("Separator");
wxString R::CSV_DATEI_WAEHLEN = wxT("CSV-Datei wählen");
wxString R::MINI_CSV_MSG = wxT("Die Zeilen der CSV-Datei werden von links nach rechts in folgendem Format ausgewertet:");
wxString R::MINI_IMPORT_MSG = wxT("Es werden nur Minis importiert, die über die Kennung Nachname+Vorname noch nicht in der\n"
		"bisherigen Liste enthalten sind.");
wxString R::EINZELTERMIN_CSV_MSG = wxT("Die Zeilen der CSV-Datei werden von links nach rechts in folgendem ");
wxString R::EINZELTERMIN_IMPORT_MSG = wxT("Es werden nur Termine importiert, die über die Kennung Ort+Datum+Zeit noch nicht in der\n"
		"bisherigen Liste enthalten sind.");
//Extras
wxString R::EMAILS = wxT("E-Mails");
wxString R::KOPIERTEMAILS = wxT("kopiert vorhandene E-Mail-Adressen Semikolon-separiert in Zwischenablage");
wxString R::ADRESSEN = wxT("Adressen");
wxString R::KOPIERTADRESSEN = wxT("kopiert Liste aller vorhandenen Adressen formatiert in Zwischenablage");
wxString R::KOPIERTEMAILSFERTIG = wxT("Email-Adressen in Zwischenablage kopiert!");
wxString R::KOPIERTADRESSENFERTIG = wxT("Adressen in Zwischenablage kopiert!");
wxString R::KOPIERTWARNICHTMOEGLICH = wxT("\nBei folgenden Minis war dies nicht möglich:\n");
//Über
wxString R::HEADLINE = wxT("ein Programm zum effizienten Erstellen hochwertiger Ministrantenpläne");
wxString R::AUTOR = wxT("Autor: ");
wxString R::KOMPILIERTMIT = wxT("Kompiliert mit: ");
wxString R::BIBLIOTHEKEN = wxT("Bibliotheken: ");
wxString R::INSTALLATIONSVERZEICHNIS = wxT("Installationsverzeichnis: ");
//Einstellungen
wxString R::MSG_LANG_CHANGE_DE = wxT("(Änderung erst bei Programm-Neustart wirksam)");
wxString R::MSG_LANG_CHANGE_EN = wxT("(Change only visible after program restart)");
//Nachrichten
wxString R::MSG_MINI_UNIQUE = wxT("Ein Mini muss über Name+Vorname eindeutig identifizierbar sein.");
wxString R::MSG_FEHLZEIT_UNIQUE = wxT("Diese Fehlzeit existiert bereits.");
wxString R::MSG_TIME_ERR = wxT("Bitte eine gültige Zeit im Format hh:mm angeben.");
wxString R::MSG_TIME_BEGINN_ERR = wxT("Bitte eine gültige Anfangszeit im Format hh:mm angeben.");
wxString R::MSG_TIME_ENDE_ERR = wxT("Bitte eine gültige Endzeit im Format hh:mm angeben.");
wxString R::MSG_WEEK_NUM_ERR = wxT("Bitte eine gültige Anzahl Wochen [n] angeben.");
wxString R::MSG_WEEK_COUNT_START = wxT("Bitte ein Anfangsdatum angeben, ab dem die Zählung der Wochen erfolgen soll (erster Termin ist an erstem passendem Wochentag ab [") + DATUM_BEGINN + wxT("]).");
wxString R::MSG_GROUP_NUM = wxT("Eine Gruppe sollte mindestens 2 Mitglieder haben.");
wxString R::MSG_TGROUP_NUM = wxT("Ein Verbund sollte mindestens 2 Mitglieder haben.");
wxString R::MSG_EINZEL_UNIQUE = wxT("Ein Einzeltermin muss über Ort, Datum und Zeit eindeutig identifizierbar sein.");
wxString R::MSG_SERIE_UNIQUE = wxT("Ein Serientermin muss über Ort, Zeit, Modus, Anfangs- und Enddatum eindeutig identifizierbar sein.");
wxString R::MSG_DIENST_UNIQUE = wxT("Ein Dienst muss eine eindeutige Bezeichnung haben.");
wxString R::MSG_MINI_SEL_ERR = wxT("Bitte wählen Sie einen Mini aus.");
wxString R::MSG_TERMIN_SEL_ERR = wxT("Bitte wählen Sie einen Termin aus.");
wxString R::MSG_DIENST_SEL_ERR = wxT("Bitte wählen Sie einen Dienst aus.");
wxString R::MSG_DATUM_ORDER = wxT("Das Enddatum liegt vor dem Anfangsdatum.");
wxString R::MSG_PLAN_CREATE_IMPOSSIBLE = wxT("Zu diesen Vorgaben kann leider definitiv kein Plan erstellt werden.");
wxString R::MSG_MANUAL_NOT_OPENED = wxT("Es konnte kein Programm gefunden werden, um das PDF-Handbuch unter MiniPlaner/help/Handbuch.pdf zu öffnen.");
wxString R::MSG_FILE_NOT_FOUND = wxT("Die Datei konnte nicht gefunden werden.");
wxString R::MSG_RETRIEVE_NOT_POSSIBLE = wxT("Die folgenden Einträge konnten nicht eingelesen werden");
wxString R::MSG_IMPORT_NOT_POSSIBLE = wxT("Die folgenden Einträge wurden nicht importiert, da sie bereits vorhanden sind:");
wxString R::Q_SPEICHERN = wxT("Änderungen speichern?");
wxString R::Q_LOESCHEN = wxT("Entfernen?");

void R::setLangDE() {
	//default
}

void R::setLangEN() {
	//Allgemein
	R::MINI_PLANER = wxT("MiniPlaner");
	R::DIENST_DIALOG = wxT("Ministry Dialog");
	R::MINI_DIALOG = wxT("Volunteer Dialog");
	R::EINZELTERMIN_DIALOG = wxT("Single Mass Dialog");
	R::SERIENTERMIN_DIALOG = wxT("Regular Mass Dialog");
	R::TERMIN_DIENST_DIALOG = wxT("Mass-Ministry Dialog");
	R::MGRUPPE_DIALOG = wxT("Volunteer Group Dialog");
	R::TGRUPPE_DIALOG = wxT("Mass Collection Dialog");
	R::FEHLZEIT_DIALOG = wxT("Absence Time Dialog");
	R::PLAN_DIALOG = wxT("Planner");
	R::TERMIN_DIALOG = wxT("Mass Dialog");
	R::EXPORT_LAYOUT_DIALOG = wxT("Export Layout Dialog");
	R::MINI_EXPORT_DIALOG = wxT("Volunteer Export Dialog");
	R::MINI_IMPORT_DIALOG = wxT("Volunteer Import Dialog");
	R::MINI_EXTRAS_DIALOG = wxT("Volunteer Extras Dialog");
	R::SPEICHERN_DIALOG = wxT("");
	R::LOESCHEN_DIALOG = wxT("");
	R::PLANER_SETTINGS_DIALOG = wxT("Algorithm Settings Dialog");

	R::HILFE = wxT("Help");
	R::UEBER = wxT("About");
	R::SPRACHE = wxT("Interface Language");
	R::KONTAKT_MSG = wxT("If you have questions, problems or remarks, please contact me.");
	R::SEMIKOLON = wxT("Semicolon");
	R::KOMMA = wxT("Comma");
	R::LEERZEICHEN = wxT("Space");
	R::ANDERES = wxT("Other: ");

	R::OK = wxT("OK");
	R::CANCEL = wxT("Cancel");
	R::ADD = wxT("New");
	R::DEL = wxT("Delete");
	R::EDT = wxT("Edit");
	R::JA = wxT("Yes");
	R::NEIN = wxT("No");

	R::DIENSTE = wxT("Ministries");
	R::MINI = wxT("Volunteer");
	R::MINIS = wxT("Volunteers");
	R::MGRUPPEN = wxT("Volunteer Groups");
	R::TERMINE = wxT("Masses");
	R::TGRUPPEN = wxT("Mass Collections");
	R::FEHLZEITEN = wxT("Absence Times");
	R::PLAENE = wxT("Plans");
	//Adresse
	R::STRASSE_NR = wxT("Street No.");
	R::PLZ_ORT = wxT("ZIP City");
	R::TEL = wxT("Telephone");
	R::MOBILE = wxT("Mobile");
	R::EMAIL = wxT("E-Mail");
	//Messdiener
	R::NAME = wxT("Name");
	R::NACHNAME = wxT("Surname");
	R::VORNAME = wxT("First Name");
	R::GEBURTSTAG = wxT("Birth Date");
	R::BEM = wxT("Remark");
	wxString mini_atts[] = {R::NACHNAME, R::VORNAME, R::DIENSTE, R::GEBURTSTAG, R::STRASSE_NR, R::PLZ_ORT, R::TEL, R::MOBILE, R::EMAIL, R::BEM};
	for (int i = 0; i < R::MINI_ATTS_NUM; i++) {
		R::MINI_ATTS[i] = mini_atts[i];
	}
	//Termine
	R::EINZELTERMINE = wxT("Single Masses");
	R::SERIENTERMINE = wxT("Regular Masses");
	R::ANZAHL = wxT("Amount");
	R::ORT = wxT("Place");
	R::DATUM = wxT("Date");
	R::ZEIT = wxT("Time");
	R::MODUS = wxT("Mode");
	R::DATUM_BEGINN = wxT("Beginning date (incl.)");
	R::DATUM_ENDE = wxT("End date (incl.)");
	wxString teinzel_atts[] = {R::NAME, R::ORT, R::DATUM, R::ZEIT, R::DIENSTE, R::BEM};
	for (int i = 0; i < R::TEINZEL_NUM; i++) {
		R::TEINZEL_ATTS[i] = teinzel_atts[i];
	}
	wxString tserie_atts[] = {R::NAME, R::ORT, R::MODUS, R::ZEIT, R::DIENSTE, R::DATUM_BEGINN, R::DATUM_ENDE, R::BEM};
	for (int i = 0; i < R::TSERIE_NUM; i++) {
		R::TSERIE_ATTS[i] = tserie_atts[i];
	}
	R::SONNTAG = wxT("Su.");
	R::MONTAG = wxT("Mo.");
	R::DIENSTAG = wxT("Tu.");
	R::MITTWOCH = wxT("We.");
	R::DONNERSTAG = wxT("Th.");
	R::FREITAG = wxT("Fr.");
	R::SAMSTAG = wxT("Sa.");
	wxString wochentage[] = {R::SONNTAG, R::MONTAG, R::DIENSTAG, R::MITTWOCH, R::DONNERSTAG, R::FREITAG, R::SAMSTAG};
	for (int i = 0; i < 7; i++) {
		R::WOCHENTAGE[i] = wochentage[i];
	}
	//Modus
	R::TAEGLICH = wxT("daily");
	R::WOECHENTLICH = wxT("weekly");
	R::GERADE_KW = wxT("in even weeks");
	R::UNGERADE_KW = wxT("in odd weeks");
	R::N_WOECHENTLICH = wxT("[n]-weekly from (incl.) the week after [beginning date]");
	R::W_IM_MONAT = wxT("[n-th] [weekday] in month");
	R::MONATLICH = wxT("monthly");
	wxString tmodi[] = {R::TAEGLICH, R::WOECHENTLICH, R::GERADE_KW, R::UNGERADE_KW, R::N_WOECHENTLICH, R::W_IM_MONAT, R::MONATLICH};
	for (int i = 0; i < R::TMODI_NUM; i++) {
		R::TMODI[i] = tmodi[i];
	}
	R::LETZTER = wxT("Last");
	R::VORLETZTER = wxT("Last but one");
	R::WOCHENTAG = wxT("Weekday");
	R::TAG = wxT("Day");
	R::DATUM_AB = wxT("Beginning date (incl.)");
	R::DATUM_BIS = wxT("End date (incl.)");
	//Gruppen
	R::GRUPPE = wxT("Group");
	R::RESTLISTE = wxT("Remaining volunteers");
	R::BEV_GEM = wxT("Preferably together");
	R::NUR_GEM = wxT("Exclusively together");
	wxString mgmodi[] = {R::BEV_GEM, R::NUR_GEM};
	for (int i = 0; i < 2; i++) {
		R::MGMODI[i] = mgmodi[i];
	}
	R::RESTTERMINE = wxT("Remaining masses");
	R::TGRUPPE = wxT("Collection");
	R::PERIODISCH = wxT("Weekly: 7-day-period, beginning on (incl.) ");
	R::NICHT_PERIODISCH = wxT("Non-periodic");
	wxString tgmodi[] = {R::PERIODISCH, R::NICHT_PERIODISCH};
	for (int i = 0; i < R::TGMODI_NUM; i++) {
		R::TGMODI[i] = tgmodi[i];
	}
	//Dienste
	R::DIENST = wxT("Duty");
	R::ALLGEMEIN = wxT("Normal");
	//Fehlzeiten
	R::FEHLZEIT = wxT("Absence time");
	R::ZEITRAUM = wxT("Period of time");
	R::TERMIN = wxT("Mass");
	wxString fehlzeit_modi[] = {R::ZEITRAUM, R::WOCHENTAG, R::TERMIN};
	for (int i = 0; i < 3; i++) {
		R::FEHLZEIT_MODI[i] = fehlzeit_modi[i];
	}
	R::VON = wxT("From");
	R::BIS = wxT("Until");
	//Pläne
	R::OEFFNEN = wxT("Open");
	R::ZURUECK = wxT("Back");
	R::WEITER = wxT("Continue");
	R::EINSAETZE = wxT("Assignments");
	R::MASKE = wxT("Input mask");
	R::AUTOMATISCH = wxT("Automatic");
	R::STOPPEN = wxT("Stop");
	R::LEEREN = wxT("Empty");
	R::EXPORT = wxT("Export");
	R::SPEICHERN = wxT("Save");
	R::DATEN = wxT("Data");
	R::EINSTELLUNGEN = wxT("Settings");
	R::FEHLZEITEN_ANRECHNEN = wxT("Absence times will be partially considered when running algorithm");
	R::FEHLZEITEN_KOMPENSIEREN = wxT("Absence times have to be compensated if possible");
	R::ALG_MINIMUM = wxT("Algorithm 1 (with extensive minimum search, poss. faster)");
	R::ALG_CHRONO = wxT("Algorithm 2 (poss. more evenly distributed)");
	//Export
	R::MESSDIENERPLAN = wxT("Service Plan");
	R::MESSDIENERPLAN_SH = wxT("ServicePlan");
	R::LAYOUT = wxT("Layout");
	R::VORSCHAU = wxT("Preview");
	R::MINIS_LAYOUT = wxT("Order of volunteers");
	wxString minis_layout_modi[] = {wxT("in [n] columns"), wxT("comma-separated")};
	for (int i = 0; i < 2; i++) {
		R::MINIS_LAYOUT_MODI[i] = minis_layout_modi[i];
	}
	R::BASICS_LAYOUT = wxT("Position of Mass Description");
	wxString basics_layout_modi[] = {wxT("left"), wxT("top")};
	for (int i = 0; i < 2; i++) {
		R::BASICS_LAYOUT_MODI[i] = basics_layout_modi[i];
	}
	R::NAMEN_LAYOUT = wxT("Format of Names");
	wxString namen_layout_modi[] = {wxT("First-Name Surname"), wxT("F. Surname"), wxT("F. S."), wxT("First-Name")};
	for (int i = 0; i < 4; i++) {

		R::NAMEN_LAYOUT_MODI[i] = namen_layout_modi[i];
	}
	R::DATEI_AUSGABE = wxT("Save to file");
	R::CLIPBOARD_AUSGABE = wxT("Copy to clipboard");
	R::TITEL = wxT("Title");
	R::DIENSTE_ZEIGEN = wxT("Distinguish ministries");
	R::SPEICHERN_HTML = wxT("Save as HTML");
	R::SPEICHERN_CSV = wxT("Save as CSV (tab-separated)");
	R::SPEICHERN_EXCEL_XML = wxT("Save as Excel-XML");
	R::SPALTEN = wxT("Columns");
	R::NUM = wxT("No.");
	R::MESSDIENERLISTE = wxT("Volunteer List");
	R::MESSDIENERLISTE_SH = wxT("VolunteerList");
	//Import
	R::IMPORT = wxT("Import");
	R::IMPORTIEREN = wxT("Import");
	R::SEPARATOR = wxT("Separator");
	R::CSV_DATEI_WAEHLEN = wxT("Choose CSV file");
	R::MINI_CSV_MSG = wxT("The lines of the CSV file are evaluated from left to right in the following format (entries may be empty or missing):");
	R::MINI_IMPORT_MSG = wxT("Only volunteers are imported that are not yet contained in the list by the id name + first-name.");
	//Extras
	R::EMAILS = wxT("E-Mails");
	R::KOPIERTEMAILS = wxT("copies existing e-mail addresses to clipboard");
	R::ADRESSEN = wxT("Addresses");
	R::KOPIERTADRESSEN = wxT("copies formated list of existing addresses to clipboard");
	R::KOPIERTEMAILSFERTIG = wxT("E-mail addresses copied to clipboard!");
	R::KOPIERTADRESSENFERTIG = wxT("Addresses copied to clipboard!");
	R::KOPIERTWARNICHTMOEGLICH = wxT("\nFailed doing the following volunteers:\n");
	//Über
	R::HEADLINE = wxT("a small program to efficiently create high-quality service plans");
	R::AUTOR = wxT("Author: ");
	R::KOMPILIERTMIT = wxT("Compiled with: ");
	R::BIBLIOTHEKEN = wxT("Libraries: ");
	R::INSTALLATIONSVERZEICHNIS = wxT("Installation directory: ");

	//Einstellungen

	//Nachrichten
	R::MSG_MINI_UNIQUE = wxT("A volunteer must be uniquely identifiable by name + first-name.");
	R::MSG_FEHLZEIT_UNIQUE = wxT("This absence time already exists.");
	R::MSG_TIME_ERR = wxT("Please enter a valid time in the format hh:mm.");
	R::MSG_TIME_BEGINN_ERR = wxT("Please enter a valid beginning time in the format hh:mm.");
	R::MSG_TIME_ENDE_ERR = wxT("Please enter a valid end time in the format hh:mm.");
	R::MSG_WEEK_NUM_ERR = wxT("Please enter a valid amount of weeks [n].");
	R::MSG_WEEK_COUNT_START = wxT("Please enter a beginning time from which the weeks shall be counted (first mass is on first fitting weekday after [") + R::DATUM_BEGINN + wxT("]).");
	R::MSG_GROUP_NUM = wxT("A group should contain at least 2 members.");
	R::MSG_TGROUP_NUM = wxT("A collection should contain at least 2 members.");
	R::MSG_EINZEL_UNIQUE = wxT("A single mass must be uniquely identifiable by place, date and time.");
	R::MSG_SERIE_UNIQUE = wxT("A regular mass must be uniquely identifiable by place, time, mode, beginning and end date.");
	R::MSG_DIENST_UNIQUE = wxT("A ministry must have a unique name.");
	R::MSG_MINI_SEL_ERR = wxT("Please select a volunteer.");
	R::MSG_TERMIN_SEL_ERR = wxT("Please select a mass.");
	R::MSG_DIENST_SEL_ERR = wxT("Please select a ministry.");
	R::MSG_DATUM_ORDER = wxT("The end date is before the beginning date.");
	R::MSG_PLAN_CREATE_IMPOSSIBLE = wxT("Unfortunately, it is impossible to create a plan given these requirements.");
	R::MSG_MANUAL_NOT_OPENED = wxT("Could not find a program to open the PDF handbook under MiniPlaner/help/Handbuch.pdf.");
	R::MSG_FILE_NOT_FOUND = wxT("File not found.");
	R::Q_SPEICHERN = wxT("Save changes?");
	R::Q_LOESCHEN = wxT("Delete?");
}

void R::setLang() {
	if (R::lang == R::LANG_DE) {
		setLangDE();
	} else {
		setLangEN();
	}
}

int R::lang = R::LANG_DE;

void R::setSubWindowPosition(wxWindow* parent, wxDialog* self) {
	wxPoint parent_point = parent->GetScreenPosition();
	wxSize parent_size = parent->GetSize();
	wxSize own_size = self->GetSize();
	self->SetPosition(wxPoint(parent_point.x + parent_size.x - own_size.x - 150, parent_point.y + 30));
}

const wxString R::VERSION_ID = wxT("2.0.4");
const int R::VERSION_NUMBER = 4;//need number for comparison

wxString R::window_size = wxT("");