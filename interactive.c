#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

typedef struct {
    int ***matrice;
    int N, M;
} imagine;

typedef struct {
    float **matrice;
    int size;
} filtru;

int ***load_image(int N, int M, char *path) {
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

void delete_image(imagine imagini[], int index, int i_img) {
    for (int i = 0; i < imagini[index].N; i++) {
        for (int j = 0; j < imagini[index].M; j++) {
            free(imagini[index].matrice[i][j]);
        }
		free(imagini[index].matrice[i]);
    }
	free(imagini[index].matrice);

    for (int i = index; i < i_img; i++) {
        imagini[i] = imagini[i+1];
    }
}

float **load_filter(int size) {
    // Alocam o noua matrice
    float **m = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++) {
        m[i] = (float *)malloc(size * sizeof(float));
    }

    for (int i = 0; i < (size * size); i++) {
        scanf("%f", &m[i/size][i%size]);
    }

    return m;
}

void delete_filter(filtru filtre[10], int index, int i_fil) {
    for (int i = 0; i < filtre[index].size; i++) {
		free(filtre[index].matrice[i]);
    }
	free(filtre[index].matrice);

    for (int i = index; i < i_fil; i++) {
        filtre[i] = filtre[i+1];
    }
}

void save(int index, imagine imagini[], int N, int M, char *path) {
    write_to_bmp(imagini[index].matrice, N, M, path);
}

int main()
{
    int i_img = 0, i_fil = 0;
    imagine imagini[10];
    filtru filtre[10];
    char comanda[2];

    do {
        scanf("%s", comanda);

        if (strcmp(comanda, "l") == 0) {
            int N, M;
            char path[50];
            scanf("%d %d %s", &N, &M, path);

            imagini[i_img].matrice = load_image(N, M, path);
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
            scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
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

        } else if (strcmp(comanda, "cf") == 0) {
            int size;
            scanf("%d", &size);

            filtre[i_fil].matrice = load_filter(size);
            filtre[i_fil].size = size;
            i_fil++;

        } else if (strcmp(comanda, "af") == 0) {
            int index_img, index_filter;
            scanf("%d %d", &index_img, &index_filter);

            imagini[index_img].matrice = apply_filter(imagini[index_img].matrice, imagini[index_img].N, imagini[index_img].M, filtre[index_filter].matrice, filtre[index_filter].size);
        
        } else if (strcmp(comanda, "df") == 0) {
            int index;
            scanf("%d", &index);

            delete_filter(filtre, index, i_fil);
            i_fil--;
        } else if (strcmp(comanda, "di") == 0) {
            int index;
            scanf("%d", &index);

            delete_image(imagini, index, i_img);
            i_img--;
        }

    } while (strcmp(comanda, "e") != 0);

    

	
	
    return 0;
}
