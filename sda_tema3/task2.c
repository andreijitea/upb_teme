/* JITEA Andrei-Petru - 315CB */

#include "task2.h"

/*
 * Functia citeste un graf de orase din fisierul de intrare si il returneaza
 * Pentru fiecare nod destinatie, salveaza ordinea in care a fost citit.
 * Ordinea trebuie pastrata pentru a putea afisa corect graful.
 */
GraphCity2 *readGraphCity2(FILE *input, int count) {
    GraphCity2 *g = initGraphCity2(count);
    char source[20], dest[20];

    for (int i = 0; i < count / 2; i++) {
        int cost = 0;
        // Citeste numele nodurilor sursa si destinatie si costul muchiei
        fscanf(input, "%s %s %d", source, dest, &cost);

        // Adauga muchia in graful de orase
        addEdgeCity2(g, source, dest, i, cost);
    }

    return g;
}

/*
 * Functia initializeaza un graf cu un numar de noduri dat.
 * Functia primeste dublul numarului din fisierul de intrare,
 * pentru a avea suficiente noduri pentru fiecare muchie,
 * in cazul in care fiecare muchie are un nod sursa si un nod destinatie diferit.
 */
GraphCity2 *initGraphCity2(int count) {
    GraphCity2 *g = (GraphCity2 *) malloc(sizeof(GraphCity2));
    g->count = count;
    g->end_count = 0;

    // Aloca memorie pentru listele de adiacenta
    g->adj_list = (AdjListCity2 *) malloc(count * sizeof(AdjListCity2));
    for (int i = 0; i < count; i++)
        g->adj_list[i] = NULL;

    return g;
}

/*
 * Functia creeaza un nod de tip celula pentru lista de adiacenta a unui oras.
 */
AdjListCity2 createCellCity2(char *dest) {
    AdjListCity2 cell = (AdjListCity2) malloc(sizeof(AdjCellCity2));
    strcpy(cell->dest, dest);
    cell->next = NULL;
    cell->print_order = -1;
    cell->city_id = -1;
    cell->cost = 0;
    cell->status = UNUSED;

    return cell;
}

/*
 * Functia adauga o muchie in graful de orase de la nodul sursa la nodul destinatie.
 * Salveaza ordinea de afisare a muchiei si costul acesteia.
 */
void addEdgeCity2(GraphCity2 *g, char *source, char *dest, int order, int cost) {
    // Cauta nodul sursa in listele de adiacenta
    for (int i = 0; i < g->count; i++) {
        // Daca nodul sursa nu exista inca, il adauga, impreuna cu nodul destinatie
        if (g->adj_list[i] == NULL) {
            // Adauga nodul sursa
            g->adj_list[i] = createCellCity2(source);

            // Adauga nodul destinatie si salveaza toate informatiile necesare
            g->adj_list[i]->next = createCellCity2(dest);
            g->adj_list[i]->next->print_order = order;
            g->adj_list[i]->next->cost = cost;

            break;
        }
        // Daca nodul sursa exista deja, adauga nodul destinatie la lista de adiacenta
        else if (strcmp(g->adj_list[i]->dest, source) == 0) {
            // Cauta ultimul nod din lista de adiacenta
            AdjListCity2 aux = g->adj_list[i];
            while (aux->next != NULL)
                aux = aux->next;

            // Adauga nodul destinatie si salveaza toate informatiile necesare
            aux->next = createCellCity2(dest);
            aux->next->print_order = order;
            aux->next->cost = cost;

            break;
        }
    }

    // Face legatura inversa, de la nodul destinatie la nodul sursa
    for (int i = 0; i < g->count; i++) {
        // Daca nodul destinatie nu exista inca, il adauga, impreuna cu nodul sursa
        if (g->adj_list[i] == NULL) {
            g->adj_list[i] = createCellCity2(dest);
            g->adj_list[i]->next = createCellCity2(source);
            g->adj_list[i]->next->cost = cost;

            break;
        }
        // Daca nodul destinatie exista deja, adauga nodul sursa la lista de adiacenta
        else if (strcmp(g->adj_list[i]->dest, dest) == 0) {
            // Cauta ultimul nod din lista de adiacenta
            AdjListCity2 aux = g->adj_list[i];
            while (aux->next != NULL)
                aux = aux->next;
            // Adauga nodul sursa si salveaza toate informatiile necesare
            aux->next = createCellCity2(source);
            aux->next->cost = cost;

            break;
        }
    }
}

