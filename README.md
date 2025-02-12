
# System-oriented Programming - Portfolio Assignment 05

## Projektbeschreibung

Dieses Projekt implementiert einen eingeschränkten `find`-Befehl, der rekursiv Verzeichnisse durchsucht und Dateien sowie Verzeichnisse anhand verschiedener Suchkriterien filtert. Neben den Basisfunktionen bietet das Programm erweiterte Features wie parallele Verarbeitung (Threading), Logging, Begrenzung der Rekursionstiefe und das Überspringen versteckter Dateien.

## Features

- **Namenssuche:** Filtert Dateien/Verzeichnisse, deren Namen einen bestimmten Substring enthalten.
- **Typfilter:** Wählen Sie zwischen Dateien (`f`) und Verzeichnissen (`d`).
- **Threading:** Optionale parallele Verarbeitung von Unterverzeichnissen zur Verbesserung der Performance.
- **Maximale Rekursionstiefe:** Mit `-maxdepth <n>` können Sie die Tiefe der Verzeichnissuche begrenzen.
- **Hidden-Filter:** Mit `-skip-hidden` werden alle versteckten Dateien und Verzeichnisse (Namen, die mit `.` beginnen) übersprungen.
- **Logging:** Treffer werden in eine Logdatei geschrieben, falls diese Option genutzt wird.
- **Verbose-Ausgabe:** Mit `-verbose` werden zusätzliche Meldungen und Statistiken während der Ausführung ausgegeben.

## Kommandozeilenoptionen

| Option              | Beschreibung                                                                           | Standardwert/Anmerkung                   |
|---------------------|----------------------------------------------------------------------------------------|------------------------------------------|
| `-path <directory>` | Gibt das Startverzeichnis für die Suche an.                                            | Standard: `.` (aktuelles Verzeichnis)     |
| `-name <pattern>`   | Filtert nach einem Substring im Dateinamen.                                            | Standard: kein Namensfilter              |
| `-type <f\|d>`      | Beschränkt die Suche auf Dateien (`f`) oder Verzeichnisse (`d`).                       | Standard: beide (kein Filter)            |
| `-maxdepth <n>`     | Legt die maximale Tiefe der rekursiven Suche fest.                                       | Standard: `-1` (keine Begrenzung)          |
| `-skip-hidden`      | Überspringt alle versteckten Dateien und Verzeichnisse (Namen beginnen mit `.`).         | Standard: deaktiviert (ohne Angabe aktiv)|
| `-threads`          | Aktiviert die parallele Verarbeitung mittels Threads.                                  | Standard: deaktiviert                    |
| `-log <filename>`   | Schreibt Treffer in die angegebene Logdatei.                                             | Standard: kein Logging                   |
| `-verbose`          | Gibt zusätzliche Meldungen und Statistiken aus.                                          | Standard: deaktiviert                    |

## Build und Ausführung

### Build-Anleitung

Öffnen Sie ein Terminal im Projektverzeichnis und führen Sie folgenden Befehl aus, um das Projekt zu kompilieren:

```
make all
```

Dies erzeugt das ausführbare Programm `find`.

### Ausführungsbeispiel

Um das Programm mit verschiedenen Optionen zu starten, können Sie beispielsweise folgenden Befehl verwenden:

```
./find -path /tmp -name test -type f -maxdepth 3 -skip-hidden -threads -log logfile.txt -verbose
```

Dieser Befehl führt Folgendes aus:
- Startet im Verzeichnis `/tmp`.
- Filtert nach Dateien, deren Name den Substring `test` enthält.
- Beschränkt die rekursive Suche auf 3 Ebenen.
- Überspringt versteckte Dateien und Verzeichnisse.
- Verwendet Threads für die parallele Suche.
- Schreibt Treffer in die Logdatei `logfile.txt`.
- Gibt zusätzliche Meldungen und Statistiken aus.

## Testfälle

Ein einfacher Testlauf kann mit folgendem Befehl gestartet werden:

```
make test
```

Dieser Befehl führt das Programm mit vordefinierten Optionen aus, um die Funktionalität zu überprüfen.

## Verzeichnisstruktur

- **`main.c`**  
  Enthält das Hauptprogramm und die Verarbeitung der Kommandozeilenargumente.

- **`find.c` / `find.h`**  
  Implementiert die rekursive Verzeichnissuche und verarbeitet die Suchkriterien.

- **`stats.c` / `stats.h`**  
  Zuständig für die Erfassung von Suchstatistiken (Anzahl gescannter Verzeichnisse, Dateien, Treffer und Fehler).

- **`list.c` / `list.h`**  
  Implementiert eine dynamische, verkettete Liste zur Speicherung der gefundenen Dateipfade.

- **`log.c` / `log.h`**  
  Bietet Funktionen zur Ausgabe von Lognachrichten in eine Logdatei.

- **`Makefile`**  
  Steuert den Build-Prozess (Erzeugen der ausführbaren Datei, Aufräumen und Ausführen von Tests).

## Abhängigkeiten

- **Compiler:** GCC (mit Unterstützung für C99)
- **Bibliotheken:** POSIX-Threads (pthread), Standard-C-Bibliotheken

