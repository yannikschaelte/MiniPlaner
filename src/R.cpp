/* 
 * File:   R.cpp
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:18 PM
 */

#include "R.h"

//Allgemein
wxString R::MINI_PLANER;
wxString R::DIENST_DIALOG;
wxString R::MINI_DIALOG;
wxString R::EINZELTERMIN_DIALOG;
wxString R::SERIENTERMIN_DIALOG;
wxString R::TERMIN_DIENST_DIALOG;
wxString R::MGRUPPE_DIALOG;
wxString R::TGRUPPE_DIALOG;
wxString R::FEHLZEIT_DIALOG;
wxString R::PLAN_DIALOG;
wxString R::TERMIN_DIALOG;
wxString R::EXPORT_LAYOUT_DIALOG;
wxString R::MINI_EXPORT_DIALOG;
wxString R::MINI_IMPORT_DIALOG;
wxString R::MINI_EXTRAS_DIALOG;
wxString R::EINZELTERMIN_IMPORT_DIALOG;
wxString R::SPEICHERN_DIALOG;
wxString R::LOESCHEN_DIALOG;
wxString R::PLANER_SETTINGS_DIALOG;

wxString R::HILFE;
wxString R::UEBER;
wxString R::SPRACHE;
wxString R::KONTAKT_MSG;
wxString R::EXTRAS;
wxString R::SEMIKOLON;
wxString R::KOMMA;
wxString R::LEERZEICHEN;
wxString R::ANDERES;

wxString R::OK;
wxString R::CANCEL;
wxString R::ADD;
wxString R::DEL;
wxString R::EDT;
wxString R::JA;
wxString R::NEIN;

wxString R::DIENSTE;
wxString R::MINI;
wxString R::MINIS;
wxString R::MGRUPPEN;
wxString R::TERMINE;
wxString R::TGRUPPEN;
wxString R::FEHLZEITEN;
wxString R::PLAENE;
//Adresse
wxString R::STRASSE_NR;
wxString R::PLZ_ORT;
wxString R::TEL;
wxString R::MOBILE;
wxString R::EMAIL;
//Messdiener
wxString R::NAME;
wxString R::NACHNAME;
wxString R::VORNAME;
wxString R::GEBURTSTAG;
wxString R::BEM;
wxString R::MINI_ATTS[R::MINI_ATTS_NUM];
//Termine
wxString R::EINZELTERMINE;
wxString R::SERIENTERMINE;
wxString R::ANZAHL;
wxString R::ORT;
wxString R::DATUM;
wxString R::ZEIT;
wxString R::MODUS;
wxString R::DATUM_BEGINN;
wxString R::DATUM_ENDE;
wxString R::TEINZEL_ATTS[R::TEINZEL_NUM];
wxString R::TSERIE_ATTS[R::TSERIE_NUM];

