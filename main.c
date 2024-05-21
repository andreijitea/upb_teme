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
        int r, k, *tot_tr_c;
        float l;
        tot_tr_c = (int *)calloc(1, sizeof(int));

        GraphCity *graphCity;
        GraphTr *graphTr;
        fscanf(in_file, "%d %d %f", &r, &k, &l);
        printf("%d %d %f\n", r, k, l);
        graphCity = readGraphCity(in_file, 2 * r, tot_tr_c);

        graphTr = initGraphTr(*tot_tr_c);
        buildGraphTr(graphCity, graphTr);


        ageGraph(graphCity, graphTr, k);
        printGraphCity(out_file, graphCity, l);

        deleteGraphCity(graphCity);
        deleteGraphTr(graphTr);
        free(tot_tr_c);
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