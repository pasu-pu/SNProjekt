#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find.h"
#include "list.h"
#include "stats.h"

void print_usage(const char *progname) {
    printf("Usage: %s [-path <directory>] [-name <pattern>] [-type <f|d>] [-threads] [-verbose]\n", progname);
}

int main(int argc, char *argv[]) {
    char *start_path = ".";
    char *name_pattern = NULL;
    char type = 0;      /* 0 = beide, d.h. weder auf Dateien noch auf Verzeichnisse beschränkt */
    int use_threads = 0;
    int verbose = 0;

    /* Einfaches Parsen der Kommandozeilenargumente */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-path") == 0 && i+1 < argc) {
            start_path = argv[++i];
        } else if (strcmp(argv[i], "-name") == 0 && i+1 < argc) {
            name_pattern = argv[++i];
        } else if (strcmp(argv[i], "-type") == 0 && i+1 < argc) {
            if (argv[i+1][0] == 'f' || argv[i+1][0] == 'd') {
                type = argv[++i][0];
            } else {
                fprintf(stderr, "Invalid type option. Use 'f' for file or 'd' for directory.\n");
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "-threads") == 0) {
            use_threads = 1;
        } else if (strcmp(argv[i], "-verbose") == 0) {
            verbose = 1;
        } else {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    SearchCriteria criteria;
    criteria.name = name_pattern;
    criteria.type = type;
    criteria.use_threads = use_threads;
    criteria.verbose = verbose;

    List *results = list_create();

    /* Initialisiere Statistik-Struktur */
    Stats stats;
    stats_init(&stats);

    search_directory(start_path, &criteria, results, &stats);

    list_print(results);

    if (verbose) {
        stats_print(&stats);
    }

    stats_destroy(&stats);
    list_destroy(results);
    return 0;
}

