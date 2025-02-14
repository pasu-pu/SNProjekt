
# System-oriented Programming - Portfolio Assignment 05

## Projektübersicht

Dieses Projekt implementiert einen eingeschränkten Linux-`find`-Befehl in C. Das Programm durchsucht rekursiv Verzeichnisse und filtert Dateien sowie Verzeichnisse anhand verschiedener Kriterien. Neben den Basisfunktionen demonstriert das Projekt den Einsatz von dynamischen Datenstrukturen, Multithreading mit Synchronisation, Logging sowie die Verarbeitung von Kommandozeilenargumenten.

## Features

- **Namenssuche:**  
  Filtert Dateien und Verzeichnisse, deren Namen einen bestimmten Substring enthalten.

- **Typfilter:**  
  Begrenzen Sie die Suche auf Dateien (`-type f`) oder Verzeichnisse (`-type d`).

- **Multithreading:**  
  Optionale parallele Verarbeitung von Unterverzeichnissen mittels Threads zur Verbesserung der Performance.

- **Maximale Rekursionstiefe:**  
  Mit `-maxdepth <n>` können Sie die Tiefe der Verzeichnissuche begrenzen.

- **Hidden-Filter:**  
  Mit `-skip-hidden` werden alle versteckten Dateien und Verzeichnisse (Namen, die mit `.` beginnen) übersprungen.

- **Logging:**  
  Treffer können in eine Logdatei geschrieben werden, wenn die Option `-log <filename>` verwendet wird.

- **Verbose-Ausgabe:**  
  Mit `-verbose` werden zusätzliche Meldungen und Suchstatistiken (z. B. Anzahl gescannter Verzeichnisse, Dateien, Treffer und Fehler) ausgegeben.

## Kommandozeilenoptionen

| Option              | Beschreibung                                                                 | Standard/Anmerkung                    |
|---------------------|------------------------------------------------------------------------------|---------------------------------------|
| `-path <directory>` | Gibt das Startverzeichnis für die Suche an.                                  | Standard: `.` (aktuelles Verzeichnis)  |
| `-name <pattern>`   | Filtert nach einem Substring im Dateinamen.                                  | Kein Filter (falls nicht angegeben)    |
| `-type <f\|d>`       | Beschränkt die Suche auf Dateien (`f`) oder Verzeichnisse (`d`).             | Standard: beide (kein Filter)          |
| `-maxdepth <n>`     | Legt die maximale Tiefe der rekursiven Suche fest.                           | Standard: `-1` (keine Begrenzung)        |
| `-skip-hidden`      | Überspringt versteckte Dateien und Verzeichnisse (Namen beginnen mit `.`).     | Standard: deaktiviert                  |
| `-threads`          | Aktiviert die parallele Verarbeitung mittels Threads.                      | Standard: deaktiviert                  |
| `-log <filename>`   | Schreibt Treffer in die angegebene Logdatei.                                 | Standard: kein Logging                 |
| `-verbose`          | Gibt zusätzliche Meldungen und Suchstatistiken aus.                        | Standard: deaktiviert                  |

## Build und Ausführung

### Build-Anleitung


Öffnen Sie ein Terminal im Projekt findProject Verzeichniss und führen Sie den folgenden Befehl aus:

```bash
make all
```

Dies kompiliert den Quellcode mithilfe von GCC und erzeugt das ausführbare Programm `find`.

### Ausführungsbeispiel

Ein Beispielaufruf des Programms:

```bash
./find -path /tmp -name test -type f -maxdepth 3 -skip-hidden -threads -log logfile.txt -verbose
```

Dieser Befehl:
- Startet im Verzeichnis `/tmp`
- Filtert nach Dateien, deren Name den Substring `test` enthält
- Beschränkt die rekursive Suche auf 3 Ebenen
- Überspringt versteckte Dateien und Verzeichnisse
- Verwendet Threads zur parallelen Verarbeitung
- Schreibt Treffer in die Logdatei `logfile.txt`
- Gibt zusätzliche Meldungen und Suchstatistiken aus

### Testfälle

Ein einfaches automatisiertes Testverfahren ist integriert. Um die Testfälle auszuführen, geben Sie im Terminal Folgendes ein:

```bash
make test
```

Dies führt das Skript `tests/run_tests.sh` aus, welches die Ausgabe des Programms mit den in `tests/expected` definierten Ergebnissen vergleicht.

## Verzeichnisstruktur

```
project-root/
├── README.md         # Diese Datei: Enthält Projektbeschreibung, Build- und Ausführungsanweisungen
├── Makefile          # Build-Skript (verwendet GCC zur Kompilierung)
├── src/              # Quellcode des Projekts
│   ├── main.c        # Hauptprogramm: Kommandozeilenargumentverarbeitung und Programmstart
│   ├── find.c        # Implementierung der rekursiven Verzeichnissuche
│   ├── find.h        # Header für find.c
│   ├── list.c        # Implementierung einer dynamischen, verketteten Liste zur Speicherung von Suchergebnissen
│   ├── list.h        # Header für list.c
│   ├── stats.c       # Erfassung von Suchstatistiken
│   ├── stats.h       # Header für stats.c
│   ├── log.c         # Logging-Funktionalität
│   └── log.h         # Header für log.c
└── tests/            # Testressourcen und Testskripte
    ├── run_tests.sh  # Shell-Skript zur Ausführung automatisierter Tests
    ├── test_input/   # Beispielverzeichnisse und Dateien als Eingabedaten für Tests
    └── expected/     # Erwartete Ausgabedateien für die Testfälle
```

## Abhängigkeiten

- **Compiler:** GCC (mit Unterstützung für C99)
- **Bibliotheken:**  
  - POSIX Threads (`pthread`)
  - Standard C-Bibliotheken


