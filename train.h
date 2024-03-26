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
T_List *clearAllCells(T_List *list);
void clearVipCell(T_List *list);
void moveVipLeft(T_List *list);
void moveVipRight(T_List *list);
void insertCellRight(T_List *list, char info);
void insertCellLeft(T_List *list, FILE *file, char info);
void writeToVipCell(T_List *list, char info);
void fprintfList(T_List *list, FILE *file);
void fprintfVipCell(T_List *list, FILE *file);
void printfList(T_List *list);
void freeList(T_List *list);

#endif //SDA_TEMA1_TRAIN_H
