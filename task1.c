#include "task1.h"

/*
 * Functia citeste un graf din fisierul de intrare si il returneaza
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
        int *tr_list_ids = calloc(tr_count, sizeof(int));
        float *tr_list_deg = calloc(tr_count, sizeof(float));
        for (int j = 0; j < tr_count; j++) {
            fscanf(input, "%f", &tr_deg);
            tr_list_ids[j] = total_tr_count++;
            tr_list_deg[j] = tr_deg;
        }

        // Adauga muchia in graf
        addEdgeCity(g, source, dest, i, tr_count, tr_list_ids, tr_list_deg);
    }
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
    for (int i = 0; i < count; i++) {
        g->adj_list[i] = NULL;
    }

    return g;
}

/*
 * Functia creeaza un nod de tip celula pentru lista de adiacenta.
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

GraphTr *initGraphTr(int count) {
    GraphTr *g = (GraphTr *) malloc(sizeof(GraphTr));
    g->count = count;

    // Aloca memorie pentru listele de adiacenta
    g->adj_list = (AdjListTr *) malloc(count * sizeof(AdjListTr));
    for (int i = 0; i < count; i++) {
        g->adj_list[i] = NULL;
    }

    return g;
}

AdjListTr createCellTr(int source) {
    AdjListTr cell = (AdjListTr) malloc(sizeof(AdjCellTr));
    cell->dest = source;
    cell->next = NULL;
    cell->deg = 0;

    return cell;
}

void buildGraphTr(GraphCity *graphCity, GraphTr *graphTr) {
    for (int i = 0; i < graphCity->count; i++) {
        AdjListCity aux = graphCity->adj_list[i], prev = NULL;
        if (aux == NULL) {
            continue;
        }
        prev = aux;
        printf("%s %d: ", aux->dest, aux->tr_count);
        aux = aux->next;
        while (aux != NULL) {
            printf("%s ", aux->dest);
            for (int j = 0; j < aux->tr_count; j++) {
                printf("%d ", aux->tr_list_ids[j]);
                // Adauga muchii interioare in graful de tronsoane
                if (0 < j && j < aux->tr_count) {
//                    printf("(%d %d)\n", aux->tr_list_ids[j - 1], aux->tr_list_ids[j]);
                    addEdgeTr(graphTr, aux->tr_list_ids[j - 1], aux->tr_list_ids[j], aux->tr_list_deg[j]);
                }
                // Adauga muchii exterioare (din vecinii orasului) in graful de tronsoane
                else {
                    if (prev->next == NULL)
                        continue;
                    AdjCellCity *temp = prev->next;
                    while (temp != NULL) {
                        if (temp != aux) {
//                            printf("(%d %d)\n", aux->tr_list_ids[j], temp->tr_list_ids[0]);
                            addEdgeTr(graphTr, aux->tr_list_ids[j], temp->tr_list_ids[0], temp->tr_list_deg[0]);
                        }

                        temp = temp->next;
                    }

                }
            }
            aux = aux->next;
        }
        printf("\n");
    }
}

void addEdgeTr(GraphTr *g, int source, int dest, float deg) {
    // Cauta nodul sursa in listele de adiacenta
    for (int i = 0; i < g->count; i++) {
        // Daca nodul sursa nu exista inca, il adauga, impreuna cu nodul destinatie
        if (g->adj_list[i] == NULL) {
            // Adauga nodul sursa
            g->adj_list[i] = createCellTr(source);
            // Adauga nodul destinatie si salveaza ordinea de afisare
            g->adj_list[i]->next = createCellTr(dest);
            g->adj_list[i]->next->deg = deg;
            break;
        }
        // Daca nodul sursa exista deja, adauga nodul destinatie la lista de adiacenta
        else if (g->adj_list[i]->dest == source) {
            // Cauta ultimul nod din lista de adiacenta
            AdjListTr aux = g->adj_list[i];
            while (aux->next != NULL) {
                aux = aux->next;
            }
            // Adauga nodul destinatie si salveaza ordinea de afisare
            aux->next = createCellTr(dest);
            aux->next->deg = deg;
            break;
        }
    }
//    // acelasi lucru pentru nodul destinatie
//    for (int i = 0; i < g->count; i++) {
//        if (g->adj_list[i] == NULL) {
//            g->adj_list[i] = createCellTr(dest);
//            g->adj_list[i]->next = createCellTr(source);
//            g->adj_list[i]->next->deg = deg;
//            break;
//        }
//        else if (g->adj_list[i]->dest == dest) {
//            AdjListTr aux = g->adj_list[i];
//            while (aux->next != NULL) {
//                aux = aux->next;
//            }
//            aux->next = createCellTr(source);
//            aux->next->deg = deg;
//            break;
//        }
//    }
}

void ageGraph(GraphCity *graphCity, GraphTr *graphTr, int duration) {
    float *temp_deg = calloc(graphTr->count, sizeof(float));

    free(temp_deg);
}

/*
 * Functia adauga o muchie in graf de la nodul sursa la nodul destinatie.
 *
 */
