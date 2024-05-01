#ifndef SDA_TEMA2_TREE_H
#define SDA_TEMA2_TREE_H

typedef struct node {
    char letter;
    struct node *children[27];
} Node, *Tree;

#endif //SDA_TEMA2_TREE_H
