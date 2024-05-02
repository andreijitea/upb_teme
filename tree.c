/* JITEA Andrei-Petru - 315CB */

#include "tree.h"

/*
 * Initializeaza un arbore cu o litera data
 * (Se poate aplica pentru orice nod din arbore)
 */
Tree initTree(char letter) {
	Tree tree = (Tree)malloc(sizeof(Node));
	tree->letter = letter;
	for (int i = 0; i < CHILD_LEN; i++) {
		tree->children[i] = NULL;
	}
	return tree;
}
// Elibereaza memoria alocata pentru un arbore
void freeTree(Tree tree) {
	if (tree == NULL) {
		return;
	}
	/*
	 * Elibereaza memoria revursiv
	 * pentru toti copiii nodului curent
	 */
	for (int i = 0; i < CHILD_LEN; i++) {
		freeTree(tree->children[i]);
	}
	// Elibereaza memoria pentru nodul curent
	free(tree);
}

// Calculeaza recursiv inaltimea unui arbore
int getTreeHeight(Tree tree) {
	int max_height = 0;
	if (tree == NULL)
		return 0;
	/*
	 * Calculeaza inaltimea pentru fiecare
	 * copil al nodului curent si alege maximul
	 */
	for (int i = 0; i < CHILD_LEN; i++) {
		int child_height = getTreeHeight(tree->children[i]);
		if (child_height > max_height)
			max_height = child_height;
	}
	return max_height + 1;
}

// Afiseaza recursiv elementele unui arbore la un anumit nivel
void printTreeLevel(Tree tree, int level, FILE *outfile) {
	if (tree == NULL) {
		return;
	}
	/* Afiseaza litera nodului curent daca nivelul este 0
	 * Altfel, afiseaza recursiv litera copiilor nodului curent
	 */
	if (level == 0) {
		fprintf(outfile, "%c ", tree->letter);
	} else if (level > 0) {
		for (int i = 0; i < CHILD_LEN; i++) {
			printTreeLevel(tree->children[i], level - 1, outfile);
		}
	}
}

// Afiseaza un arbore, linie cu linie
void printTree(Tree tree, FILE *outfile) {
	int height = getTreeHeight(tree);
	for (int i = 1; i < height; i++) {
		printTreeLevel(tree, i, outfile);
		fprintf(outfile, "\n");
	}
}

