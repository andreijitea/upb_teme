/* JITEA Andrei-Petru - 315CB */

#include "tasks_helpers.h"


int main(int argc, char *argv[]) {
    FILE *infile = NULL, *outfile = NULL;
    Tree tree = initTree('0');

    /*
     * Rezolvarea celor 4 cerinte, in functie de primul argument
     * dat in linia de comanda.
     */
    if (strcmp(argv[1], "-c1") == 0) {
        infile = fopen(argv[2], "r");
        outfile = fopen(argv[3], "w");

        int wordcount;
        fscanf(infile, "%d", &wordcount);
        /* Citeste cuvant cu cuvant fisierul dat si
         * adauga sufixele fiecaruia in arbore
         */
        for (int i = 0; i < wordcount; i++) {
            char word[100];
            fscanf(infile, "%s", word);
            // Adauga caracterul special '$' la finalul cuvantului
            int wordlen = strlen(word);
            word[wordlen] = '$';
            word[wordlen+1] = '\0';
            // Adauga sufixele cuvantului in arbore
            for (int j = wordlen; j >= 0; j--) {
                addSuffix(tree, &word[j]);
            }
        }
        // Afiseaza arborele in fisierul de iesire
        printTree(tree, outfile);
    } else if (strcmp(argv[1], "-c2") == 0) {
        infile = fopen(argv[3], "r");
        outfile = fopen(argv[4], "w");
    } else if (strcmp(argv[1], "-c3") == 0) {
        infile = fopen(argv[2], "r");
        outfile = fopen(argv[3], "w");
    } else if (strcmp(argv[1], "-c4") == 0) {
        infile = fopen(argv[2], "r");
        outfile = fopen(argv[3], "w");
    }

    freeTree(tree);

    if (infile != NULL)
        fclose(infile);
    if (outfile != NULL)
        fclose(outfile);


    return 0;
}