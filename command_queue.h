#ifndef SDA_TEMA1_COMMAND_QUEUE_H
#define SDA_TEMA1_COMMAND_QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MOVE_LEFT_ID 0
#define MOVE_RIGHT_ID 1
#define WRITE_ID 2
#define CLEAR_CELL_ID 3
#define CLEAR_ALL_ID 4
#define INSERT_LEFT_ID 5
#define INSERT_RIGHT_ID 6
#define SEARCH_ID 7
#define SEARCH_LEFT_ID 8
#define SEARCH_RIGHT_ID 9


typedef struct qcell {
    int command_id;
    char *param;
    struct qcell *prev, *next;
} T_QCell;

typedef struct {
    T_QCell *head, *tail;
    int length;
} T_Queue;

T_Queue *initQueue();
T_QCell *createQCell(int id, char *param);

void pushQCell(T_Queue *queue, int id, char *param);
void popQCell(T_Queue *queue);

void freeQueue(T_Queue *queue);

void reverseQueue(T_Queue *queue);

void printfQueue(T_Queue *queue);

#endif //SDA_TEMA1_COMMAND_QUEUE_H
