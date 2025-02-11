#ifndef STATS_H
#define STATS_H

#include <pthread.h>

typedef struct Stats {
    unsigned long total_dirs;
    unsigned long total_files;
    unsigned long total_matches;
    unsigned long total_errors;
    pthread_mutex_t mutex;
} Stats;

void stats_init(Stats *stats);
void stats_destroy(Stats *stats);
void stats_update_dir(Stats *stats);
void stats_update_file(Stats *stats);
void stats_update_match(Stats *stats);
void stats_update_error(Stats *stats);
void stats_print(const Stats *stats);

#endif

