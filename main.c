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

    T_Queue *commands = initQueue();
    T_List *train = initList();
    long reps;
    char line[100], *endp;
    fgets(line, 100, in_file);
    reps = strtol(line, &endp, 10);

    for (int i = 0; i < reps; i++) {
        fgets(line, 100, in_file);
        // Elimina caracterul '\n' din capatul randului (pentru strcmp)
        line[strcspn(line, "\n")] = '\0';
        char *tok = strtok(line, " ");
        // Primul TOK este mereu comanda, urmatorul TOK este parametrul, daca exista
        printf("c: %s\n", tok);
        if (strcmp(tok, "EXECUTE") == 0) {
            switch (commands->head->command_id) {
                case MOVE_LEFT_ID:
                    moveVipLeft(train);
                    break;
                case MOVE_RIGHT_ID:
                    moveVipRight(train);
                    break;
                case WRITE_ID:
                    writeToVipLCell(train, commands->head->param[0]);
                    break;
                case CLEAR_CELL_ID:
                    train = clearVipLCell(train);
                    break;
                case CLEAR_ALL_ID:
                    train = clearAllLCells(train);
                    break;
                case INSERT_LEFT_ID:
                    insertLCellLeft(train, commands->head->param[0], out_file);
                    break;
                case INSERT_RIGHT_ID:
                    insertLCellRight(train, commands->head->param[0]);
                    break;
                case SEARCH_ID:
                    search(train, commands->head->param, out_file);
                    break;
                case SEARCH_LEFT_ID:
                    searchLeft(train, commands->head->param, out_file);
                    break;
                case SEARCH_RIGHT_ID:
                    searchRight(train, commands->head->param, out_file);
                    break;
            }
            popQCell(commands);
        } else if (strcmp(tok, "SHOW_CURRENT") == 0) {
            fprintfVipLCell(train, out_file);
        } else if (strcmp(tok, "SHOW") == 0) {
            fprintfList(train, out_file);
        } else if (strcmp(tok, "SWITCH") == 0) {
            reverseQueue(commands);
        } else if (strcmp(tok, "MOVE_LEFT") == 0) {
            pushQCell(commands, MOVE_LEFT_ID, NULL);
        } else if (strcmp(tok, "MOVE_RIGHT") == 0) {
            pushQCell(commands, MOVE_RIGHT_ID, NULL);
        } else if (strcmp(tok, "WRITE") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, WRITE_ID, tok);
        } else if (strcmp(tok, "CLEAR_CELL") == 0) {
            pushQCell(commands, CLEAR_CELL_ID, NULL);
        } else if (strcmp(tok, "CLEAR_ALL") == 0) {
            pushQCell(commands, CLEAR_ALL_ID, NULL);
        } else if (strcmp(tok, "INSERT_LEFT") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, INSERT_LEFT_ID, tok);
        } else if (strcmp(tok, "INSERT_RIGHT") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, INSERT_RIGHT_ID, tok);
        } else if (strcmp(tok, "SEARCH") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, SEARCH_ID, tok);
        } else if (strcmp(tok, "SEARCH_LEFT") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, SEARCH_LEFT_ID, tok);
        } else if (strcmp(tok, "SEARCH_RIGHT") == 0) {
            tok = strtok(NULL, " ");
            pushQCell(commands, SEARCH_RIGHT_ID, tok);
        }
        printfQueue(commands);
        printfList(train);
        printf("\n");
    }


    freeQueue(commands);
    freeList(train);

    fclose(in_file);
    fclose(out_file);
    return 0;
}