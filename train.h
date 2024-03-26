#ifndef SDA_TEMA1_TRAIN_H
#define SDA_TEMA1_TRAIN_H
#include <stdlib.h>
#include <stdio.h>

typedef struct cell {
    char info;
    struct cell *prev, *next;
} T_Cell;

typedef struct {
    T_Cell *head, *vip;
    int length;
} T_List;

T_List *initList();
T_Cell *createCell();
void insertCellRight(T_List *list, char info);
void insertCellLeft(T_List *list, char info);
void writeToCellVIP(T_List *list, char info);
void fprintList(T_List *list, FILE *file);
void fprintListVIP(T_List *list, FILE *file);
void printList(T_List *list);
void deleteList(T_List *list);

#endif //SDA_TEMA1_TRAIN_H
