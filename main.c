/* JITEA Andrei-Petru - 315CB */

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
		// Rezolvare TASK 1
		int r, k, *tot_tr_c;
		float l;
		tot_tr_c = (int *)calloc(1, sizeof(int)); // nr total de tronsoane

		GraphCity *graphCity; // graf orase
		GraphTr *graphTr; // graf tronsoane

		// Citeste datele de intrare
		fscanf(in_file, "%d %d %f", &r, &k, &l);

		// Citeste graful de orase
		graphCity = readGraphCity(in_file, 2 * r, tot_tr_c);

		// Construieste graful de tronsoane, in raport cu graful de orase
		graphTr = initGraphTr(*tot_tr_c);
		buildGraphTr(graphCity, graphTr);

		// Aplica procesul de degradare a tronsoanelor din graf
		ageGraph(graphCity, graphTr, k);

		// Afiseaza graful de orase, conform cerintei
		printGraphCity(out_file, graphCity, l);

		// Elibereaza memoria alocata dinamic pentru grafuri
		deleteGraphCity(graphCity);
		deleteGraphTr(graphTr);
		free(tot_tr_c);
	} else if (strcmp(argv[1], "2") == 0) {
		// task 2
	} else {
		printf("Argument invalid\n");
		return 1;
	}

	// Inchide fisierele
	fclose(in_file);
	fclose(out_file);
	return 0;
}