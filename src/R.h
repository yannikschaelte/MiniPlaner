/* 
 * File:   R.h
 * Author: Yannik
 *
 * Created on August 11, 2015, 4:18 PM
 */

#ifndef R_H
#define	R_H

#include <wx/wx.h>

namespace R {
	//Allgemein
	extern wxString MINI_PLANER;
	extern wxString DIENST_DIALOG;
	extern wxString MINI_DIALOG;
	extern wxString EINZELTERMIN_DIALOG;
	extern wxString SERIENTERMIN_DIALOG;
	extern wxString TERMIN_DIENST_DIALOG;
	extern wxString MGRUPPE_DIALOG;
	extern wxString TGRUPPE_DIALOG;
	extern wxString FEHLZEIT_DIALOG;
	extern wxString PLAN_DIALOG;
	extern wxString TERMIN_DIALOG;
	extern wxString EXPORT_LAYOUT_DIALOG;
	extern wxString MINI_EXPORT_DIALOG;
	extern wxString MINI_IMPORT_DIALOG;
	extern wxString MINI_EXTRAS_DIALOG;
	extern wxString EINZELTERMIN_IMPORT_DIALOG;
	extern wxString SPEICHERN_DIALOG;
	extern wxString LOESCHEN_DIALOG;
	extern wxString PLANER_SETTINGS_DIALOG;

	extern wxString HILFE;
	extern wxString UEBER;
	extern wxString SPRACHE;
	extern wxString KONTAKT_MSG;
	extern wxString EXTRAS;
	extern wxString SEMIKOLON;
	extern wxString KOMMA;
	extern wxString LEERZEICHEN;
	extern wxString ANDERES;

	extern wxString OK;
	extern wxString CANCEL;
	extern wxString ADD;
	extern wxString DEL;
	extern wxString EDT;
	extern wxString JA;
	extern wxString NEIN;

	extern wxString DIENSTE;
	extern wxString MINI;
	extern wxString MINIS;
	extern wxString MGRUPPEN;
	extern wxString TERMINE;
	extern wxString TGRUPPEN;
	extern wxString URLAUB;
	extern wxString FEHLZEITEN;
	extern wxString PLAENE;
	//Adresse
	extern wxString STRASSE_NR;
	extern wxString PLZ_ORT;
	extern wxString TEL;
	extern wxString MOBILE;
	extern wxString EMAIL;
	//Messdiener
	extern wxString NAME;
	extern wxString NACHNAME;
	extern wxString VORNAME;
	extern wxString GEBURTSTAG;
	extern wxString BEM;
	const int MINI_ATTS_NUM = 10;
	extern wxString MINI_ATTS[MINI_ATTS_NUM];
	//Termine
	extern wxString EINZELTERMINE;
	extern wxString SERIENTERMINE;
	extern wxString ANZAHL;
	extern wxString ORT;
	extern wxString DATUM;
	extern wxString ZEIT;
	extern wxString MODUS;
	extern wxString DATUM_BEGINN;
	extern wxString DATUM_ENDE;
	const int TEINZEL_NUM = 6;
	const int TSERIE_NUM = 8;
	extern wxString TEINZEL_ATTS[TEINZEL_NUM];
	extern wxString TSERIE_ATTS[TSERIE_NUM];

