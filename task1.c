/* JITEA Andrei-Petru - 315CB */

#include "task1.h"

/*
 * Functia citeste un graf de orase din fisierul de intrare si il returneaza
 * Pentru fiecare nod destinatie, salveaza ordinea in care a fost citit.
 * Ordinea trebuie pastrata pentru a putea afisa corect graful.
 */
GraphCity *readGraphCity(FILE *input, int count, int *tot_tr_c) {
	int total_tr_count = 0;
	GraphCity *g = initGraphCity(count);
	char source[20], dest[20];

	for (int i = 0; i < count / 2; i++) {
		int tr_count = 0;
		float tr_deg = 0;
		// Citeste numele nodurilor sursa si destinatie si numarul de tronsoane
		fscanf(input, "%s %s %d", source, dest, &tr_count);

		// Citeste tronsoanele unei muchii si le salveaza intr-o lista
		// In alta lista se salveaza id-urile tronsoanelor (unice la nivel de graf)
		int *tr_list_ids = calloc(tr_count, sizeof(int));
		float *tr_list_deg = calloc(tr_count, sizeof(float));
		for (int j = 0; j < tr_count; j++) {
			fscanf(input, "%f", &tr_deg);
			tr_list_ids[j] = total_tr_count++;
			tr_list_deg[j] = tr_deg;
		}

		// Adauga muchia in graful de orase
		addEdgeCity(g, source, dest, i, tr_count, tr_list_ids, tr_list_deg);
	}
	// Returneaza numarul total de tronsoane din graf
	*tot_tr_c = total_tr_count;

	return g;
}

/*
 * Functia initializeaza un graf cu un numar de noduri dat.
 * Functia primeste dublul numarului din fisierul de intrare,
 * pentru a avea suficiente noduri pentru fiecare muchie,
 * in cazul in care fiecare muchie are un nod sursa si un nod destinatie diferit.
 */
GraphCity *initGraphCity(int count) {
	GraphCity *g = (GraphCity *) malloc(sizeof(GraphCity));
	g->count = count;

	// Aloca memorie pentru listele de adiacenta
	g->adj_list = (AdjListCity *) malloc(count * sizeof(AdjListCity));
	for (int i = 0; i < count; i++)
		g->adj_list[i] = NULL;

	return g;
}

/*
 * Functia creeaza un nod de tip celula pentru lista de adiacenta a unui oras.
 */
AdjListCity createCellCity(char *dest) {
	AdjListCity cell = (AdjListCity) malloc(sizeof(AdjCellCity));
	strcpy(cell->dest, dest);
	cell->next = NULL;
	cell->print_order = -1;
	cell->tr_count = 0;
	cell->tr_list_ids = NULL;
	cell->tr_list_deg = NULL;

	return cell;
}

/*
 * Functia initializeaza un graf de tronsoane cu un numar de noduri dat ca parametru.
 */
GraphTr *initGraphTr(int count) {
	GraphTr *g = (GraphTr *) malloc(sizeof(GraphTr));
	g->count = count;

	// Aloca memorie pentru listele de adiacenta
	g->adj_list = (AdjListTr *) malloc(count * sizeof(AdjListTr));
	for (int i = 0; i < count; i++)
		g->adj_list[i] = NULL;

	return g;
}

/*
 * Functia creeaza un nod de tip celula pentru lista de adiacenta a unui tronson.
 */
AdjListTr createCellTr(int source) {
	AdjListTr cell = (AdjListTr) malloc(sizeof(AdjCellTr));
	cell->dest = source;
	cell->next = NULL;
	cell->deg = 0;

	return cell;
}

/*
 * Functia construieste graful de tronsoane pornind de la graful de orase.
 * Fiecare tronson din graful de orase devine un nod in graful de tronsoane.
 */
void buildGraphTr(GraphCity *graphCity, GraphTr *graphTr) {
	// Parcurge fiecare nod din graful de orase
	for (int i = 0; i < graphCity->count; i++) {
		AdjListCity aux = graphCity->adj_list[i], prev = NULL;

		if (aux == NULL)
			continue;

		prev = aux;
		aux = aux->next;

		while (aux != NULL) {
			for (int j = 0; j < aux->tr_count; j++) {
				// Adauga muchii interioare in graful de tronsoane
				if (0 < j && j < aux->tr_count)
					addEdgeTr(graphTr, aux->tr_list_ids[j - 1], aux->tr_list_ids[j], aux->tr_list_deg[j]);
				// Adauga muchii exterioare (din vecinii orasului) in graful de tronsoane
				else {
					if (prev->next == NULL)
						continue;

					AdjCellCity *temp = prev->next;

					while (temp != NULL) {
						// Se omite nodul curent daca este acelasi cu nodul sursa
						if (temp != aux)
							addEdgeTr(graphTr, aux->tr_list_ids[j], temp->tr_list_ids[0], temp->tr_list_deg[0]);

						temp = temp->next;
					}
				}
			}
			aux = aux->next;
		}
	}
}

