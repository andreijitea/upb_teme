#include "train_list.h"


// Initializeaza o lista
T_List *initList() {
    T_List *list = malloc(sizeof(T_List));
    // Initializeaza santinela listei
    list->head = (T_LCell*) malloc(sizeof(T_LCell));
    if (list->head == NULL)
        return NULL;
    // Initializeaza celula listei
    T_LCell *aux = createLCell();
    if (aux == NULL)
        return NULL;
    // Conecteaza santinela cu celula listei
    list->head->next = aux;
    list->head->prev = aux;
    aux->next = list->head;
    aux->prev = list->head;

    // Pozitioneaza VIP-ul in singura celula existenta
    list->vip = aux;
    // Seteaza lungimea listei initiale (1 santinela + 1 vagon)
    list->length = 2;
    return list;
}

// Initializeaza o celula noua
T_LCell *createLCell() {
    T_LCell *aux = (T_LCell*) malloc(sizeof(T_LCell));
    aux->info = '#';
    aux->next = NULL;
    aux->prev = NULL;
    return aux;
}

// Sterge toate celulele listei (reinitializeaza lista)
T_List *clearAllLCells(T_List *list) {
    freeList(list);
    T_List *new_list = initList();
    return new_list;
}

// Sterge celula VIP-ului
T_List *clearVipLCell(T_List *list) {
    // Scade lungimea listei
    list->length--;
    // In cazul in care lista avea 1 element, o reseteaza
    if (list->length == 1) {
        freeList(list);
        T_List *new_list = initList();
        return new_list;
    }
    // Reface legaturile dintre celulele vecine
    T_LCell *aux = list->vip;
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    // Muta VIP-ul o celula la stanga
    moveVipLeft(list);

    // Sterge celula veche
    free(aux);
    return list;
}

// Muta VIP-ul la dreapta
void moveVipRight(T_List *list) {
    // In cazul in care VIP-ul este capatul listei, insereaza o noua celula
    if (list->vip->next == list->head) {
        insertLCellRight(list, '#');
        return;
    }
    // Muta VIP-ul o celula la dreapta
    list->vip = list->vip->next;
    return;
}

// Muta VIP-ul la stanga
void moveVipLeft(T_List *list) {
    // In cazul in care VIP-ul este prima celula, se muta in coada listei
    if (list->vip->prev == list->head) {
        list->vip = list->head->prev;
        return;
    }
    // Muta VIP-ul o celula la stanga
    list->vip = list->vip->prev;
    return;
}

// Insereaza o celula la dreapta VIP-ului
void insertLCellRight(T_List *list, char info) {
    // Incrementeaza lungimea listei
    list->length++;
    // Initializeaza o noua celula
    T_LCell *aux = createLCell();
    aux->info = info;
    // Conecteaza noua celula cu celulele vecine din lista
    list->vip->next = aux;
    aux->next = list->head;
    aux->prev = list->vip;
    list->head->prev = aux;
    // Muta VIP-ul in noua celula
    list->vip = aux;
    return;
}

// Insereaza o celula la stanga VIP-ului
void insertLCellLeft(T_List *list, char info, FILE *file) {
    // Verifica daca VIP-ul este prima celula
    if (list->vip->prev == list->head) {
        fprintf(file, "ERROR\n");
        return;
    }
    // Incrementeaza lungimea listei
    list->length++;
    // Initializeaza o noua celula
    T_LCell *aux = createLCell();
    aux->info = info;
    // Conecteaza noua celula cu celulele vecine din lista
    list->vip->prev->next = aux;
    aux->prev = list->vip->prev;
    list->vip->prev = aux;
    aux->next = list->vip;
    // Muta VIP-ul in noua celula
    list->vip = aux;
    return;
}

// Schimba litera celulei VIP
void writeToVipLCell(T_List *list, char info) {
    list->vip->info = info;
    return;
}

// Afiseaza lista
void fprintfList(T_List *list, FILE *file) {
    T_LCell *crt = list->head->next;
    for (int i = 1; i < list->length; i++) {
        // Afiseaza celulele in care nu se afla VIP-ul
        if (crt != list->vip) {
            fprintf(file, "%c", crt->info);
            crt = crt->next;
            continue;
        }
        // Afiseaza celula in care se afla VIP-ul
        fprintf(file, "|%c|", crt->info);
        crt = crt->next;
    }
    fprintf(file, "\n");
}

// Afiseaza continutul celulei de pe pozitia VIP
void fprintfVipLCell(T_List *list, FILE *file) {
    fprintf(file, "%c\n", list->vip->info);
    return;
}

