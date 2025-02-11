#ifndef STATS_H
#define STATS_H

#include <pthread.h>

/* Struktur zur Erfassung von Such-Statistiken */
typedef struct Stats {
    unsigned long total_dirs;
    unsigned long total_files;
    unsigned long total_matches;
    unsigned long total_errors;
    pthread_mutex_t mutex;
} Stats;

/* Initialisiert die Statistik-Struktur */
void stats_init(Stats *stats);

/* Zerstört die Statistik-Struktur und gibt Ressourcen frei */
void stats_destroy(Stats *stats);

/* Aktualisiert die Statistik beim Scannen eines Verzeichnisses */
void stats_update_dir(Stats *stats);

/* Aktualisiert die Statistik beim Scannen einer Datei */
void stats_update_file(Stats *stats);

/* Aktualisiert die Statistik bei einem Treffer */
void stats_update_match(Stats *stats);

/* Aktualisiert die Statistik bei einem Fehler */
void stats_update_error(Stats *stats);

/* Gibt die erfassten Statistiken aus */
void stats_print(const Stats *stats);

#endif
