/* JITEA Andrei-Petru - 315CB */

#include "tasks_helpers.h"

// Rezolvarea cerintei 1
void task1(Tree tree, FILE *infile, FILE *outfile) {
	int wordcount;
	fscanf(infile, "%d", &wordcount);
	// Adauga sufixele cuvintelor in arbore
	makeTree(tree, infile, wordcount);
	// Afiseaza arborele in fisierul de iesire
	printTree(tree, outfile);
}

// Rezolvarea cerintei 2
void task2(Tree tree, FILE *infile, FILE *outfile, int k) {
	int wordcount;
	fscanf(infile, "%d", &wordcount);
	// Adauga sufixele cuvintelor in arbore
	makeTree(tree, infile, wordcount);
	/*
	 * Afiseaza numarul nodurilor frunza
	 * ale arborelui in fisierul de iesire
	 */
	fprintf(outfile, "%d\n", countLeaves(tree));
	/*
	 * Afiseaza numarul de sufixe de lungime k
	 * ale arborelui in fisierul de iesire
	 */
	fprintf(outfile, "%d\n", countKLenSuffixes(tree, k+1, 0));
	/*
	 * Afiseaza numarul maxim de descendenti
	 * directi ai unui nod al arborelui
	 * in fisierul de iesire
	 */
	fprintf(outfile, "%d\n", maxChildren(tree));
}

// Rezolvarea cerintei 3
void task3(Tree tree, FILE *infile, FILE *outfile) {
	int wordcount, suffixcount;
	fscanf(infile, "%d %d", &wordcount, &suffixcount);
	// Adauga sufixele cuvintelor in arbore
	makeTree(tree, infile, wordcount);
	// Verifica daca sufixele date se gasesc in arbore
	for (int i = 0; i < suffixcount; i++) {
		char suffix[100];
		fscanf(infile, "%s", suffix);
		// Afiseaza daca sufixul se gaseste in arbore
		int suffixlen = strlen(suffix);
		suffix[suffixlen] = '$';
		suffix[suffixlen+1] = '\0';
		fprintf(outfile, "%d\n", findSuffix(tree, suffix));
	}
}

// Adauga un sufix al unui cuvant intr-un arbore dat
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

	// Calculeaza numarul de descendenti directi ai nodului curent
	int max = 0;
	for (int i = 0; i < CHILD_LEN; i++) {
		if (tree->children[i] != NULL) {
			max++;
		}
	}

	/*
	 * Continua recursiv cautarea numarului maxim de descendenti
	 * si il compara cu numarul maxim gasit pana acum
	 */
	for (int i = 0; i < CHILD_LEN; i++) {
		int aux = maxChildren(tree->children[i]);
		if (aux > max) {
			max = aux;
		}
	}
	return max;
}

// Alcatuieste arborele din cuvintele citite din fisier
void makeTree(Tree tree, FILE *infile, int wordcount) {
	/*
	 * Citeste cuvant cu cuvant fisierul dat si
	 * adauga sufixele fiecaruia in arbore
	 */
	for (int i = 0; i < wordcount; i++) {
		char word[100];
		fscanf(infile, "%s", word);
		// Adauga caracterul special '$' la finalul cuvantului
		int wordlen = strlen(word);
		word[wordlen] = '$';
		word[wordlen+1] = '\0';
		// Adauga sufixele cuvantului in arbore
		for (int j = wordlen; j >= 0; j--) {
			addSuffix(tree, &word[j]);
		}
	}
}

/*
 * Verifica recursiv daca un sufix dat se gaseste in arbore
 * (returneaza 1 daca sufixul se gaseste, 0 altfel)
 */
int findSuffix(Tree tree, char *suffix) {
	if (tree == NULL || suffix == NULL || suffix[0] == '\0')
		return 0;
	// Calculeaza indexul copilului
	int index;
	if (suffix[0] == '$')
		index = 0;
	else
		index = suffix[0] - 'a' + 1;
	if (tree->children[index] == NULL) {
		return 0;
	}
	// Verifica daca s-a ajuns la finalul sufixului
	if (suffix[0] == '$' && tree->children[index]->letter == '$') {
		return 1;
	}
	// Continua recursiv cautarea sufixului pe urmatoarea litera
	return findSuffix(tree->children[index], suffix+1);
}
