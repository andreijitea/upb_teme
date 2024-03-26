#include "train.h"
#include <stdlib.h>
#include <stdio.h>

T_List *initList() {
    T_List *list = malloc(sizeof(T_List));
    // Create the head of the list (locomotiva)
    list->head = (T_Cell*) malloc(sizeof(T_Cell));
    if (list->head == NULL)
        return NULL;
    // Create first "real" node of the list (primul vagon)
    T_Cell *aux = createCell();
    if (aux == NULL)
        return NULL;
    // Connect the head with the first cell
    list->head->next = aux;
    list->head->prev = aux;
    aux->next = list->head;
    aux->prev = list->head;

    // Set the "VIP" pointer (locatia mecanicului)
    list->vip = aux;
    // Set the length of the list (1 locomotiva + 1 vagon)
    list->length = 2;
    return list;
}

T_Cell *createCell() {
    T_Cell *aux = (T_Cell*) malloc(sizeof(T_Cell));
    aux->info = '#';
    aux->next = NULL;
    aux->prev = NULL;
    return aux;
}

void insertCellRight(T_List *list, char info) {
    // Increment the list length
    list->length++;
    // Create the new cell and set its value
    T_Cell *aux = createCell();
    aux->info = info;
    // Make the connections between the new cell and the existing ones
    list->vip->next = aux;
    aux->next = list->head;
    aux->prev = list->vip;
    list->head->prev = aux;
    // Move the "vip" to the new cell
    list->vip = aux;
    return;
}

void insertCellLeft(T_List *list, char info) {
    // Increment the list length
    list->length++;
    // Create the new cell and set its value
    T_Cell *aux = createCell();
    aux->info = info;
    // Make the connections between the new cell and the existing ones
    list->vip->prev->next = aux;
    aux->prev = list->vip->prev;
    list->vip->prev = aux;
    aux->next = list->vip;
    // Move the "vip" to the new cell
    list->vip = aux;
    return;
}

void writeToCellVIP(T_List *list, char info) {
    list->vip->info = info;
    return;
}

void fprintList(T_List *list, FILE *file) {
    // Set a pointer to the first "real" cell (primul vagon)
    T_Cell *crt = list->head->next;
    for (int i = 1; i < list->length; i++) {
        // Prints the cells the "vip" does not point to (vagoanele in care nu se afla mecanicul)
        if (crt != list->vip) {
            fprintf(file, "%c", crt->info);
            continue;
        }
        // Prints the cell the "vip" points to (vagonul in care se afla mecanicul)
        fprintf(file, "|%c|", crt->info);

        crt = crt->next;
    }
    return;
}

void fprintListVIP(T_List *list, FILE *file) {
    fprintf(file, "%c", list->vip->info);
    return;
}

// Only for debugging purposes... Delete at the end!
void printList(T_List *list) {
    // Set a pointer to the first "real" cell (primul vagon)
    T_Cell *crt = list->head->next;
    for (int i = 1; i < list->length; i++) {
        // Prints the cells the "vip" does not point to (vagoanele in care nu se afla mecanicul)
        if (crt != list->vip) {
            printf("%c", crt->info);
            crt = crt->next;
            continue;
        }
        // Prints the cell the "vip" points to (vagonul in care se afla mecanicul)
        printf("|%c|", crt->info);
        crt = crt->next;
    }
    printf("\n");
    return;
}

void deleteList(T_List *list) {
    // Set a pointer to the head of the list (locomotiva)
    T_Cell *crt = list->head;
    // Break connections between the head and last cell, resulting a linear doubly linked list
    list->head->prev->next = NULL;
    list->head->prev = NULL;

    // Delete every cell one by one
    while (crt != NULL) {
        T_Cell *aux = crt;
        crt = crt->next;
        free(aux);
    }
    // Delete the list structure
    free(list);
    return;
}