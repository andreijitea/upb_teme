/* JITEA Andrei-Petru - 315CB */

#ifndef SDA_TEMA2_TASKS_HELPERS_H
#define SDA_TEMA2_TASKS_HELPERS_H

#include "tree.h"

void addSuffix(Tree tree, char *suffix);
int countLeaves(Tree tree);
int countKLenSuffixes(Tree tree, int k, int depth);
int maxChildren(Tree tree);

#endif //SDA_TEMA2_TASKS_HELPERS_H
