#include <stdio.h>
#include "train.h"


int main() {
    FILE *in_file = fopen("tema1.in", "r");
    FILE *out_file = fopen("tema1.out", "w");

    if (in_file == NULL || out_file == NULL) {
        printf("Eroare de deschidere a unuia dintre fisiere...\n");
        return -1;
    }

    T_List *train = initList();


    
    printfList(train);


    freeList(train);
    fclose(in_file);
    fclose(out_file);
    return 0;
}