	extern wxString SONNTAG;
	extern wxString MONTAG;
	extern wxString DIENSTAG;
	extern wxString MITTWOCH;
	extern wxString DONNERSTAG;
	extern wxString FREITAG;
	extern wxString SAMSTAG;
	extern wxString WOCHENTAGE[7];
	//TModus
	extern wxString TAEGLICH;
	extern wxString WOECHENTLICH;
	extern wxString GERADE_KW;
	extern wxString UNGERADE_KW;
	extern wxString N_WOECHENTLICH;
	extern wxString W_IM_MONAT;
	extern wxString MONATLICH;
	const int TMODI_NUM = 7;
	extern wxString TMODI[TMODI_NUM];
	extern wxString LETZTER;
	extern wxString VORLETZTER;
	extern wxString WOCHENTAG;
	extern wxString TAG;
	extern wxString DATUM_AB;
	extern wxString DATUM_BIS;
	//Gruppen (MGruppe, TGruppe)
	extern wxString GRUPPE;
	extern wxString RESTLISTE;
	extern wxString BEV_GEM;
	extern wxString NUR_GEM;
	extern wxString MGMODI[2];
	extern wxString RESTTERMINE;
	extern wxString TGRUPPE;
	extern wxString PERIODISCH;
	extern wxString NICHT_PERIODISCH;
	const int TGMODI_NUM = 2;
	extern wxString TGMODI[TGMODI_NUM];
	//Dienste
	extern wxString DIENST;
	extern wxString ALLGEMEIN;
	//Fehlzeiten
	extern wxString FEHLZEIT;
	extern wxString ZEITRAUM;
	extern wxString TERMIN;
	extern wxString FEHLZEIT_MODI[3];
	extern wxString VON;
	extern wxString BIS;
	//Pläne
	extern wxString OEFFNEN;
	extern wxString ZURUECK;
	extern wxString WEITER;
	extern wxString EINSAETZE;
	extern wxString MASKE;
	extern wxString AUTOMATISCH;
	extern wxString STOPPEN;
	extern wxString LEEREN;
	extern wxString EXPORT;
	extern wxString SPEICHERN;
	extern wxString DATEN;
	extern wxString EINSTELLUNGEN;
	extern wxString FEHLZEITEN_ANRECHNEN;
	extern wxString FEHLZEITEN_KOMPENSIEREN;
	extern wxString ALG_MINIMUM;
	extern wxString ALG_CHRONO;
	//Export
	extern wxString MESSDIENERPLAN;
	extern wxString MESSDIENERPLAN_SH;
	extern wxString LAYOUT;
	extern wxString VORSCHAU;
	extern wxString MINIS_LAYOUT;
	extern wxString MINIS_LAYOUT_MODI[2];
	extern wxString BASICS_LAYOUT;
	extern wxString BASICS_LAYOUT_MODI[2];
	extern wxString NAMEN_LAYOUT;
	extern wxString NAMEN_LAYOUT_MODI[4];
	extern wxString DATEI_AUSGABE;
	extern wxString CLIPBOARD_AUSGABE;
	extern wxString TITEL;
	extern wxString DIENSTE_ZEIGEN;
	extern wxString SPEICHERN_HTML;
	extern wxString SPEICHERN_CSV;
	extern wxString SPEICHERN_EXCEL_XML;
	extern wxString SPALTEN;
	extern wxString NUM;
	extern wxString MESSDIENERLISTE;
	extern wxString MESSDIENERLISTE_SH;
	//Import
	extern wxString IMPORT;
	extern wxString IMPORTIEREN;
	extern wxString SEPARATOR;
	extern wxString CSV_DATEI_WAEHLEN;
	extern wxString MINI_CSV_MSG;
	extern wxString MINI_IMPORT_MSG;
	extern wxString EINZELTERMIN_CSV_MSG;
	extern wxString EINZELTERMIN_IMPORT_MSG;
	//Extras
	extern wxString EMAILS;
	extern wxString KOPIERTEMAILS;
	extern wxString ADRESSEN;
	extern wxString KOPIERTADRESSEN;
	extern wxString KOPIERTEMAILSFERTIG;
	extern wxString KOPIERTADRESSENFERTIG;
	extern wxString KOPIERTWARNICHTMOEGLICH;
	//Über
	extern wxString HEADLINE;
	extern wxString AUTOR;
	extern wxString KOMPILIERTMIT;
	extern wxString BIBLIOTHEKEN;
	extern wxString INSTALLATIONSVERZEICHNIS;
	//Einstellungen
	extern wxString MSG_LANG_CHANGE_EN;
	extern wxString MSG_LANG_CHANGE_DE;
	//Nachrichten
	extern wxString MSG_MINI_UNIQUE;
	extern wxString MSG_FEHLZEIT_UNIQUE;
	extern wxString MSG_TIME_ERR;
	extern wxString MSG_TIME_BEGINN_ERR;
	extern wxString MSG_TIME_ENDE_ERR;
	extern wxString MSG_WEEK_NUM_ERR;
	extern wxString MSG_WEEK_COUNT_START;
	extern wxString MSG_GROUP_NUM;
	extern wxString MSG_TGROUP_NUM;
	extern wxString MSG_EINZEL_UNIQUE;
	extern wxString MSG_SERIE_UNIQUE;
	extern wxString MSG_DIENST_UNIQUE;
	extern wxString MSG_MINI_SEL_ERR;
	extern wxString MSG_TERMIN_SEL_ERR;
	extern wxString MSG_DIENST_SEL_ERR;
	extern wxString MSG_DATUM_ORDER;
	extern wxString MSG_PLAN_CREATE_IMPOSSIBLE;
	extern wxString MSG_MANUAL_NOT_OPENED;
	extern wxString MSG_FILE_NOT_FOUND;
	extern wxString MSG_RETRIEVE_NOT_POSSIBLE;
	extern wxString MSG_IMPORT_NOT_POSSIBLE;
	extern wxString Q_SPEICHERN;
	extern wxString Q_LOESCHEN;

	void setLangDE();
	void setLangEN();
	void setLang();

	const int LANG_DE = 0;
	const int LANG_EN = 1;
	extern int lang;

	enum {
		ID_ANY,
		ID_LB,
		ID_LC,
		ID_BT_ADD,
		ID_BT_DEL,
		ID_BT_EDT,
		ID_LC2,
		ID_BT_ADD2,
		ID_BT_DEL2,
		ID_BT_EDT2,
		ID_BT_OK,
		ID_BT_CANCEL,
		ID_CH,
		ID_BT_BACK,
		ID_BT_CONT,
		ID_BT_COMPUTE,
		ID_BT_STOP,
		ID_EXPORT,
		ID_IMPORT,
		ID_UNDO,
		ID_REDO
	};

	void setSubWindowPosition(wxWindow* parent, wxDialog* self);

	extern const int VERSION_NUMBER;//need number for comparison

	extern wxString window_size;
};

#endif	/* R_H */