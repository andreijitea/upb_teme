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

T_List *clearAllCells(T_List *list) {
    freeList(list);
    T_List *new_list = initList();
    return new_list;
}

void clearVipCell(T_List *list) {
    // Decrement the length of the list by one
    list->length--;
    // Reset the list if it has only one cell
    if (list->length == 1) {
        list = initList();
        return;
    }
    // Remake connections between cells
    T_Cell *aux = list->vip;
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    // Move the VIP to the left
    moveVipLeft(list);

    // Free the cleared cell
    free(aux);
    return;
}

void moveVipRight(T_List *list) {
    // If the VIP is at the end of the list, insert a new cell to the right
    if (list->vip->next == list->head) {
        insertCellRight(list, '#');
        return;
    }
    // Move the VIP to the right one cell
    list->vip = list->vip->next;
    return;
}
void moveVipLeft(T_List *list) {
    // If the VIP is at the first "real" cell, go to the end
    if (list->vip->prev == list->head) {
        list->vip = list->head->prev;
        return;
    }
    // Move the VIP to the left one cell
    list->vip = list->vip->prev;
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

void insertCellLeft(T_List *list, FILE *file, char info) {
    // Check if VIP is on the first cell
    if (list->vip->prev == list->head) {
        // Delete printf when done
        printf("ERROR\n");
        fprintf(file, "ERROR\n");
        return;
    }
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

void writeToVipCell(T_List *list, char info) {
    list->vip->info = info;
    return;
}

void fprintfList(T_List *list, FILE *file) {
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
    fprintf(file, "\n");
    return;
}

void fprintfVipCell(T_List *list, FILE *file) {
    fprintf(file, "%c\n", list->vip->info);
    return;
}

void freeList(T_List *list) {
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

// Only for debugging purposes... Delete at the end!
void printfList(T_List *list) {
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