/*
 * Functia seteaza indexul fiecarui nod si indexul fiecarui nod din fiecare lista de adiacenta
 * pentru a aplica algoritmul lui Dijkstra asupra grafului.
 */
void setCityIds(GraphCity2 *g) {
    // Seteaza indexul fiecarui nod
    for (int i = 0; i < g->count; i++) {
        AdjListCity2 aux = g->adj_list[i];
        if (aux == NULL)
            continue;

        aux->city_id = i;
    }

    // Seteaza indexul fiecarui nod din fiecare lista de adiacenta
    for (int i = 0; i < g->count; i++) {
        AdjListCity2 aux = g->adj_list[i];
        if (aux == NULL)
            continue;

        // Parcurge lista de adiacenta
        aux = aux->next;
        while (aux != NULL) {
            // Cauta nodul destinatie in listele de adiacenta
            // si seteaza indexul nodului destinatie
            for (int j = 0; j < g->count; j++) {
                AdjListCity2 temp = g->adj_list[j];
                if (temp == NULL)
                    continue;

                // Daca nodul destinatie a fost gasit, seteaza indexul
                if (strcmp(aux->dest, temp->dest) == 0) {
                    aux->city_id = temp->city_id;
                    break;
                }
            }
            aux = aux->next;
        }
    }

}

