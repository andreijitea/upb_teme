/* JITEA Andrei-Petru - 315CB */

#ifndef SDA_TEMA2_TASKS_HELPERS_H
#define SDA_TEMA2_TASKS_HELPERS_H

#include "tree.h"

void addSuffix(Tree tree, char *suffix);
int countLeaves(Tree tree);
int countKLenSuffixes(Tree tree, int k, int depth);
int maxChildren(Tree tree);
int findSuffix(Tree tree, char *suffix);
void makeTree(Tree tree, FILE *infile, int wordcount);

void task1(Tree tree, FILE *infile, FILE *outfile);
void task2(Tree tree, FILE *infile, FILE *outfile, int k);
void task3(Tree tree, FILE *infile, FILE *outfile);

#endif //SDA_TEMA2_TASKS_HELPERS_H
