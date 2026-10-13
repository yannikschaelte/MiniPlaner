# MiniPlaner

Software zum effizienten Erstellen hochwertiger Messdienerpläne.

<img src="img/minis64.png" alt="Logo"/>

## Beschreibung

Das Programm **MiniPlaner** ist ein Werkzeug zur Erstellung von Messdienerplänen in Kirchengemeinden und Pfarrverbünden. Es ist sehr übersichtlich gehalten, bietet jedoch vielfältige Einstellungsmöglichkeiten: Messdiener und Termine können auf verschiedene Weisen gruppiert werden, das flexible Dienst-System lässt individuelle Maßlösungen zu und Messdiener können für Zeiträume oder bestimmte Gottesdienste als fehlend eingetragen werden. So kann etwa festgelegt werden, dass zu einem Gottesdienst mindestens ein älterer Messdiener oder jemand, der Weihrauch beherrscht, mit dabei ist, dass Geschwister meist/immer zusammen dienen oder dass niemand sowohl in der Vorabendmesse am Samstag als auch zum Hochamt am Sonntag dienen muss. Man kann viel eingeben, muss aber nicht.

<img src="img/hauptfenster_minis.PNG" width="360" alt="Hauptfenster"/> <img src="img/planer.PNG" width="360" alt="Planer"/>

Nach der Eingabe aller benötigten Daten können schnell Pläne für vorzugebende Zeiträume erstellt werden, interaktiv oder automatisch mittels eines Algorithmus, welcher verschiedene einen gelungenen Plan ausmachenden Faktoren gleichzeitig zu berücksichtigen versucht. Das Programm bietet hierbei verschiedene Kontrollmöglichkeiten und Eingabehilfen an. Der Export der graphisch aufbereiteten fertigen Pläne ist in verschiedenen Formaten möglich - als Excel-Datei, CSV, [Webseite](examples/Ministrantenplan_bsp.html) oder als [PDF-Datei](examples/Ministrantenplan_bsp.pdf) zum Ausdrucken.

Ist bereits eine Liste aller Messdiener in einem Tabellenformat vorhanden, so kann der Import dieser als CSV-Datei die Dateneingabe enorm beschleunigen, ebenso das Verwenden von Serienterminen für periodische Termine.

Ausführliche Informationen zu Bedienung und Funktionsweise finden sich im [Handbuch](Handbuch.pdf)

## Daten

* Version: 2.0.5
* System-Voraussetzungen: Windows, Linux und macOS
* Autor: Yannik Schälte

## Download

Kostenlos und für Windows, Linux und macOS. Rückmeldungen sind herzlich willkommen!

* **Windows**: [MiniPlaner-Setup.exe](https://github.com/yannikschaelte/MiniPlaner/releases/download/v2.0.5/MiniPlaner-Setup.exe) oder [MiniPlaner.exe](https://github.com/yannikschaelte/MiniPlaner/releases/download/v2.0.5/MiniPlaner.exe) (ohne Installation)
* **Linux**: [MiniPlaner-x86_64.AppImage](https://github.com/yannikschaelte/MiniPlaner/releases/download/v2.0.5/MiniPlaner-x86_64.AppImage)
* **macOS**: [MiniPlaner.dmg](https://github.com/yannikschaelte/MiniPlaner/releases/download/v2.0.5/MiniPlaner.dmg)

Beim ersten Start können Sie leer oder mit Beispieldaten beginnen.

## Add-Ons

* **MiniInterface**: Deponieren Sie die Datei [MiniInterface.php](addons/MiniInterface.php) auf Ihrer Gemeinde-Homepage, so können Messdiener über ihren Browser zuhause selbst eintragen, wann sie dienen möchten. Diese Daten können Sie dann im **MiniPlaner** bei der Planerstellung automatisch berücksichtigen lassen (Beispiel: [MiniInterface.dat](examples/MiniInterface.dat)).

## Updates

* 13.10.2026 (2.0.5): Windows, Linux und macOS; Willkommensdialog und Einstellungen; Export als Excel (.xlsx)
* 01.03.2019 (2.0.4): move project to github.com
* 12.10.2016 (2.0.3): several minor error fixes, added "Termin::extras" button and "Mini::bem" attribute, added fill-in-help
* 30.04.2016 (2.0.2): integrated MiniInterface, certain changes of mass data in plan window possible
* 18.02.2016 (2.001): 2 minor error fixes, added "Mini::extras" button
* 11.10.2015 (2.0): initial release

## Hilfe und Kontakt

* [Handbuch](Handbuch.pdf)
* E-Mail: ``yannik.schaelte <at> gmail.com``

## Entwickler

Der Code des **MiniPlaner** ist frei verfügbar auf [https://github.com/yannikschaelte/miniplaner](https://github.com/yannikschaelte/miniplaner).

&copy; 2017 Yannik Schälte. Alle Rechte vorbehalten.
