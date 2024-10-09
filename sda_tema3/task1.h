/* JITEA Andrei-Petru - 315CB */

#ifndef SDA_TEMA3_TASK1_H
#define SDA_TEMA3_TASK1_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Structura pentru lista de adiacenta a unui tronson
typedef struct adj_list_tr {
	int dest;
	float deg;
	struct adj_list_tr *next;
} AdjCellTr, *AdjListTr;

// Structura pentru un graf de tronsoane
typedef struct {
	int count;
	AdjListTr *adj_list;
} GraphTr;

// Structura pentru lista de adiacenta a unui oras
typedef struct adj_list_city {
	int print_order;
	char dest[20];
	int tr_count;
	int *tr_list_ids;
	float *tr_list_deg;
	struct adj_list_city *next;
} AdjCellCity, *AdjListCity;

// Structura pentru un graf de orase
typedef struct {
	int count;
	AdjListCity *adj_list;
} GraphCity;

// Functii pentru graful de orase
GraphCity *readGraphCity(FILE *input, int count, int *tot_tr_c);
GraphCity *initGraphCity(int count);
AdjListCity createCellCity(char *dest);
void addEdgeCity(GraphCity *g, char *source, char *dest, int order, int tr_count, int *tr_list_ids, float *tr_list_deg);
void printGraphCity(FILE *outfile, GraphCity *g, float max_deg);
void deleteGraphCity(GraphCity *g);

// Functii pentru graful de tronsoane
GraphTr *initGraphTr(int count);
AdjListTr createCellTr(int source);
void addEdgeTr(GraphTr *g, int source, int dest, float deg);
void buildGraphTr(GraphCity *graphCity, GraphTr *graphTr);
void deleteGraphTr(GraphTr *g);

// Functia de aplicare a procesului de degradare a tronsoanelor
void ageGraph(GraphCity *graphCity, GraphTr *graphTr, int duration);


#endif //SDA_TEMA3_TASK1_H
