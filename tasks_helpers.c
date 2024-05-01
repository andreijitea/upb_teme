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