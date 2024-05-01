/* JITEA Andrei-Petru - 315CB */

#include "tasks_helpers.h"

/*
 * Adauga un sufix al unui cuvant intr-un arbore dat
 */
void addSuffix(Tree tree, char *suffix) {
    if (tree == NULL || suffix == NULL || suffix[0] == '\0')
        return;
    // Calculeaza indexul copilului
    int index;
    if (suffix[0] == '$')
        index = 0;
    else
        index = suffix[0] - 'a' + 1;
    if (index < 0 || index >= CHILD_LEN) {
        return;
    }
    // Daca copilul de pe pozitia calculata nu exista, il creeaza
    if (tree->children[index] == NULL) {
        tree->children[index] = initTree(suffix[0]);
    }
    // Trece la urmatoarea litera a sufixului
    suffix++;
    // Continua recursiv adaugarea sufixului de la litera urmatoare
    addSuffix(tree->children[index], suffix);
}

/*
 * Numara recursiv nodurile frunza dintr-un arbore
 * (nodurile care au litera '$')
 */
int countLeaves(Tree tree) {
    if (tree == NULL)
        return 0;
    int num = 0;
    if (tree->letter == '$') {
        num++;
    }
    for (int i = 0; i < CHILD_LEN; i++) {
        num += countLeaves(tree->children[i]);
    }
    return num;
}

/*
 * Numara sufixele de dimensiune k dintr-un arbore,
 * comparand adancimea curenta cu dimensiunea k
 * (k+1 deoarece se ia in considerare si caracterul '$')
 */
int countKLenSuffixes(Tree tree, int k, int depth) {
    if (tree == NULL)
        return 0;
    int len = 0;
    if (tree->letter == '$' && depth == k)
        return 1;
    
    for (int i = 0; i < CHILD_LEN; i++) {
        len += countKLenSuffixes(tree->children[i], k, depth+1);
    }
    return len;
}

/*
 * Afla numarul maxim de descendenti directi
 * ai unui nod din arbore
 */
int maxChildren(Tree tree) {
    if (tree == NULL)
        return 0;

    int max = 0;
    for (int i = 0; i < CHILD_LEN; i++) {
        if (tree->children[i] != NULL) {
            max++;
        }
    }

    for (int i = 0; i < CHILD_LEN; i++) {
        int aux = maxChildren(tree->children[i]);
        if (aux > max) {
            max = aux;
        }
    }
    return max;
}