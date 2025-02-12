#ifndef FIND_H
#define FIND_H

#include "list.h"
#include "stats.h"
#include "log.h"

/* Struktur zur Definition der Suchkriterien */
typedef struct {
    char *name;       /* Gesuchter Substring im Dateinamen (NULL = alle) */
    char type;        /* 'f' für Dateien, 'd' für Verzeichnisse, 0 = beide */
    int use_threads;  /* 1, wenn parallele Verarbeitung (Threads) genutzt werden soll */
    int verbose;      /* 1, wenn zusätzliche Ausgaben gewünscht sind */
    int max_depth;    /* Maximale Rekursionstiefe (-1 = keine Begrenzung) */
    int skip_hidden;  /* 1, wenn versteckte Dateien/Verzeichnisse übersprungen werden sollen */
    char *logfile;    /* Dateiname für Log-Ausgaben (NULL = kein Logging) */
} SearchCriteria;

/* Durchsucht rekursiv das Verzeichnis 'dirpath' nach Dateien/Verzeichnissen,
   die den Suchkriterien entsprechen, und speichert die Ergebnisse in 'results'.
   Dabei werden auch Statistiken in 'stats' erfasst.
   'depth' gibt die aktuelle Rekursionstiefe an.
   'logger' ist optional für Log-Ausgaben. */
void search_directory(const char *dirpath, const SearchCriteria *criteria, List *results, Stats *stats, int depth, Logger *logger);

#endif