wxString R::SONNTAG;
wxString R::MONTAG;
wxString R::DIENSTAG;
wxString R::MITTWOCH;
wxString R::DONNERSTAG;
wxString R::FREITAG;
wxString R::SAMSTAG;
wxString R::WOCHENTAGE[7];
//Modus
wxString R::TAEGLICH;
wxString R::WOECHENTLICH;
wxString R::GERADE_KW;
wxString R::UNGERADE_KW;
wxString R::N_WOECHENTLICH;
wxString R::W_IM_MONAT;
wxString R::MONATLICH;
wxString R::TMODI[R::TMODI_NUM];
wxString R::LETZTER;
wxString R::VORLETZTER;
wxString R::WOCHENTAG;
wxString R::TAG;
wxString R::DATUM_AB;
wxString R::DATUM_BIS;
//Gruppen
wxString R::GRUPPE;
wxString R::RESTLISTE;
wxString R::BEV_GEM;
wxString R::NUR_GEM;
wxString R::MGMODI[2];
wxString R::RESTTERMINE;
wxString R::TGRUPPE;
wxString R::PERIODISCH;
wxString R::NICHT_PERIODISCH;
wxString R::TGMODI[R::TGMODI_NUM];
//Dienste
wxString R::DIENST;
wxString R::ALLGEMEIN;
//Fehlzeiten
wxString R::FEHLZEIT;
wxString R::ZEITRAUM;
wxString R::TERMIN;
wxString R::FEHLZEIT_MODI[3];
wxString R::VON;
wxString R::BIS;
//Pläne
wxString R::OEFFNEN;
wxString R::ZURUECK;
wxString R::WEITER;
wxString R::EINSAETZE;
wxString R::MASKE;
wxString R::AUTOMATISCH;
wxString R::STOPPEN;
wxString R::LEEREN;
wxString R::EXPORT;
wxString R::SPEICHERN;
wxString R::DATEN;
wxString R::EINSTELLUNGEN;
wxString R::FEHLZEITEN_ANRECHNEN;
wxString R::FEHLZEITEN_KOMPENSIEREN;
wxString R::ALG_MINIMUM;
wxString R::ALG_CHRONO;
//Export
wxString R::MESSDIENERPLAN;
wxString R::MESSDIENERPLAN_SH;
wxString R::LAYOUT;
wxString R::VORSCHAU;
wxString R::MINIS_LAYOUT;
wxString R::MINIS_LAYOUT_MODI[2];
wxString R::BASICS_LAYOUT;
wxString R::BASICS_LAYOUT_MODI[2];
wxString R::NAMEN_LAYOUT;
wxString R::NAMEN_LAYOUT_MODI[4];
wxString R::DATEI_AUSGABE;
wxString R::CLIPBOARD_AUSGABE;
wxString R::TITEL;
wxString R::DIENSTE_ZEIGEN;
wxString R::SPEICHERN_HTML;
wxString R::SPEICHERN_CSV;
wxString R::SPEICHERN_XLSX;
wxString R::SPALTEN;
wxString R::NUM;
wxString R::MESSDIENERLISTE;
wxString R::MESSDIENERLISTE_SH;
//Import
wxString R::IMPORT;
wxString R::IMPORTIEREN;
wxString R::SEPARATOR;
wxString R::CSV_DATEI_WAEHLEN;
wxString R::MI_PAGE_EXPORT;
wxString R::MI_PAGE_IMPORT;
wxString R::MI_PULL;
wxString R::MI_PULL_OK;
wxString R::MI_PULL_ERR;
wxString R::MELDUNG;
wxString R::FEHLER_T;
wxString R::DATEI_SPEICHERN;
wxString R::UPDATE_TITLE;
wxString R::UPDATE_MSG;
wxString R::UPDATE_DOWNLOAD;
wxString R::TMODUS_N_WOECHENTLICH;
wxString R::CSV_FILTER;
wxString R::MINI_CSV_MSG;
wxString R::MINI_IMPORT_MSG;
wxString R::EINZELTERMIN_CSV_MSG;
wxString R::EINZELTERMIN_IMPORT_MSG;
//Extras
wxString R::EMAILS;
wxString R::KOPIERTEMAILS;
wxString R::ADRESSEN;
wxString R::KOPIERTADRESSEN;
wxString R::KOPIERTEMAILSFERTIG;
wxString R::KOPIERTADRESSENFERTIG;
wxString R::KOPIERTWARNICHTMOEGLICH;
//Über
wxString R::HEADLINE;
wxString R::AUTOR;
wxString R::BEITRAGENDE;
wxString R::KOMPILIERTMIT;
wxString R::BIBLIOTHEKEN;
wxString R::INSTALLATIONSVERZEICHNIS;
//Einstellungen
wxString R::MSG_LANG_CHANGE_DE;
wxString R::MSG_LANG_CHANGE_EN;
//Nachrichten
wxString R::MSG_MINI_UNIQUE;
wxString R::MSG_FEHLZEIT_UNIQUE;
wxString R::MSG_TIME_ERR;
wxString R::MSG_TIME_BEGINN_ERR;
wxString R::MSG_TIME_ENDE_ERR;
wxString R::MSG_WEEK_NUM_ERR;
wxString R::MSG_WEEK_COUNT_START;
wxString R::MSG_GROUP_NUM;
wxString R::MSG_TGROUP_NUM;
wxString R::MSG_EINZEL_UNIQUE;
wxString R::MSG_SERIE_UNIQUE;
wxString R::MSG_DIENST_UNIQUE;
wxString R::MSG_MINI_SEL_ERR;
wxString R::MSG_TERMIN_SEL_ERR;
wxString R::MSG_DIENST_SEL_ERR;
wxString R::MSG_DATUM_ORDER;
wxString R::MSG_PLAN_CREATE_IMPOSSIBLE;
wxString R::MSG_MANUAL_NOT_OPENED;
wxString R::MSG_FILE_NOT_FOUND;
wxString R::MSG_RETRIEVE_NOT_POSSIBLE;
wxString R::MSG_IMPORT_NOT_POSSIBLE;
wxString R::Q_SPEICHERN;
wxString R::Q_LOESCHEN;

