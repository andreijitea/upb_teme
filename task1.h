#ifndef SDA_TEMA3_TASK1_H
#define SDA_TEMA3_TASK1_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct tronson {
    int year;
    float deg;
    struct tronson *next;
    struct tronson *prev;
} TrCell, *TrList;

typedef struct adjList {
    int print_order;
    char dest[20];
    int tr_count;
    TrList tr_list;
    struct adjList *next;
} AdjCell, *AdjList;

typedef struct {
    int count;
    AdjList *adj_list;
} Graph;

Graph *readGraph(FILE *input, int count);
Graph *initGraph(int count);
AdjList createCell(char *dest);
void addEdge(Graph *g, char *source, char *dest, int order, int tr_count, TrList tr_list);
void printGraph(Graph *g);
void deleteGraph(Graph *g);

#endif //SDA_TEMA3_TASK1_H