/*
 * Functia adauga o muchie in graful de tronsoane de la nodul sursa la nodul destinatie,
 * salvand degradarea muchiei.
 */
void addEdgeTr(GraphTr *g, int source, int dest, float deg) {
	// Cauta nodul sursa in listele de adiacenta
	for (int i = 0; i < g->count; i++) {
		// Daca nodul sursa nu exista inca, il adauga, impreuna cu nodul destinatie
		if (g->adj_list[i] == NULL) {
			// Adauga nodul sursa
			g->adj_list[i] = createCellTr(source);

			// Adauga nodul destinatie si salveaza degradarea
			g->adj_list[i]->next = createCellTr(dest);
			g->adj_list[i]->next->deg = deg;

			break;
		}
		// Daca nodul sursa exista deja, adauga nodul destinatie la lista de adiacenta
		else if (g->adj_list[i]->dest == source) {
			// Cauta ultimul nod din lista de adiacenta
			AdjListTr aux = g->adj_list[i];
			while (aux->next != NULL)
				aux = aux->next;

			// Adauga nodul destinatie si salveaza degradarea
			aux->next = createCellTr(dest);
			aux->next->deg = deg;

			break;
		}
	}
}

/*
 * Functia aplica procesul de degradare a tronsoanelor din graf, pentru un numar de ani dat,
 * conform regulilor din enuntul temei.
 */
void ageGraph(GraphCity *graphCity, GraphTr *graphTr, int duration) {
	for (int i = 0; i < duration; i++) {
		// Vectori auxiliari pentru a salva degradarea tronsoanelor si nodurile vizitate
		float *temp_deg = calloc(graphTr->count, sizeof(float));
		int *visited = calloc(graphTr->count, sizeof(int));

		/*
		 * Salveaza degradarea fiecarui tronson intr-un vector,
		 * pentru a le putea procesa mai usor
		 */
		for (int j = 0; j < graphTr->count; j++) {
			AdjListTr aux = graphTr->adj_list[j];
			if (aux == NULL)
				continue;

			aux = aux->next;
			while (aux != NULL) {
				temp_deg[aux->dest] = aux->deg;
				aux = aux->next;
			}
		}

		// Proceseaza mai intai degradarea tronsoanelor cu degradare 0
		for (int j = 0; j < graphTr->count; j++) {
			AdjListTr aux = graphTr->adj_list[j];
			if (aux == NULL)
				continue;

			// Salveaza id-ul nodului sursa
			int id = aux->dest;

			if (temp_deg[id] != 0 || visited[id] == 1)
				continue;

			// Cauta degradarea maxima dintre tronsoanele vecine
			float max_deg = 0;
			aux = aux->next;
			while (aux != NULL) {
				if (aux->deg > max_deg)
					max_deg = aux->deg;

				aux = aux->next;
			}
			// Seteaza degradarea nodului sursa la jumatate din degradarea maxima
			// si il marcheaza ca vizitat
			temp_deg[id] = max_deg / 2;
			visited[id] = 1;
		}

		// Proceseaza apoi degradarea tronsoanelor cu degradare diferita de 0
		for (int j = 0; j < graphTr->count; j++) {
			AdjListTr aux = graphTr->adj_list[j];
			if (aux == NULL)
				continue;

			// Salveaza id-ul nodului sursa
			int id = aux->dest;

			if (temp_deg[id] == 0 || visited[id] == 1)
				continue;

			// Seteaza degradarea nodului sursa la dublul degradarii curente
			// si il marcheaza ca vizitat
			temp_deg[id] = temp_deg[id] * 2;
			visited[id] = 1;
		}

		// Truncheaza degradarea tronsoanelor la 100
		for (int j = 0; j < graphTr->count; j++) {
			if (temp_deg[j] > 100)
				temp_deg[j] = 100;
		}

		// Modifica graful de tronsoane cu noile valori de degradare procesate
		for (int j = 0; j < graphTr->count; j++) {
			AdjListTr aux = graphTr->adj_list[j];
			if (aux == NULL)
				continue;

			aux = aux->next;
			while (aux != NULL) {
				aux->deg = temp_deg[aux->dest];
				aux = aux->next;
			}
		}

		// Modifica graful de orase cu noile valori de degradare procesate
		// Afisarea se foloseste de aceste valori, nu de graful de tronsoane
		for (int j = 0; j < graphCity->count; j++) {
			AdjListCity aux = graphCity->adj_list[j];
			if (aux == NULL)
				continue;

			aux = aux->next;
			while (aux != NULL) {
				for (int k = 0; k < aux->tr_count; k++)
					aux->tr_list_deg[k] = temp_deg[aux->tr_list_ids[k]];

				aux = aux->next;
			}
		}

		// Elibereaza memoria alocata pentru vectorii auxiliari
		free(visited);
		free(temp_deg);
	}
}