wxString R::WELCOME_TITLE;
wxString R::WELCOME_INTRO;
wxString R::WELCOME_EMPTY;
wxString R::WELCOME_DEMO_NOTE;
wxString R::WELCOME_DEMO;
wxString R::TOUR_DIENSTE;
wxString R::TOUR_MINIS;
wxString R::TOUR_MGRUPPEN;
wxString R::TOUR_TERMINE;
wxString R::TOUR_TGRUPPEN;
wxString R::TOUR_FEHLZEITEN;
wxString R::TOUR_PLAENE;
wxString R::TOUR_TITLE;
wxString R::TOUR_DOCS;
wxString R::OPEN_MANUAL;
wxString R::SET_DATA_FOLDER;
wxString R::SET_OPEN_FOLDER;
wxString R::SET_LOAD_DEMO;
wxString R::SET_DELETE_ALL;
wxString R::SET_LANG_NOTE;
wxString R::MSG_CONFIRM_DEMO;
wxString R::MSG_CONFIRM_DELETE;
wxString R::MSG_RESTART;

void R::setLangDE() {
	R::MINI_PLANER = wxT("MiniPlaner");
	R::DIENST_DIALOG = wxT("Dienst-Dialog");
	R::MINI_DIALOG = wxT("Mini-Dialog");
	R::EINZELTERMIN_DIALOG = wxT("Einzeltermin-Dialog");
	R::SERIENTERMIN_DIALOG = wxT("Serientermin-Dialog");
	R::TERMIN_DIENST_DIALOG = wxT("Termin-Dienst-Dialog");
	R::MGRUPPE_DIALOG = wxT("Minigruppe-Dialog");
	R::TGRUPPE_DIALOG = wxT("Terminverbund-Dialog");
	R::FEHLZEIT_DIALOG = wxT("Fehlzeit-Dialog");
	R::PLAN_DIALOG = wxT("Planer");
	R::TERMIN_DIALOG = wxT("Termin-Dialog");
	R::EXPORT_LAYOUT_DIALOG = wxT("Export-Layout-Dialog");
	R::MINI_EXPORT_DIALOG = wxT("Mini-Export-Dialog");
	R::MINI_IMPORT_DIALOG = wxT("Mini-Import-Dialog");
	R::MINI_EXTRAS_DIALOG = wxT("Mini-Extras-Dialog");
	R::EINZELTERMIN_IMPORT_DIALOG = wxT("Einzeltermin-Import-Dialog");
	R::SPEICHERN_DIALOG = wxT("");
	R::LOESCHEN_DIALOG = wxT("");
	R::PLANER_SETTINGS_DIALOG = wxT("Algorithmus-Einstellungen-Dialog");
	R::HILFE = wxT("Hilfe");
	R::UEBER = wxT("Über");
	R::SPRACHE = wxT("Sprache der Benutzeroberfläche");
	R::KONTAKT_MSG = wxT("Bei Fragen, Programmfehlern, Problemen oder Ideen dürfen Sie sich jederzeit gern melden.");
	R::EXTRAS = wxT("Extras");
	R::SEMIKOLON = wxT("Semikolon");
	R::KOMMA = wxT("Komma");
	R::LEERZEICHEN = wxT("Leerzeichen");
	R::ANDERES = wxT("Anderes: ");
	R::OK = wxT("OK");
	R::CANCEL = wxT("Abbrechen");
	R::ADD = wxT("Neu");
	R::DEL = wxT("Entfernen");
	R::EDT = wxT("Ändern");
	R::JA = wxT("Ja");
	R::NEIN = wxT("Nein");
	R::DIENSTE = wxT("Dienste");
	R::MINI = wxT("Mini");
	R::MINIS = wxT("Minis");
	R::MGRUPPEN = wxT("M.-Gruppen");
	R::TERMINE = wxT("Termine");
	R::TGRUPPEN = wxT("T.-Verbünde");
	R::FEHLZEITEN = wxT("Fehlzeiten");
	R::PLAENE = wxT("Pläne");
	R::STRASSE_NR = wxT("Straße Nr.");
	R::PLZ_ORT = wxT("PLZ Ort");
	R::TEL = wxT("Telefon");
	R::MOBILE = wxT("Mobil");
	R::EMAIL = wxT("E-Mail");
	R::NAME = wxT("Name");
	R::NACHNAME = wxT("Nachname");
	R::VORNAME = wxT("Vorname");
	R::GEBURTSTAG = wxT("Geburtsdatum");
	R::BEM = wxT("Bem.");
	{
		const wxString t[] = {R::NACHNAME, R::VORNAME, R::DIENSTE, R::GEBURTSTAG, R::STRASSE_NR, R::PLZ_ORT, R::TEL, R::MOBILE, R::EMAIL, R::BEM};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::MINI_ATTS[i] = t[i];
	}
	R::EINZELTERMINE = wxT("Einzeltermine");
	R::SERIENTERMINE = wxT("Serientermine");
	R::ANZAHL = wxT("Anzahl");
	R::ORT = wxT("Ort");
	R::DATUM = wxT("Datum");
	R::ZEIT = wxT("Zeit");
	R::MODUS = wxT("Modus");
	R::DATUM_BEGINN = wxT("Anfangsdatum (inkl.)");
	R::DATUM_ENDE = wxT("Enddatum (inkl.)");
	{
		const wxString t[] = {NAME, ORT, DATUM, ZEIT, DIENSTE, BEM};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::TEINZEL_ATTS[i] = t[i];
	}
	{
		const wxString t[] = {NAME, ORT, MODUS, ZEIT, DIENSTE, DATUM_BEGINN, DATUM_ENDE, BEM};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::TSERIE_ATTS[i] = t[i];
	}
	R::SONNTAG = wxT("So.");
	R::MONTAG = wxT("Mo.");
	R::DIENSTAG = wxT("Di.");
	R::MITTWOCH = wxT("Mi.");
	R::DONNERSTAG = wxT("Do.");
	R::FREITAG = wxT("Fr.");
	R::SAMSTAG = wxT("Sa.");
	{
		const wxString t[] = {SONNTAG, MONTAG, DIENSTAG, MITTWOCH, DONNERSTAG, FREITAG, SAMSTAG};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::WOCHENTAGE[i] = t[i];
	}
	R::TAEGLICH = wxT("täglich");
	R::WOECHENTLICH = wxT("wöchentlich");
	R::GERADE_KW = wxT("in geraden KWs");
	R::UNGERADE_KW = wxT("in ungeraden KWs");
	R::N_WOECHENTLICH = wxT("[n]-wöchentlich ab (inkl.) der Woche nach [Anfangsdatum]");
	R::W_IM_MONAT = wxT("[n-ter] [Wochentag] im Monat");
	R::MONATLICH = wxT("monatlich");
	{
		const wxString t[] = {TAEGLICH, WOECHENTLICH, GERADE_KW, UNGERADE_KW, N_WOECHENTLICH, W_IM_MONAT, MONATLICH};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::TMODI[i] = t[i];
	}
	R::LETZTER = wxT("letzter");
	R::VORLETZTER = wxT("vorletzter");
	R::WOCHENTAG = wxT("Wochentag");
	R::TAG = wxT("Tag");
	R::DATUM_AB = wxT("Anfangsdatum (inkl.)");
	R::DATUM_BIS = wxT("Enddatum (inkl.)");
	R::GRUPPE = wxT("Gruppe");
	R::RESTLISTE = wxT("restliche Minis");
	R::BEV_GEM = wxT("vorzugsweise gemeinsam");
	R::NUR_GEM = wxT("ausschließlich gemeinsam");
	{
		const wxString t[] = {BEV_GEM, NUR_GEM};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::MGMODI[i] = t[i];
	}
	R::RESTTERMINE = wxT("restliche Termine");
	R::TGRUPPE = wxT("Verbund");
	R::PERIODISCH = wxT("wöchentlich: 7-Tage-Periode, beginnend ab (inkl.) ");
	R::NICHT_PERIODISCH = wxT("nicht-periodisch");
	{
		const wxString t[] = {PERIODISCH, NICHT_PERIODISCH};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::TGMODI[i] = t[i];
	}
	R::DIENST = wxT("Dienst");
	R::ALLGEMEIN = wxT("Normal");
	R::FEHLZEIT = wxT("Fehlzeit");
	R::ZEITRAUM = wxT("Zeitraum");
	R::TERMIN = wxT("Termin");
	{
		const wxString t[] = {ZEITRAUM, WOCHENTAG, TERMIN};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::FEHLZEIT_MODI[i] = t[i];
	}
	R::VON = wxT("von");
	R::BIS = wxT("bis");
	R::OEFFNEN = wxT("Öffnen");
	R::ZURUECK = wxT("Zurück");
	R::WEITER = wxT("Weiter");
	R::EINSAETZE = wxT("Einsätze");
	R::MASKE = wxT("Eingabemaske");
	R::AUTOMATISCH = wxT("Automatisch");
	R::STOPPEN = wxT("Stoppen");
	R::LEEREN = wxT("Leeren");
	R::EXPORT = wxT("Export");
	R::SPEICHERN = wxT("Speichern");
	R::DATEN = wxT("Daten");
	R::EINSTELLUNGEN = wxT("Einstellungen");
	R::FEHLZEITEN_ANRECHNEN = wxT("Fehl-Zeiträume werden intern bei Einsatzhäufigkeiten anteilig angerechnet");
	R::FEHLZEITEN_KOMPENSIEREN = wxT("Fehl-Zeiträume werden zu einer anderen Zeit kompensiert, falls möglich");
	R::ALG_MINIMUM = wxT("Algorithmus 1 (mit erweiterter Minimumssuche, evtl. schneller)");
	R::ALG_CHRONO = wxT("Algorithmus 2 (evtl. gleichmäßigere Abstände zwischen Einsätzen)");
	R::MESSDIENERPLAN = wxT("Ministrantenplan");
	R::MESSDIENERPLAN_SH = R::MESSDIENERPLAN;
	R::LAYOUT = wxT("Layout");
	R::VORSCHAU = wxT("Vorschau");
	R::MINIS_LAYOUT = wxT("Anordnung Minis");
	{
		const wxString t[] = {wxT("in [n] Spalten"), wxT("kommasepariert")};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::MINIS_LAYOUT_MODI[i] = t[i];
	}
	R::BASICS_LAYOUT = wxT("Position Terminbeschreibung");
	{
		const wxString t[] = {wxT("links"), wxT("oben")};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::BASICS_LAYOUT_MODI[i] = t[i];
	}
	R::NAMEN_LAYOUT = wxT("Format Namen");
	{
		const wxString t[] = {wxT("Vorname Nachname"), wxT("V. Nachname"), wxT("Vorname N."), wxT("Vorname")};
		for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) R::NAMEN_LAYOUT_MODI[i] = t[i];
	}
	R::DATEI_AUSGABE = wxT("Als Datei speichern");
	R::CLIPBOARD_AUSGABE = wxT("In Zwischenablage kopieren");
	R::TITEL = wxT("Überschrift");
	R::DIENSTE_ZEIGEN = wxT("Unterteilung nach Diensten");
	R::SPEICHERN_HTML = wxT("Im HTML-Format speichern");
	R::SPEICHERN_CSV = wxT("Im Tab-separierten CSV-Format speichern");
	R::SPEICHERN_XLSX = wxT("Als Excel-Datei speichern");
	R::SPALTEN = wxT("Spalten");
	R::NUM = wxT("Nr.");
	R::MESSDIENERLISTE = wxT("Ministrantenliste");
	R::MESSDIENERLISTE_SH = R::MESSDIENERLISTE;
	R::IMPORT = wxT("Import");
	R::IMPORTIEREN = wxT("Importieren");
	R::SEPARATOR = wxT("Separator");
	R::CSV_DATEI_WAEHLEN = wxT("CSV-Datei wählen");
	R::MI_PAGE_EXPORT = wxT("Daten für MiniInterface-Formular exportieren");
	R::MI_PAGE_IMPORT = wxT("Mit Daten aus MiniInterface-Formular Plan erstellen");
	R::MI_PULL = wxT("Lade Daten aus Zwischenablage");
	R::MI_PULL_OK = wxT("Daten erfolgreich verarbeitet!");
	R::MI_PULL_ERR = wxT("Daten aus Zwischenablage konnten nicht korrekt verarbeitet werden!");
	R::MELDUNG = wxT("Meldung");
	R::FEHLER_T = wxT("Fehler");
	R::DATEI_SPEICHERN = wxT("Datei speichern");
	R::UPDATE_TITLE = wxT("Update-Information");
	R::UPDATE_MSG = wxT("Es ist eine neuere Version des Programms verfügbar.");
	R::UPDATE_DOWNLOAD = wxT("Zum Download");
	R::TMODUS_N_WOECHENTLICH = wxT("%i-wöchentlich am %s, ab (inkl.) der Woche nach [Anfangsdatum]");
	R::CSV_FILTER = wxT("CSV-Dateien (*.csv)|*.csv|Alle (*.*)|*.*");
	R::MINI_CSV_MSG = wxT("Die Zeilen der CSV-Datei werden von links nach rechts in folgendem Format ausgewertet:");
	R::MINI_IMPORT_MSG = wxT("Es werden nur Minis importiert, die über die Kennung Nachname+Vorname noch nicht in der\n"
			"bisherigen Liste enthalten sind.");
	R::EINZELTERMIN_CSV_MSG = wxT("Die Zeilen der CSV-Datei werden von links nach rechts in folgendem ");
	R::EINZELTERMIN_IMPORT_MSG = wxT("Es werden nur Termine importiert, die über die Kennung Ort+Datum+Zeit noch nicht in der\n"
			"bisherigen Liste enthalten sind.");
	R::EMAILS = wxT("E-Mails");
	R::KOPIERTEMAILS = wxT("kopiert vorhandene E-Mail-Adressen Semikolon-separiert in Zwischenablage");
	R::ADRESSEN = wxT("Adressen");
	R::KOPIERTADRESSEN = wxT("kopiert Liste aller vorhandenen Adressen formatiert in Zwischenablage");
	R::KOPIERTEMAILSFERTIG = wxT("Email-Adressen in Zwischenablage kopiert!");
	R::KOPIERTADRESSENFERTIG = wxT("Adressen in Zwischenablage kopiert!");
	R::KOPIERTWARNICHTMOEGLICH = wxT("\nBei folgenden Minis war dies nicht möglich:\n");
	R::HEADLINE = wxT("ein Programm zum effizienten Erstellen hochwertiger Ministrantenpläne");
	R::AUTOR = wxT("Autor: ");
	R::BEITRAGENDE = wxT("Beitragende: ");
	R::KOMPILIERTMIT = wxT("Kompiliert mit: ");
	R::BIBLIOTHEKEN = wxT("Bibliotheken: ");
	R::INSTALLATIONSVERZEICHNIS = wxT("Installationsverzeichnis: ");
	R::MSG_LANG_CHANGE_DE = wxT("(Änderung erst bei Programm-Neustart wirksam)");
	R::MSG_LANG_CHANGE_EN = wxT("(Change only visible after program restart)");
	R::MSG_MINI_UNIQUE = wxT("Ein Mini muss über Name+Vorname eindeutig identifizierbar sein.");
	R::MSG_FEHLZEIT_UNIQUE = wxT("Diese Fehlzeit existiert bereits.");
	R::MSG_TIME_ERR = wxT("Bitte eine gültige Zeit im Format hh:mm angeben.");
	R::MSG_TIME_BEGINN_ERR = wxT("Bitte eine gültige Anfangszeit im Format hh:mm angeben.");
	R::MSG_TIME_ENDE_ERR = wxT("Bitte eine gültige Endzeit im Format hh:mm angeben.");
	R::MSG_WEEK_NUM_ERR = wxT("Bitte eine gültige Anzahl Wochen [n] angeben.");
	R::MSG_WEEK_COUNT_START = wxT("Bitte ein Anfangsdatum angeben, ab dem die Zählung der Wochen erfolgen soll (erster Termin ist an erstem passendem Wochentag ab [") + DATUM_BEGINN + wxT("]).");
	R::MSG_GROUP_NUM = wxT("Eine Gruppe sollte mindestens 2 Mitglieder haben.");
	R::MSG_TGROUP_NUM = wxT("Ein Verbund sollte mindestens 2 Mitglieder haben.");
	R::MSG_EINZEL_UNIQUE = wxT("Ein Einzeltermin muss über Ort, Datum und Zeit eindeutig identifizierbar sein.");
	R::MSG_SERIE_UNIQUE = wxT("Ein Serientermin muss über Ort, Zeit, Modus, Anfangs- und Enddatum eindeutig identifizierbar sein.");
	R::MSG_DIENST_UNIQUE = wxT("Ein Dienst muss eine eindeutige Bezeichnung haben.");
	R::MSG_MINI_SEL_ERR = wxT("Bitte wählen Sie einen Mini aus.");
	R::MSG_TERMIN_SEL_ERR = wxT("Bitte wählen Sie einen Termin aus.");
	R::MSG_DIENST_SEL_ERR = wxT("Bitte wählen Sie einen Dienst aus.");
	R::MSG_DATUM_ORDER = wxT("Das Enddatum liegt vor dem Anfangsdatum.");
	R::MSG_PLAN_CREATE_IMPOSSIBLE = wxT("Zu diesen Vorgaben kann leider definitiv kein Plan erstellt werden.");
	R::MSG_MANUAL_NOT_OPENED = wxT("Das Handbuch konnte nicht im Browser geöffnet werden: https://yannikschaelte.github.io/MiniPlaner/Handbuch.pdf");
	R::MSG_FILE_NOT_FOUND = wxT("Die Datei konnte nicht gefunden werden.");
	R::MSG_RETRIEVE_NOT_POSSIBLE = wxT("Die folgenden Einträge konnten nicht eingelesen werden");
	R::MSG_IMPORT_NOT_POSSIBLE = wxT("Die folgenden Einträge wurden nicht importiert, da sie bereits vorhanden sind:");
	R::Q_SPEICHERN = wxT("Änderungen speichern?");
	R::Q_LOESCHEN = wxT("Entfernen?");
	R::WELCOME_TITLE = wxT("Willkommen beim MiniPlaner");
	R::WELCOME_INTRO = wxT("Dienstpläne für Ihre Minis. Wie möchten Sie starten?");
	R::WELCOME_EMPTY = wxT("Leer starten");
	R::WELCOME_DEMO_NOTE = wxT("Beispieldaten löschen: <b>Einstellungen</b>.");
	R::WELCOME_DEMO = wxT("Mit Beispieldaten starten");
	R::TOUR_DIENSTE = wxT("Aufgaben einer Messe, z.B. Altar");
	R::TOUR_MINIS = wxT("Wer die Dienste übernimmt");
	R::TOUR_MGRUPPEN = wxT("Wer zusammen eingeteilt wird, z.B. Geschwister");
	R::TOUR_TERMINE = wxT("Einzelne und regelmäßige Messen");
	R::TOUR_TGRUPPEN = wxT("Termine mit denselben Minis");
	R::TOUR_FEHLZEITEN = wxT("Wann Minis nicht können");
	R::TOUR_PLAENE = wxT("Plan erstellen und exportieren");
	R::TOUR_TITLE = wxT("Der Weg zum Plan");
	R::TOUR_DOCS = wxT("Mehr Hilfe:");
	R::OPEN_MANUAL = wxT("Handbuch öffnen");
	R::SET_DATA_FOLDER = wxT("Datenordner");
	R::SET_OPEN_FOLDER = wxT("Ordner öffnen");
	R::SET_LOAD_DEMO = wxT("Beispieldaten laden");
	R::SET_DELETE_ALL = wxT("Alle Daten löschen");
	R::SET_LANG_NOTE = wxT("Die Sprache wird nach einem Neustart übernommen.");
	R::MSG_CONFIRM_DEMO = wxT("Alle bisherigen Daten werden durch Beispieldaten ersetzt. Eine Sicherungskopie bleibt im Datenordner erhalten. Fortfahren?");
	R::MSG_CONFIRM_DELETE = wxT("Alle Daten werden gelöscht. Eine Sicherungskopie bleibt im Datenordner erhalten. Fortfahren?");
	R::MSG_RESTART = wxT("Der MiniPlaner wird jetzt beendet. Bitte starten Sie ihn erneut.");
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
	R::WELCOME_TITLE = wxT("Welcome to the MiniPlaner");
	R::WELCOME_INTRO = wxT("Service plans for your volunteers. How do you want to start?");
	R::WELCOME_EMPTY = wxT("Start empty");
	R::WELCOME_DEMO_NOTE = wxT("Delete demo data under <b>Settings</b>.");
	R::WELCOME_DEMO = wxT("Start with demo data");
	R::TOUR_DIENSTE = wxT("Tasks in a mass, e.g. altar");
	R::TOUR_MINIS = wxT("Who takes them on");
	R::TOUR_MGRUPPEN = wxT("Who serves together, e.g. siblings");
	R::TOUR_TERMINE = wxT("Single and regular masses");
	R::TOUR_TGRUPPEN = wxT("Masses with the same volunteers");
	R::TOUR_FEHLZEITEN = wxT("When volunteers are unavailable");
	R::TOUR_PLAENE = wxT("Create and export the plan");
	R::TOUR_TITLE = wxT("From data to plan");
	R::TOUR_DOCS = wxT("More help:");
	R::OPEN_MANUAL = wxT("Open manual");
	R::SET_DATA_FOLDER = wxT("Data folder");
	R::SET_OPEN_FOLDER = wxT("Open folder");
	R::SET_LOAD_DEMO = wxT("Load demo data");
	R::SET_DELETE_ALL = wxT("Delete all data");
	R::SET_LANG_NOTE = wxT("The language is applied after a restart.");
	R::MSG_CONFIRM_DEMO = wxT("All current data will be replaced by demo data. A backup copy is kept in the data folder. Continue?");
	R::MSG_CONFIRM_DELETE = wxT("All data will be deleted. A backup copy is kept in the data folder. Continue?");
	R::MSG_RESTART = wxT("The MiniPlaner will now close. Please start it again.");
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
	R::SPEICHERN_XLSX = wxT("Save as Excel file");
	R::SPALTEN = wxT("Columns");
	R::NUM = wxT("No.");
	R::MESSDIENERLISTE = wxT("Volunteer List");
	R::MESSDIENERLISTE_SH = wxT("VolunteerList");
	//Import
	R::IMPORT = wxT("Import");
	R::IMPORTIEREN = wxT("Import");
	R::SEPARATOR = wxT("Separator");
	R::CSV_DATEI_WAEHLEN = wxT("Choose CSV file");
	R::MI_PAGE_EXPORT = wxT("Export data for the MiniInterface form");
	R::MI_PAGE_IMPORT = wxT("Create plan from MiniInterface form data");
	R::MI_PULL = wxT("Load data from clipboard");
	R::MI_PULL_OK = wxT("Data processed successfully!");
	R::MI_PULL_ERR = wxT("Clipboard data could not be processed correctly!");
	R::MELDUNG = wxT("Message");
	R::FEHLER_T = wxT("Error");
	R::DATEI_SPEICHERN = wxT("Save file");
	R::UPDATE_TITLE = wxT("Update information");
	R::UPDATE_MSG = wxT("A newer version of the program is available.");
	R::UPDATE_DOWNLOAD = wxT("Go to download");
	R::TMODUS_N_WOECHENTLICH = wxT("Every %i weeks on %s, starting (incl.) the week after [start date]");
	R::CSV_FILTER = wxT("CSV files (*.csv)|*.csv|All (*.*)|*.*");
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
	R::BEITRAGENDE = wxT("Contributors: ");
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
	R::MSG_MANUAL_NOT_OPENED = wxT("Could not open the manual in the browser: https://yannikschaelte.github.io/MiniPlaner/Handbuch.pdf");
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

const int R::VERSION_NUMBER = 4;//need number for comparison

wxString R::window_size = wxT("");