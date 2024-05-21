#ifndef SDA_TEMA3_TASK1_H
#define SDA_TEMA3_TASK1_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int year;
    float deg;
} TrCell, *TrList;

typedef struct adj_list_city {
    int print_order;
    char dest[20];
    int tr_count;
    TrList tr_list;
    struct adj_list_city *next;
} AdjCellCity, *AdjListCity;

typedef struct {
    int count;
    AdjListCity *adj_list;
} GraphCity;

GraphCity *readGraphCity(FILE *input, int count);
GraphCity *initGraphCity(int count);
AdjListCity createCellCity(char *dest);
void ageGraph(GraphCity *g, int duration);
void addEdgeCity(GraphCity *g, char *source, char *dest, int order, int tr_count, TrList tr_list);
void printGraphCity(GraphCity *g);
void deleteGraphCity(GraphCity *g);

#endif //SDA_TEMA3_TASK1_H
