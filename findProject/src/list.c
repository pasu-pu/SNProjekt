#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"

List *list_create() {
    List *list = malloc(sizeof(List));
    if (!list) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    list->head = list->tail = NULL;
    pthread_mutex_init(&list->mutex, NULL);
    return list;
}

void list_destroy(List *list) {
    if (!list)
        return;
    Node *current = list->head;
    while (current) {
        Node *tmp = current;
        current = current->next;
        free(tmp->path);
        free(tmp);
    }
    pthread_mutex_destroy(&list->mutex);
    free(list);
}

void list_add(List *list, const char *path) {
    if (!list || !path)
        return;
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->path = strdup(path);
    if (!node->path) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    node->next = NULL;

    pthread_mutex_lock(&list->mutex);
    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    pthread_mutex_unlock(&list->mutex);
}

void list_print(const List *list) {
    if (!list)
        return;
    printf("----- Gefundene Treffer -----\n");
    Node *current = list->head;
    while (current) {
        printf("  - %s\n", current->path);
        current = current->next;
    }
    printf("----- Ende der Trefferliste -----\n");
}

