#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include "find.h"

/* Struktur, um Parameter an einen Thread zu übergeben */
typedef struct ThreadArg {
    char *dirpath;
    const SearchCriteria *criteria;
    List *results;
    Stats *stats;
    int depth;
    Logger *logger;
} ThreadArg;

/* Prototyp der Thread-Funktion */
void *thread_search_directory(void *arg);

/* Prüft, ob ein Pfad den Suchkriterien entspricht */
static int match_criteria(const char *path, const char *filename, const SearchCriteria *criteria, struct stat *sb) {
    (void)path;  // Nicht genutzt

    /* Filter nach Typ */
    if (criteria->type == 'f') {
        if (!S_ISREG(sb->st_mode))
            return 0;
    } else if (criteria->type == 'd') {
        if (!S_ISDIR(sb->st_mode))
            return 0;
    }
    /* Filter nach Namen */
    if (criteria->name != NULL) {
        if (strstr(filename, criteria->name) == NULL)
            return 0;
    }
    return 1;
}

void search_directory(const char *dirpath, const SearchCriteria *criteria, List *results, Stats *stats, int depth, Logger *logger) {
    /* Falls max_depth gesetzt ist und die maximale Tiefe erreicht wurde */
    if (criteria->max_depth != -1 && depth > criteria->max_depth) {
        return;
    }

    DIR *dir = opendir(dirpath);
    if (!dir) {
        fprintf(stderr, "Kann Verzeichnis nicht öffnen: %s (%s)\n", dirpath, strerror(errno));
        if (stats) stats_update_error(stats);
        return;
    }

    /* Statistik: Verzeichnis wurde gescannt */
    if (stats) stats_update_dir(stats);

    struct dirent *entry;
    pthread_t threads[256];
    int thread_count = 0;
    ThreadArg thread_args[256];

    while ((entry = readdir(dir)) != NULL) {
        /* Überspringe "." und ".." */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        /* Option: überspringe versteckte Einträge */
        if (criteria->skip_hidden && entry->d_name[0] == '.') {
            continue;
        }

        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", dirpath, entry->d_name);

        struct stat sb;
        if (lstat(fullpath, &sb) == -1) {
            perror("lstat");
            if (stats) stats_update_error(stats);
            continue;
        }

        if (S_ISDIR(sb.st_mode)) {
            /* Zähle Verzeichnisse auch als Datei-Eintrag */
            if (stats) stats_update_file(stats);
            if (match_criteria(fullpath, entry->d_name, criteria, &sb)) {
                list_add(results, fullpath);
                if (stats) stats_update_match(stats);
                if (criteria->verbose) {
                    printf("Treffer (Verzeichnis): %s\n", fullpath);
                }
                if (logger) {
                    char log_msg[PATH_MAX + 50];
                    snprintf(log_msg, sizeof(log_msg), "Treffer (Verzeichnis): %s", fullpath);
                    logger_log(logger, log_msg);
                }
            }
            /* Rekursive Suche in Unterverzeichnissen, evtl. in einem neuen Thread */
            if (criteria->use_threads) {
                ThreadArg *targ = &thread_args[thread_count];
                targ->dirpath = strdup(fullpath);
                if (!targ->dirpath) {
                    perror("strdup");
                    exit(EXIT_FAILURE);
                }
                targ->criteria = criteria;
                targ->results = results;
                targ->stats = stats;
                targ->depth = depth + 1;
                targ->logger = logger;
                if (pthread_create(&threads[thread_count], NULL, thread_search_directory, targ) != 0) {
                    fprintf(stderr, "Fehler beim Erstellen eines Threads für %s\n", fullpath);
                    free(targ->dirpath);
                } else {
                    thread_count++;
                }
            } else {
                search_directory(fullpath, criteria, results, stats, depth + 1, logger);
            }
        } else {
            if (stats) stats_update_file(stats);
            if (match_criteria(fullpath, entry->d_name, criteria, &sb)) {
                list_add(results, fullpath);
                if (stats) stats_update_match(stats);
                if (criteria->verbose) {
                    printf("Treffer (Datei): %s\n", fullpath);
                }
                if (logger) {
                    char log_msg[PATH_MAX + 50];
                    snprintf(log_msg, sizeof(log_msg), "Treffer (Datei): %s", fullpath);
                    logger_log(logger, log_msg);
                }
            }
        }
    }
    closedir(dir);

    /* Warte auf alle gestarteten Threads */
    if (criteria->use_threads) {
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

void *thread_search_directory(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    search_directory(targ->dirpath, targ->criteria, targ->results, targ->stats, targ->depth, targ->logger);
    free(targ->dirpath);
    return NULL;
}
