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
} ThreadArg;

/* Prototyp der Thread-Funktion */
void *thread_search_directory(void *arg);

/* Prüft, ob ein Pfad den Suchkriterien entspricht */
static int match_criteria(const char *path, const char *filename, const SearchCriteria *criteria, struct stat *sb) {
    (void)path;  // Markiert 'path' als unbenutzt, um Warnungen zu unterdrücken

    if (criteria->type == 'f') {
        if (!S_ISREG(sb->st_mode))
            return 0;
    } else if (criteria->type == 'd') {
        if (!S_ISDIR(sb->st_mode))
            return 0;
    }
    if (criteria->name != NULL) {
        if (strstr(filename, criteria->name) == NULL)
            return 0;
    }
    return 1;
}

void search_directory(const char *dirpath, const SearchCriteria *criteria, List *results) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        fprintf(stderr, "Cannot open directory: %s (%s)\n", dirpath, strerror(errno));
        return;
    }

    struct dirent *entry;
    pthread_t threads[256];
    int thread_count = 0;
    ThreadArg thread_args[256];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", dirpath, entry->d_name);

        struct stat sb;
        if (lstat(fullpath, &sb) == -1) {
            perror("lstat");
            continue;
        }

        if (S_ISDIR(sb.st_mode)) {
            if (match_criteria(fullpath, entry->d_name, criteria, &sb)) {
                list_add(results, fullpath);
            }
            if (criteria->use_threads) {
                ThreadArg *targ = &thread_args[thread_count];
                targ->dirpath = strdup(fullpath);
                if (!targ->dirpath) { perror("strdup"); exit(EXIT_FAILURE); }
                targ->criteria = criteria;
                targ->results = results;
                if (pthread_create(&threads[thread_count], NULL, thread_search_directory, targ) != 0) {
                    fprintf(stderr, "Failed to create thread for %s\n", fullpath);
                    free(targ->dirpath);
                } else {
                    thread_count++;
                }
            } else {
                search_directory(fullpath, criteria, results);
            }
        } else {
            if (match_criteria(fullpath, entry->d_name, criteria, &sb)) {
                list_add(results, fullpath);
            }
        }
    }
    closedir(dir);

    if (criteria->use_threads) {
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

void *thread_search_directory(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    search_directory(targ->dirpath, targ->criteria, targ->results);
    free(targ->dirpath);
    return NULL;
}

