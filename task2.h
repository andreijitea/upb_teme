#ifndef SDA_TEMA3_TASK2_H
#define SDA_TEMA3_TASK2_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INF 100
#define USED 1
#define UNUSED 0

// Structura pentru lista de adiacenta a unui oras
typedef struct adj_list_city2 {
    int print_order;
    int city_id;
    int cost;
    int status; // daca muchia este necesara parcurgerii (UNUSED sau USED)
    char dest[20];
    struct adj_list_city2 *next;
} AdjCellCity2, *AdjListCity2;

// Structura pentru un graf de orase
typedef struct {
    int count;
    int end_count;
    AdjListCity2 *adj_list;
} GraphCity2;

// Functii pentru graful de orase
GraphCity2 *readGraphCity2(FILE *input, int count);
GraphCity2 *initGraphCity2(int count);
AdjListCity2 createCellCity2(char *dest);
void addEdgeCity2(GraphCity2 *g, char *source, char *dest, int order, int cost);
void setCityIds(GraphCity2 *g);
void printGraphCity2(FILE *outfile, GraphCity2 *g);
void deleteGraphCity2(GraphCity2 *g);

void dijkstra(GraphCity2 *g, char *source, int max_edges);


#endif //SDA_TEMA3_TASK2_H
