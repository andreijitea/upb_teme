/* JITEA Andrei-Petru - 315CB */

#include "tasks_helpers.h"


int main(int argc, char *argv[]) {
	if (argc < 3)
		printf("Nu au fost date suficiente argumente in linia de comanda...\n");

	FILE *infile = NULL, *outfile = NULL;
	Tree tree = initTree('0');

	/*
	 * Rezolvarea celor 4 cerinte, in functie de primul argument
	 * dat in linia de comanda.
	 */
	if (strcmp(argv[1], "-c1") == 0) {
		infile = fopen(argv[2], "r");
		outfile = fopen(argv[3], "w");
		task1(tree, infile, outfile);
	} else if (strcmp(argv[1], "-c2") == 0) {
		infile = fopen(argv[3], "r");
		outfile = fopen(argv[4], "w");
		int k = atoi(argv[2]);
		task2(tree, infile, outfile, k);
	} else if (strcmp(argv[1], "-c3") == 0) {
		infile = fopen(argv[2], "r");
		outfile = fopen(argv[3], "w");
		task3(tree, infile, outfile);
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
