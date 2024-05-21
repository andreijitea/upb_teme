#include <stdio.h>
#include <string.h>
#include "task1.h"


int main(int argc, char *argv[])
{
    FILE *in_file = fopen("tema3.in", "r");
    FILE *out_file = fopen("tema3.out", "w");

    if (argc != 2) {
        printf("Numarul incorect de argumente\n");
        return 1;
    } else if (strcmp(argv[1], "1") == 0) {
        int r, k, l;
        GraphCity *graph;
        fscanf(in_file, "%d %d %d", &r, &k, &l);
        printf("%d %d %d\n", r, k, l);
        graph = readGraphCity(in_file, 2 * r);
        printGraphCity(graph);
        deleteGraphCity(graph);
    } else if (strcmp(argv[1], "2") == 0) {
        // task 2
    } else {
        printf("Argument invalid\n");
        return 1;
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
}