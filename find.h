#ifndef FIND_H
#define FIND_H

#include "list.h"
#include "stats.h"

/* Struktur zur Definition der Suchkriterien */
typedef struct {
    char *name;       /* Gesuchter Substring im Dateinamen (NULL = alle) */
    char type;        /* 'f' für reguläre Dateien, 'd' für Verzeichnisse, 0 = beide */
    int use_threads;  /* 1, wenn parallele Verarbeitung (Threads) genutzt werden soll */
    int verbose;      /* 1, wenn zusätzliche Ausgaben gewünscht sind */
} SearchCriteria;

/* Durchsucht rekursiv das Verzeichnis 'dirpath' nach Dateien/Verzeichnissen,
   die den Suchkriterien entsprechen, und speichert die Ergebnisse in 'results'.
   Dabei werden auch Statistiken in 'stats' erfasst. */
void search_directory(const char *dirpath, const SearchCriteria *criteria, List *results, Stats *stats);

#endif

