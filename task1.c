#include "task1.h"

/*
 * Functia citeste un graf din fisierul de intrare si il returneaza
 * source - numele nodului sursa
 * dest - numele nodului destinatie
 * Pentru fiecare nod destinatie, salveaza ordinea in care a fost citit.
 * Ordinea trebuie pastrata pentru a putea afisa corect graful.
 */
GraphCity *readGraphCity(FILE *input, int count) {
    GraphCity *g = initGraphCity(count);
    char source[20], dest[20];
    for (int i = 0; i < count / 2; i++) {
        int tr_count = 0;
        float tr_deg = 0;
        // Citeste numele nodurilor sursa si destinatie si numarul de tronsoane
        fscanf(input, "%s %s %d", source, dest, &tr_count);

        // Citeste tronsoanele unei muchii si le salveaza intr-o lista
        TrList tr_list = (TrList) calloc(tr_count, sizeof(TrCell));
        for (int j = 0; j < tr_count; j++) {
            fscanf(input, "%f", &tr_deg);
            tr_list[j].deg = tr_deg;
            tr_list[j].year = 0;
        }

        // Adauga muchia in graf
        addEdgeCity(g, source, dest, i, tr_count, tr_list);
    }
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
    cell->tr_list = NULL;

    return cell;
}

void ageGraph(GraphCity *g, int duration) {
    // Afiseaza vecinii fiecarui tronson

}

/*
 * Functia adauga o muchie in graf de la nodul sursa la nodul destinatie.
 * Sensul opus nu este necesar.
 */
void addEdgeCity(GraphCity *g, char *source, char *dest, int order, int tr_count, TrList tr_list) {
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
            g->adj_list[i]->next->tr_list = tr_list;
            return;
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
            aux->next->tr_list = tr_list;
            return;
        }
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
                    printf("%.2f ", aux->tr_list[j].deg);
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
                                printf("%.2f ", temp->tr_list[k].deg);
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
            free(temp->tr_list);
            free(temp);
        }
    }
    free(g->adj_list);
    free(g);
}
