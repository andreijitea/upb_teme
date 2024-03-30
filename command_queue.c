#include "command_queue.h"

// Initializeaza o coada
T_Queue *initQueue() {
    T_Queue *queue = malloc(sizeof(T_Queue));
    queue->length = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

// Initializeaza o celula
T_QCell *createQCell(int id, char *param) {
    T_QCell *aux = malloc(sizeof(T_QCell));
    aux->param = malloc(strlen(param) * sizeof(char));
    aux->next = NULL;
    aux->prev = NULL;
    aux->command_id = id;
    strcpy(aux->param, param);
    return aux;
}

// Adauga o celula in coada
void pushQCell(T_Queue *queue, int id, char *param) {
    queue->length++;
    T_QCell *aux = createQCell(id, param);
    // In cazul in care coada este goala, insereaza prima celula
    if (queue->head == NULL || queue->tail == NULL) {
        queue->head = aux;
        queue->tail = aux;
        return;
    }
    // Insereaza o celula
    queue->tail->next = aux;
    aux->prev = queue->tail->next;
    queue->tail = aux;
    return;
}

// Scoate o celula din coada (prima celula)
void popQCell(T_Queue *queue) {
    queue->length--;
    // In cazul in care coada contine 1 celula, o sterge si reseteaza capetele cozii
    if (queue->length == 0) {
        T_QCell *aux = queue->head;
        free(aux->param);
        free(aux);
        queue->head = NULL;
        queue->tail = NULL;
        return;
    }
    // Muta capul cozii la urmatoarea celula
    T_QCell *aux = queue->head;
    queue->head = queue->head->next;
    aux->next = NULL;
    queue->head->prev = NULL;
    // Sterge prima celula a cozii
    free(aux->param);
    free(aux);
    return;
}

// Inverseaza celulele unei cozi
void reverseQueue(T_Queue *queue) {
    if (queue->length == 0)
        return;

    // Copiaza 'command_id' si 'param' ale celulei din capul cozii
    int command_id;
    char *param = malloc(strlen(queue->head->param) * sizeof(char));
    command_id = queue->head->command_id;
    strcpy(param, queue->head->param);

    // Elimina celula din capul cozii
    popQCell(queue);

    reverseQueue(queue);

    // Adauga in capatul cozii o noua celula cu datele salvate inainte
    pushQCell(queue, command_id, param);

    // Sterge stringul folosit intermediar inversarii cozii
    free(param);
    return;
}

// Sterge o coada
void freeQueue(T_Queue *queue) {
    // In cazul in care coada este goala, sterge structura cozii
    if (queue->length == 0) {
        free(queue);
        return;
    }
    // Sterge fiecare celula a cozii, una cate una
    T_QCell *crt = queue->head;
    while (crt != NULL) {
        T_QCell *aux = crt;
        crt = crt->next;
        free(aux->param);
        free(aux);
    }
    // Sterge structura cozii
    free(queue);
    return;
}

void printfQueue(T_Queue *queue) {
    if (queue->length == 0) {
        printf("Coada goala\n");
        return;
    }
    T_QCell *crt = queue->head;
    while (crt != queue->tail) {
        printf("Q: %d %s\n", crt->command_id, crt->param);
        crt = crt->next;
    }
    printf("Q: %d %s\n", crt->command_id, crt->param);
    return;
}