void addEdgeCity(GraphCity *g, char *source, char *dest, int order, int tr_count, int *tr_list_ids, float *tr_list_deg) {
    // Cauta nodul sursa in listele de adiacenta
    for (int i = 0; i < g->count; i++) {
        // Daca nodul sursa nu exista inca, il adauga, impreuna cu nodul destinatie
        if (g->adj_list[i] == NULL) {
            // Adauga nodul sursa
            g->adj_list[i] = createCellCity(source);

            // Adauga nodul destinatie si salveaza ordinea de afisare
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
            while (aux->next != NULL) {
                aux = aux->next;
            }
            // Adauga nodul destinatie si salveaza ordinea de afisare
            aux->next = createCellCity(dest);
            aux->next->print_order = order;
            aux->next->tr_count = tr_count;
            aux->next->tr_list_ids = tr_list_ids;
            aux->next->tr_list_deg = tr_list_deg;
            break;
        }
    }
    // acelasi lucru pentru nodul destinatie
    for (int i = 0; i < g->count; i++) {
        if (g->adj_list[i] == NULL) {
            g->adj_list[i] = createCellCity(dest);
            g->adj_list[i]->next = createCellCity(source);
            //g->adj_list[i]->next->print_order = order;
            g->adj_list[i]->next->tr_count = tr_count;
            // Face cate o copie a listelor de tronsoane pentru fiecare nod
            // Le inverseaza ordinea
            g->adj_list[i]->next->tr_list_ids = calloc(tr_count, sizeof(int));
            g->adj_list[i]->next->tr_list_deg = calloc(tr_count, sizeof(float));
            for (int j = 0; j < tr_count; j++) {
                g->adj_list[i]->next->tr_list_ids[j] = tr_list_ids[tr_count - j - 1];
                g->adj_list[i]->next->tr_list_deg[j] = tr_list_deg[tr_count - j - 1];
            }
            break;
        }
        else if (strcmp(g->adj_list[i]->dest, dest) == 0) {
            AdjListCity aux = g->adj_list[i];
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = createCellCity(source);
            // aux->next->print_order = order;
            aux->next->tr_count = tr_count;
            // Face cate o copie a listelor de tronsoane pentru fiecare nod
            // Le inverseaza ordinea
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

// afiseaza listele de adiacenta ale fiecarui nod
void prtr(GraphTr *g) {
    for (int i = 0; i < g->count; i++) {
        AdjListTr aux = g->adj_list[i];
        if (aux == NULL) {
            continue;
        }
        printf("%d: ", aux->dest);
        aux = aux->next;
        while (aux != NULL) {
            printf("%d-%.2f ", aux->dest, aux->deg);
            aux = aux->next;
        }
        printf("\n");
    }

}

// afiseaza listele de adiacenta ale fiecarui nod
void prgr(GraphCity *g) {
    for (int i = 0; i < g->count; i++) {
        AdjListCity aux = g->adj_list[i];
        if (aux == NULL) {
            continue;
        }
        printf("%s: ", aux->dest);
        aux = aux->next;
        while (aux != NULL) {
            printf("%s ", aux->dest);
            aux = aux->next;
        }
        printf("\n");
    }

}

/*
 * Functia afiseaza graful.
 * Afiseaza fiecare muchie in ordinea in care a fost citita.
 */
void printGraphCity(GraphCity *g) {
    int order = 0;
    // Parcurge fiecare nod sursa (lista de adiacenta)
    for (int i = 0; i < g->count; i++) {
        AdjListCity aux = g->adj_list[i];
        if (aux == NULL) {
            continue;
        }
        char source[20];
        strcpy(source, aux->dest);
        // Parcurge fiecare nod destinatie
        aux = aux->next;
        while (aux != NULL) {
            // Afiseaza muchia daca ordinea de afisare este corecta
            if (order == aux->print_order) {
                printf("%s %s %d ", source, aux->dest, aux->tr_count);
                // Afiseaza tronsoanele muchiei
                for (int j = 0; j < aux->tr_count; j++) {
                    printf("%d-%.2f ", aux->tr_list_ids[j], aux->tr_list_deg[j]);
                }
                printf("\n");
                aux = aux->next;
                order++;
            }
            // Daca ordinea nodului este mai mare, cauta nodul cu ordinea corecta si afiseaza muchia
            else if (order < aux->print_order) {
                for (int j = i; j < g->count; j++) {
                    AdjListCity temp = g->adj_list[j];
                    if (temp == NULL) {
                        continue;
                    }
                    char temp_source[20];
                    strcpy(temp_source, temp->dest);
                    // Parcurge fiecare nod destinatie
                    temp = temp->next;
                    while (temp != NULL) {
                        // Afiseaza muchia daca ordinea de afisare este corecta
                        if (temp->print_order == order) {
                            printf("%s %s %d ", temp_source, temp->dest, temp->tr_count);
                            // Afiseaza tronsoanele muchiei
                            for (int k = 0; k < temp->tr_count; k++) {
                                printf("%d-%.2f ", temp->tr_list_ids[k], temp->tr_list_deg[k]);
                            }
                            printf("\n");
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
}

/*
 * Functia elibereaza memoria alocata pentru graful citit.
 * Elibereaza memoria alocata pentru listele de adiacenta si pentru tronsoane.
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