/*
 * Functia adauga o muchie in graful de orase de la nodul sursa la nodul destinatie.
 * Salveaza ordinea de afisare a muchiei, lista de tronsoane, numarul de tronsoane si degradarea lor.
 */
void addEdgeCity(GraphCity *g, char *source, char *dest, int order, int tr_count, int *tr_list_ids, float *tr_list_deg) {
	// Cauta nodul sursa in listele de adiacenta
	for (int i = 0; i < g->count; i++) {
		// Daca nodul sursa nu exista inca, il adauga, impreuna cu nodul destinatie
		if (g->adj_list[i] == NULL) {
			// Adauga nodul sursa
			g->adj_list[i] = createCellCity(source);

			// Adauga nodul destinatie si salveaza toate informatiile necesare
			g->adj_list[i]->next = createCellCity(dest);
			g->adj_list[i]->next->print_order = order;
			g->adj_list[i]->next->tr_count = tr_count;
			g->adj_list[i]->next->tr_list_ids = tr_list_ids;
			g->adj_list[i]->next->tr_list_deg = tr_list_deg;

			break;
		}
		// Daca nodul sursa exista deja, adauga nodul destinatie la lista de adiacenta
		else if (strcmp(g->adj_list[i]->dest, source) == 0) {
			// Cauta ultimul nod din lista de adiacenta
			AdjListCity aux = g->adj_list[i];
			while (aux->next != NULL)
				aux = aux->next;

			// Adauga nodul destinatie si salveaza toate informatiile necesare
			aux->next = createCellCity(dest);
			aux->next->print_order = order;
			aux->next->tr_count = tr_count;
			aux->next->tr_list_ids = tr_list_ids;
			aux->next->tr_list_deg = tr_list_deg;

			break;
		}
	}

	// Face legatura inversa, de la nodul destinatie la nodul sursa
	for (int i = 0; i < g->count; i++) {
		// Daca nodul destinatie nu exista inca, il adauga, impreuna cu nodul sursa
		if (g->adj_list[i] == NULL) {
			g->adj_list[i] = createCellCity(dest);
			g->adj_list[i]->next = createCellCity(source);
			g->adj_list[i]->next->tr_count = tr_count;
			// Face cate o copie a listelor de tronsoane pentru fiecare nod
			// si le inverseaza ordinea
			g->adj_list[i]->next->tr_list_ids = calloc(tr_count, sizeof(int));
			g->adj_list[i]->next->tr_list_deg = calloc(tr_count, sizeof(float));
			for (int j = 0; j < tr_count; j++) {
				g->adj_list[i]->next->tr_list_ids[j] = tr_list_ids[tr_count - j - 1];
				g->adj_list[i]->next->tr_list_deg[j] = tr_list_deg[tr_count - j - 1];
			}

			break;
		}
		// Daca nodul destinatie exista deja, adauga nodul sursa la lista de adiacenta
		else if (strcmp(g->adj_list[i]->dest, dest) == 0) {
			// Cauta ultimul nod din lista de adiacenta
			AdjListCity aux = g->adj_list[i];
			while (aux->next != NULL)
				aux = aux->next;
			// Adauga nodul sursa si salveaza toate informatiile necesare
			aux->next = createCellCity(source);
			aux->next->tr_count = tr_count;
			// Face cate o copie a listelor de tronsoane pentru fiecare nod
			// si le inverseaza ordinea
			aux->next->tr_list_ids = calloc(tr_count, sizeof(int));
			aux->next->tr_list_deg = calloc(tr_count, sizeof(float));
			for (int j = 0; j < tr_count; j++) {
				aux->next->tr_list_ids[j] = tr_list_ids[tr_count - j - 1];
				aux->next->tr_list_deg[j] = tr_list_deg[tr_count - j - 1];
			}

			break;
		}
	}
}

