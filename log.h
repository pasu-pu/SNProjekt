#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/* Logger-Struktur zum Schreiben in eine Logdatei */
typedef struct Logger {
    FILE *file;
} Logger;

/* Erzeugt einen neuen Logger, der in die angegebene Datei schreibt */
Logger *logger_create(const char *filename);

/* Zerstört den Logger und schließt die Logdatei */
void logger_destroy(Logger *logger);

/* Schreibt eine Lognachricht in die Logdatei */
void logger_log(Logger *logger, const char *message);

#endif
