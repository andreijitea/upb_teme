#ifndef SDA_TEMA1_COMMAND_QUEUE_H
#define SDA_TEMA1_COMMAND_QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