/*
 * Functia afiseaza graful.
 * Afiseaza fiecare muchie in ordinea in care a fost citita.
 * Functia proceseaza si ce muchii au degradarea medie sub o valoare data.
 */
void printGraphCity(FILE *outfile, GraphCity *g, float max_deg) {
	int order = 0;
	float deg_sum;
	// Vector pentru a salva daca o muchie are degradarea medie sub valoarea data
	int *ok_ids = calloc(g->count / 2, sizeof(int));

	// Parcurge lista de adiacenta a fiecarui nod
	for (int i = 0; i < g->count; i++) {
		AdjListCity aux = g->adj_list[i];
		if (aux == NULL)
			continue;

		char source[20];
		strcpy(source, aux->dest);

		// Parcurge fiecare nod destinatie
		aux = aux->next;
		while (aux != NULL) {
			// Afiseaza muchia daca ordinea de afisare este corecta
			if (order == aux->print_order) {
				deg_sum = 0;
				fprintf(outfile, "%s %s %d ", source, aux->dest, aux->tr_count);

				// Afiseaza tronsoanele muchiei si calculeaza degradarea medie
				for (int j = 0; j < aux->tr_count; j++) {
					fprintf(outfile, "%.2f ", aux->tr_list_deg[j]);
					deg_sum += aux->tr_list_deg[j];
				}

				// Verifica daca degradarea medie a muchiei este sub valoarea data
				if (deg_sum / aux->tr_count < max_deg)
					ok_ids[order] = 1;

				fprintf(outfile, "\n");
				aux = aux->next;
				order++;

			}
			// Daca ordinea nodului este mai mare, cauta nodul cu ordinea corecta si afiseaza muchia
			else if (order < aux->print_order) {
				for (int j = i; j < g->count; j++) {
					AdjListCity temp = g->adj_list[j];
					if (temp == NULL)
						continue;

					char temp_source[20];
					strcpy(temp_source, temp->dest);

					// Parcurge fiecare nod destinatie
					temp = temp->next;
					while (temp != NULL) {
						// Afiseaza muchia daca ordinea de afisare este corecta
						if (temp->print_order == order) {
							deg_sum = 0;
							fprintf(outfile, "%s %s %d ", temp_source, temp->dest, temp->tr_count);

							// Afiseaza tronsoanele muchiei si calculeaza degradarea medie
							for (int k = 0; k < temp->tr_count; k++) {
								fprintf(outfile, "%.2f ", temp->tr_list_deg[k]);
								deg_sum += temp->tr_list_deg[k];
							}

							// Verifica daca degradarea medie a muchiei este sub valoarea data
							if (deg_sum / temp->tr_count < max_deg) {
								ok_ids[order] = 1;
							}

							fprintf(outfile, "\n");
							order++;

							break;
						}
						temp = temp->next;
					}
				}
			}
			else {
				aux = aux->next;
			}
		}
	}

	// Afiseaza id-urile muchiilor care au degradarea medie sub valoarea data
	for (int i = 0; i < g->count / 2; i++) {
		if (ok_ids[i] == 1)
			fprintf(outfile, "%d ", i+1);
	}

	// Elibereaza memoria alocata pentru vectorul de id-uri
	free(ok_ids);
}

/*
 * Functia elibereaza memoria alocata pentru graful citit.
 * Elibereaza memoria alocata pentru listele de adiacenta si pentru listele de tronsoane.
 */
void deleteGraphCity(GraphCity *g) {
	for (int i = 0; i < g->count; i++) {
		AdjListCity aux = g->adj_list[i];

		while (aux != NULL) {
			AdjListCity temp = aux;
			aux = aux->next;

			if (temp->tr_list_ids != NULL) {
				free(temp->tr_list_deg);
				free(temp->tr_list_ids);
			}

			free(temp);
		}
	}

	free(g->adj_list);
	free(g);
}
/*
 * Functia elibereaza memoria alocata pentru graful citit.
 * Elibereaza memoria alocata pentru listele de adiacenta.
 */
void deleteGraphTr(GraphTr *g) {
	for (int i = 0; i < g->count; i++) {
		AdjListTr aux = g->adj_list[i];

		while (aux != NULL) {
			AdjListTr temp = aux;
			aux = aux->next;
			free(temp);
		}
	}

	free(g->adj_list);
	free(g);
}