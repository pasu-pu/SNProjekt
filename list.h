#ifndef LIST_H
#define LIST_H

#include <pthread.h>

/* Knoten einer verketteten Liste, die einen Dateipfad speichert */
typedef struct Node {
    char *path;
    struct Node *next;
} Node;

/* Die Liste selbst mit einem Mutex zur Synchronisation */
typedef struct {
    Node *head;
    Node *tail;
    pthread_mutex_t mutex;
} List;

/* Erzeugt eine neue, leere Liste */
List *list_create();

/* Zerstört die Liste und gibt den allokierten Speicher frei */
void list_destroy(List *list);

/* Fügt einen neuen Eintrag (Dateipfad) an die Liste an */
void list_add(List *list, const char *path);

/* Gibt den Inhalt der Liste (alle Pfade) auf stdout aus */
void list_print(const List *list);

#endif

