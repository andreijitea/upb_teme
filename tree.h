/* JITEA Andrei-Petru - 315CB */

#ifndef SDA_TEMA2_TREE_H
#define SDA_TEMA2_TREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CHILD_LEN 27

typedef struct node {
    char letter;
    struct node *children[CHILD_LEN];
} Node, *Tree;

 int getTreeHeight(Tree tree);
void printTreeLevel(Tree tree, int level, FILE *outfile);
void printTree(Tree tree, FILE *outfile);
Tree initTree(char letter);
void freeTree(Tree tree);

#endif
