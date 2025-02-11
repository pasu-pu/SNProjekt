#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find.h"
#include "list.h"
#include "stats.h"
#include "log.h"

/* Ausgabe der Programmusage */
void print_usage(const char *progname) {
    printf("Usage: %s [OPTIONS]\n", progname);
    printf("Options:\n");
    printf("  -path <directory>    Startverzeichnis (Standard: .)\n");
    printf("  -name <pattern>      Suchpattern (Substring im Namen)\n");
    printf("  -type <f|d>          Typfilter: 'f' für Dateien, 'd' für Verzeichnisse\n");
    printf("  -maxdepth <n>        Maximale Rekursionstiefe (Standard: -1, keine Begrenzung)\n");
    printf("  -skip-hidden         Versteckte Dateien/Verzeichnisse überspringen\n");
    printf("  -threads             Parallele Verarbeitung mit Threads\n");
    printf("  -log <filename>      Logdatei zum Speichern von Treffer-Ergebnissen\n");
    printf("  -verbose             Zusätzliche Ausgaben und Statistiken\n");
}

int main(int argc, char *argv[]) {
    char *start_path = ".";
    char *name_pattern = NULL;
    char type = 0;      /* 0 = beide, d.h. kein Filter */
    int use_threads = 0;
    int verbose = 0;
    int max_depth = -1; /* -1 bedeutet keine Begrenzung */
    int skip_hidden = 0;
    char *log_filename = NULL;
    Logger *logger = NULL;

    /* Kommandozeilenargumente parsen */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-path") == 0 && i+1 < argc) {
            start_path = argv[++i];
        } else if (strcmp(argv[i], "-name") == 0 && i+1 < argc) {
            name_pattern = argv[++i];
        } else if (strcmp(argv[i], "-type") == 0 && i+1 < argc) {
            if (argv[i+1][0] == 'f' || argv[i+1][0] == 'd') {
                type = argv[++i][0];
            } else {
                fprintf(stderr, "Ungültiger Typ. Verwende 'f' für Dateien oder 'd' für Verzeichnisse.\n");
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "-maxdepth") == 0 && i+1 < argc) {
            max_depth = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-skip-hidden") == 0) {
            skip_hidden = 1;
        } else if (strcmp(argv[i], "-threads") == 0) {
            use_threads = 1;
        } else if (strcmp(argv[i], "-log") == 0 && i+1 < argc) {
            log_filename = argv[++i];
        } else if (strcmp(argv[i], "-verbose") == 0) {
            verbose = 1;
        } else {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    /* Konfiguration der Suchkriterien */
    SearchCriteria criteria;
    criteria.name = name_pattern;
    criteria.type = type;
    criteria.use_threads = use_threads;
    criteria.verbose = verbose;
    criteria.max_depth = max_depth;
    criteria.skip_hidden = skip_hidden;
    criteria.logfile = log_filename;

    if (log_filename != NULL) {
        logger = logger_create(log_filename);
    }

    List *results = list_create();

    Stats stats;
    stats_init(&stats);

    /* Starte die rekursive Suche mit Anfangstiefe 0 */
    search_directory(start_path, &criteria, results, &stats, 0, logger);

    /* Ausgabe der gefundenen Ergebnisse */
    list_print(results);

    if (verbose) {
        stats_print(&stats);
    }

    if (logger) {
        logger_destroy(logger);
    }

    stats_destroy(&stats);
    list_destroy(results);

    return 0;
}
