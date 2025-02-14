#include <stdio.h>
#include "stats.h"

void stats_init(Stats *stats) {
    stats->total_dirs = 0;
    stats->total_files = 0;
    stats->total_matches = 0;
    stats->total_errors = 0;
    pthread_mutex_init(&stats->mutex, NULL);
}

void stats_destroy(Stats *stats) {
    pthread_mutex_destroy(&stats->mutex);
}

void stats_update_dir(Stats *stats) {
    pthread_mutex_lock(&stats->mutex);
    stats->total_dirs++;
    pthread_mutex_unlock(&stats->mutex);
}

void stats_update_file(Stats *stats) {
    pthread_mutex_lock(&stats->mutex);
    stats->total_files++;
    pthread_mutex_unlock(&stats->mutex);
}

void stats_update_match(Stats *stats) {
    pthread_mutex_lock(&stats->mutex);
    stats->total_matches++;
    pthread_mutex_unlock(&stats->mutex);
}

void stats_update_error(Stats *stats) {
    pthread_mutex_lock(&stats->mutex);
    stats->total_errors++;
    pthread_mutex_unlock(&stats->mutex);
}

void stats_print(const Stats *stats) {
    printf("\n--- Suchstatistiken ---\n");
    printf("Verzeichnisse gescannt: %lu\n", stats->total_dirs);
    printf("Dateien gescannt:       %lu\n", stats->total_files);
    printf("Treffer gefunden:       %lu\n", stats->total_matches);
    printf("Fehler aufgetreten:     %lu\n", stats->total_errors);
    printf("-------------------------\n");
}
