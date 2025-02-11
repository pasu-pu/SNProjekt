#include "log.h"
#include <stdio.h>
#include <stdlib.h>

Logger *logger_create(const char *filename) {
    Logger *logger = malloc(sizeof(Logger));
    if (!logger) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    logger->file = fopen(filename, "w");
    if (!logger->file) {
        perror("fopen");
        free(logger);
        exit(EXIT_FAILURE);
    }
    return logger;
}

void logger_destroy(Logger *logger) {
    if (logger) {
        if (logger->file) {
            fclose(logger->file);
        }
        free(logger);
    }
}

void logger_log(Logger *logger, const char *message) {
    if (logger && logger->file) {
        fprintf(logger->file, "%s\n", message);
        fflush(logger->file);
    }
}