void dijkstra(GraphCity2 *g, char *source, int max_edges) {
    // Vector folosit pentru a retine distantele minime de la nodul sursa la fiecare nod
    int *distances = (int *) malloc(g->count * sizeof(int));
    // Vector folosit pentru a retine daca un nod a fost vizitat sau nu
    int *visited = (int *) malloc(g->count * sizeof(int));
    // Vector folosit pentru a retine parintele fiecarui nod
    int *prev = (int *) malloc(g->count * sizeof(int));

    // Cauta nodul sursa in listele de adiacenta
    AdjListCity2 start_cell = NULL;
    for (int i = 0; i < g->count; i++) {
        // Daca nodul sursa a fost gasit, seteaza nodul sursa
        if (strcmp(g->adj_list[i]->dest, source) == 0) {
            start_cell = g->adj_list[i];
            break;
        }
    }
    if (start_cell == NULL)
        return;


    // Initializeaza vectorii auxiliari
    for (int i = 0; i < g->count; i++) {
        distances[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }

    // Seteaza distanta punctului de plecare
    distances[start_cell->city_id] = 0;

    // Parcurge fiecare nod din graf
    for (int i = 0; i < g->count; i++) {
        int min_dist = INF, min_index = -1;
        // Cauta nodul cu distanta minima de la nodul sursa
        for (int j = 0; j < g->count; j++) {
            if (visited[j] == 0 && distances[j] <= min_dist) {
                min_dist = distances[j];
                min_index = j;
            }
        }
        // Daca nu exista noduri nevizitate, se iese din bucla
        if (min_index == -1)
            break;

        // Se marcheaza nodul ca vizitat
        visited[min_index] = 1;

        // Se actualizeaza distantele minime pentru fiecare nod vecin
        AdjListCity2 aux = g->adj_list[min_index];
        if (aux == NULL)
            continue;

        while (aux != NULL) {
            int cost = aux->cost, dest_index = aux->city_id;

            // Se actualizeaza distanta minima daca este cazul
            if (visited[dest_index] == 0 && distances[min_index] + cost < distances[dest_index]) {
                distances[dest_index] = distances[min_index] + cost;
                prev[dest_index] = min_index;
            }

            aux = aux->next;
        }
    }

    // Marcheaza muchiile care sunt necesare parcurgerii
    for (int i = 0; i < g->count; i++) {
        AdjListCity2 aux = g->adj_list[i];
        if (aux == NULL)
            continue;

        // Parcurge lista de adiacenta
        aux = aux->next;
        while (aux != NULL) {
            if (prev[aux->city_id] == i) {
                // Marcheaza muchia ca fiind necesara
                aux->status = USED;

                // Marcheaza muchia inversa ca fiind necesara
                AdjListCity2 aux2 = g->adj_list[aux->city_id];
                while (aux2->city_id != prev[aux->city_id])
                    aux2 = aux2->next;
                aux2->status = USED;

                // Incrementeaza numarul de muchii necesare
                g->end_count++;
            }
            aux = aux->next;
        }
    }

    // Elimina muchiile cu costul cel mai mare
    for (; g->end_count > max_edges;) {
        int max_cost = 0, max_id = -1;
        AdjListCity2 max_edge = NULL;

        // Cauta muchia cu costul cel mai mare
        for (int i = 0; i < g->count; i++) {
            AdjListCity2 aux = g->adj_list[i];
            if (aux == NULL)
                continue;

            // Parcurge lista de adiacenta
            aux = aux->next;
            while (aux != NULL) {
                if (aux->status == USED) {
                    if (aux->cost > max_cost) {
                        max_cost = aux->cost;
                        max_id = i;
                        max_edge = aux;
                    }
                }
                aux = aux->next;
            }
        }
        if (max_edge == NULL)
            return;

        // Modifica statusul muchiei ca fiind neutilizata
        max_edge->status = UNUSED;

        // Modifica statusul muchiei inversa ca fiind neutilizata
        AdjListCity2 aux = g->adj_list[max_edge->city_id];
        while (aux->city_id != max_id)
            aux = aux->next;
        aux->status = UNUSED;

        // Decrementeaza numarul de muchii necesare
        g->end_count--;
    }

    // Elibereaza memoria pentru vectorii auxiliari
    free(distances);
    free(visited);
    free(prev);
}

/*
 * Functia afiseaza graful.
 * Afiseaza fiecare muchie necesara in ordinea in care a fost citita.
 */
void printGraphCity2(FILE *outfile, GraphCity2 *g) {
    int order = 0;

    // Afiseaza numarul de muchii dupa eliminari
    fprintf(outfile, "%d\n", g->end_count);

    // Parcurge lista de adiacenta a fiecarui nod
    for (int i = 0; i < g->count; i++) {
        AdjListCity2 aux = g->adj_list[i];
        if (aux == NULL)
            continue;

        AdjListCity2 source_cell = aux;

        // Parcurge fiecare nod destinatie
        aux = aux->next;
        while (aux != NULL) {
            // Afiseaza muchia daca ordinea de afisare este corecta
            if (order == aux->print_order) {
                if (aux->status == USED)
                    fprintf(outfile, "%s %s\n", source_cell->dest, aux->dest);

                aux = aux->next;
                order++;

            }
            // Daca ordinea nodului este mai mare, cauta nodul cu ordinea corecta si afiseaza muchia
            else if (order < aux->print_order) {
                for (int j = i; j < g->count; j++) {
                    AdjListCity2 temp = g->adj_list[j];
                    if (temp == NULL)
                        continue;

                    AdjListCity2 temp_source = temp;

                    // Parcurge fiecare nod destinatie
                    temp = temp->next;
                    while (temp != NULL) {
                        // Afiseaza muchia daca ordinea de afisare este corecta
                        if (temp->print_order == order) {
                            if (temp->status == USED)
                                fprintf(outfile, "%s %s\n", temp_source->dest, temp->dest);

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
 * Elibereaza memoria alocata pentru listele de adiacenta.
 */
void deleteGraphCity2(GraphCity2 *g) {
    for (int i = 0; i < g->count; i++) {
        AdjListCity2 aux = g->adj_list[i];

        while (aux != NULL) {
            AdjListCity2 temp = aux;
            aux = aux->next;

            free(temp);
        }
    }

    free(g->adj_list);
    free(g);
}