#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

typedef struct {
    int ***matrice;
    int N, M;
} imagine;

int ***load(int N, int M, char *path) {
    // Alocam o noua matrice
    int ***m = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        m[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            m[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    read_from_bmp(m, N, M, path);

    return m;
}

void save(int index, imagine imagini[], int N, int M, char *path) {
    write_to_bmp(imagini[index].matrice, N, M, path);
}

int main()
{
    imagine imagini[10];
    int i_img = 0;
    char comanda[2];

    do {
        scanf("%s", comanda);

        if (strcmp(comanda, "l") == 0) {
            int N, M;
            char path[50];
            scanf("%d %d %s", &N, &M, path);

            imagini[i_img].matrice = load(N, M, path);
            imagini[i_img].N = N;
            imagini[i_img].M = M;
            i_img++;
            
        } else if (strcmp(comanda, "s") == 0) {
            int index;
            char path[50];
            scanf("%d %s", &index, path);

            save(index, imagini, imagini[index].N, imagini[index].M, path);

        } else if (strcmp(comanda, "ah") == 0) {
            int index;
            scanf("%d", &index);

            imagini[index].matrice = flip_horizontal(imagini[index].matrice, imagini[index].N, imagini[index].M);

        } else if (strcmp(comanda, "ar") == 0) {
            int index, temp;
            scanf("%d", &index);

            imagini[index].matrice = rotate_left(imagini[index].matrice, imagini[index].N, imagini[index].M);
            temp = imagini[index].N;
            imagini[index].N = imagini[index].M;
            imagini[index].M = temp;

        } else if (strcmp(comanda, "ac") == 0) {
            int index, x, y, h, w;
            scanf("%d %d %d %d %d", &index, &x, &y, &h, &w);
            imagini[index].matrice = crop(imagini[index].matrice, imagini[index].N, imagini[index].M, x, y, h, w);
            imagini[index].N = h;
            imagini[index].M = w;

        } else if (strcmp(comanda, "ae") == 0) {
            int index, rows, cols, R, G, B;
            scanf("%d %d %d %d %d %d", &index, &rows, &cols, &R, &G, &B);
            imagini[index].matrice = extend(imagini[index].matrice, imagini[index].N, imagini[index].M, rows, cols, R, G, B);
            imagini[index].N += 2 * rows;
            imagini[index].M += 2 * cols; 
        } else if (strcmp(comanda, "ap") == 0) {
            int index_dst, index_src, x, y;
            scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
            imagini[index_dst].matrice = paste(imagini[index_dst].matrice, imagini[index_dst].N, imagini[index_dst].M, imagini[index_src].matrice, imagini[index_src].N, imagini[index_src].M, x, y);
        }

    } while (strcmp(comanda, "e") != 0);

    

	
	
    return 0;
}