// Sterge o lista
void freeList(T_List *list) {
    T_LCell *crt = list->head;
    // Deconecteaza primul element si ultimul element al listei => lista liniara
    list->head->prev->next = NULL;
    list->head->prev = NULL;

    // Sterge fiecare celula a listei
    while (crt != NULL) {
        T_LCell *aux = crt;
        crt = crt->next;
        free(aux);
    }
    // Sterge structura listei
    free(list);
    return;
}

// Cauta o secventa data in intreaga lista, incepand din pozitia VIP
void search(T_List *list, char* word, FILE *file) {
    // Initializeaza un string care va contine literele din lista
    char *content = malloc((list->length - 1) * sizeof(char));
    // Parcurge lista de la pozitia VIP pana la (VIP - 1) si salveaza literele in string
    T_LCell *crt = list->vip;
    for (int i = 1; i < list->length; i++) {
        if (crt == list->head) {
            crt = list->head->next;
        }
        content[i-1] = crt->info;
        crt = crt->next;
    }
    // Cauta indexul primei aparitii a secventei cautate in lista
    char *result = strstr(content, word);
    if (result == NULL) {
        fprintf(file, "ERROR\n");
        free(content);
        return;
    }
    // Calculeaza indexul primei litere din aparitie
    int pos = result - content;
    // Parcurge lista pana la indexul calculat
    crt = list->vip;
    for (int i = 0; i < pos; i++) {
        if (crt == list->head) {
            crt = list->head->next;
        }
        crt = crt->next;
    }
    if (crt == list->head) {
        crt = list->head->next;
    }
    // Muta VIP-ul listei la pozitia calculata
    list->vip = crt;
    free(content);
    return;
}

// Cauta o secventa data in stanga VIP-ului
void searchLeft(T_List *list, char* word, FILE *file) {
    // Initializeaza un string care va contine literele din lista
    char *content = malloc((list->length - 1) * sizeof(char));
    // Parcurge lista de la VIP pana la prima celula si salveaza literele in string
    T_LCell *crt = list->vip;
    int j = 0;
    while (crt != list->head) {
        content[j] = crt->info;
        crt = crt->prev;
        j++;
    }
    content[j] = '\0';
    // Cauta indexul primei aparitii a secventei cautate in lista
    char *result = strstr(content, word);
    if (result == NULL) {
        fprintf(file, "ERROR\n");
        free(content);
        return;
    }
    // Calculeaza indexul ultimei litere din aparitie
    int pos = strlen(content) - (result - content) - strlen(word);
    // Parcurge lista pana la indexul calculat
    crt = list->head->next;
    for (int i = 0; i < pos; i++) {
        crt = crt->next;
    }
    // Muta VIP-ul listei la pozitia calculata
    list->vip = crt;
    free(content);
    return;
}

// Cauta o secventa data in dreapta VIP-ului
void searchRight(T_List *list, char* word, FILE *file) {
    // Initializeaza un string care va contine literele din lista
    char *content = malloc((list->length - 1) * sizeof(char));
    // Parcurge lista de la VIP pana in capat si salveaza literele in string
    T_LCell *crt = list->vip;
    int j = 0;
    while (crt != list->head) {
        content[j] = crt->info;
        crt = crt->next;
        j++;
    }
    content[j] = '\0';
    // Cauta indexul primei aparitii a secventei cautate in lista
    char *result = strstr(content, word);
    if (result == NULL) {
        fprintf(file, "ERROR\n");
        free(content);
        return;
    }
    // Calculeaza indexul ultimei litere din aparitie
    int pos = result - content + strlen(word) - 1;
    // Parcurge lista pana la indexul calculat
    crt = list->head->next;
    for (int i = 0; i < pos; i++) {
        crt = crt->next;
    }
    // Muta VIP-ul listei la pozitia calculata
    list->vip = crt;
    free(content);
    return;
}





// FUNCTIE FOLOSITA IN DEBUGGING
void printfList(T_List *list) {
    // Set a pointer to the first "real" cell (primul vagon)
    T_LCell *crt = list->head->next;
    for (int i = 1; i < list->length; i++) {
        // Prints the cells the "vip" does not point to (vagoanele in care nu se afla mecanicul)
        if (crt != list->vip) {
            printf("%c", crt->info);
            crt = crt->next;
            continue;
        }
        // Prints the cell the "vip" points to (vagonul in care se afla mecanicul)
        printf("|%c|", crt->info);
        crt = crt->next;
    }
    printf("\n");
    return;
}