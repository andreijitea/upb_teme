#include <stdio.h>
#include "train_list.h"
#include "command_queue.h"


int main() {
    FILE *in_file = fopen("tema1.in", "r");
    FILE *out_file = fopen("tema1.out", "w");

    if (in_file == NULL || out_file == NULL) {
        printf("Eroare de deschidere a unuia dintre fisiere...\n");
        return -1;
    }

    T_Queue *comenzi = initQueue();
    pushQCell(comenzi, 1, "test");
    pushQCell(comenzi, 2, "abc");
    popQCell(comenzi);
    popQCell(comenzi);
    printfQueue(comenzi);
    reverseQueue(comenzi);
    printfQueue(comenzi);

    freeQueue(comenzi);
    fclose(in_file);
    fclose(out_file);
    return 0;
}