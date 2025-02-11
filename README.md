# SNProjekt

Dies ist die Implementierung eines limitierten Linux-Kommandos, das an die Funktionalität von `find` angelehnt ist.  
Das Projekt wurde im Rahmen des Portfolio Assignments 05 im Modul System-oriented Programming entwickelt.

## Überblick

Das Projekt demonstriert die Entwicklung einer größeren Software in C unter Einsatz folgender Konzepte:
- **Dateisysteminteraktion:** Durchsuchen von Verzeichnissen und Abrufen von Dateiattributen mittels der Linux File API.
- **Kommandozeilenargumente:** Verarbeitung von Benutzerparametern (argc, argv) zur Konfiguration der Programmfunktionalität.
- **Dynamische Datenstrukturen:** Nutzung von verketteten Listen zur Verwaltung der Suchergebnisse.
- **Multithreading:** Optionale parallele Verarbeitung von Verzeichnissen mit POSIX Threads und Synchronisation mittels Mutex.
- **stdin/stdout:** Integration in Pipelines über Standard-Ein- und Ausgabe.
- **Build-Prozess:** Kompilierung mittels gcc und einem Makefile zur Modularität und Einfachheit.

## Projektstruktur

```
.
├── Makefile       # Makefile zum Bauen, Aufräumen und Testen des Projekts
├── main.c         # Hauptprogramm
├── find.c         # Implementierung der Suchlogik
├── find.h         # Header für find.c
├── list.c         # Implementierung der dynamischen Liste
├── list.h         # Header für list.c
└── README.md      # Diese Datei
```

## Build-Anleitung

### Voraussetzungen

- **GCC** (GNU Compiler Collection)
- **GNU Make**
- **POSIX Threads (pthread)**

### Kompilierung

Wechsle in das Projektverzeichnis und führe folgenden Befehl im Terminal aus:

```bash
make
```

Dies erstellt das Executable (z. B. `myfind`).

### Ausführen des Programms

Das Programm kann mit verschiedenen Optionen gestartet werden. Die grundlegende Syntax lautet:

```bash
./myfind -path <Verzeichnis> -name <Muster> -type <f|d> [-threads]
```

**Beispiele:**

- **Suche im aktuellen Verzeichnis** nach Dateien, deren Name den Substring `test` enthält, mit paralleler Verarbeitung:

  ```bash
  ./myfind -path . -name test -type f -threads
  ```

- **Standardaufruf** (ohne spezifische Parameter):

  ```bash
  ./myfind
  ```

### Aufräumen

Um die erzeugten Objektdateien und das Executable zu löschen, führe im Terminal aus:

```bash
make clean
```

## Testfälle

Das Projekt enthält grundlegende Testfälle, die über die Kommandozeilenargumente ausgeführt werden können.
- **Manuelle Tests:** Starte das Programm mit verschiedenen Parameterkombinationen und überprüfe die Ausgabe.
- **Pipelines:** Verwende das Programm in einer Pipeline, z. B.:

  ```bash
  ./myfind -path . -name log | grep error
  ```

Weitere Testanweisungen findest du in der Projektdokumentation (sofern vorhanden).

## Lieferumfang

- **Quellcode:** Alle C-Dateien und das Makefile befinden sich in diesem Repository.
- **Testfälle:** Die grundlegenden Testfälle sind integriert.
- **Screencast Video:** Ein Screencast-Video, in dem technische Aspekte der Implementierung erläutert werden, ist verfügbar unter:  
  [Video-URL hier einfügen]
- **Einreichungsdokument:** Zusätzlich wurde eine Textdatei erstellt, deren erste Zeile den Repository-URL, die zweite Zeile die Video-URL und die dritte Zeile eine kommagetrennte Liste der Immatrikulationsnummern der Teammitglieder enthält.

