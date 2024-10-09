/* JITEA Andrei-Petru - 315CB */

#ifndef SDA_TEMA1_TRAIN_LIST_H
#define SDA_TEMA1_TRAIN_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lcell {
	char info;
	struct lcell *prev, *next;
} T_LCell;

typedef struct {
	T_LCell *head, *vip;
	int length;
} T_List;

T_List *initList();
T_LCell *createLCell();

T_List *clearAllLCells(T_List *list);
T_List *clearVipLCell(T_List *list);

void freeList(T_List *list);

void moveVipLeft(T_List *list);
void moveVipRight(T_List *list);

void insertLCellRight(T_List *list, char info);
void insertLCellLeft(T_List *list, char info, FILE *file);

void writeToVipLCell(T_List *list, char info);

void fprintfList(T_List *list, FILE *file);
void fprintfVipLCell(T_List *list, FILE *file);

void search(T_List *list, char* word, FILE *file);
void searchLeft(T_List *list, char* word, FILE *file);
void searchRight(T_List *list, char* word, FILE *file);


void printfList(T_List *list);

#endif
