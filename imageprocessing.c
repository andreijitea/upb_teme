#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define MAX_COLOR 255
#define MIN_COLOR 0
#define COLOR_RANGE 3

// N - linii
// M - coloane

int ***flip_horizontal(int ***image, int N, int M) {
	// Procesare flip horizontal
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M/2; j++) {
            for (int k = 0; k < COLOR_RANGE; k++) {
                int temp = image[i][j][k];
                image[i][j][k] = image[i][M-j-1][k];
                image[i][M-j-1][k] = temp;
            }
        }
    }
	return image;
}


int ***rotate_left(int ***image, int N, int M) {
	// Alocam o noua matrice rezultanta a rotirii matricei originale
	int ***m = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        m[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            m[i][j] = (int *)malloc(COLOR_RANGE * sizeof(int));
        }
    }
	// Noua matrice = transpusa matricei vechi
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < COLOR_RANGE; k++) {
                int temp = image[i][j][k];
				m[j][i][k] = temp;
            }
        }
    }
	// Flip vertical al matricei noi
	for (int i = 0; i < M/2; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < COLOR_RANGE; k++) {
                int temp = m[i][j][k];
				m[i][j][k] = m[M-i-1][j][k];
				m[M-i-1][j][k] = temp;
            }
        }
    }
	// Free matrice originala
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
		free(image[i]);
    }
	free(image);

	return m;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
	// Alocam o noua matrice, sub-matrice a originalei
	int ***m = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        m[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            m[i][j] = (int *)malloc(COLOR_RANGE * sizeof(int));
        }
    }
	// Procesare sub-matrice
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < COLOR_RANGE; k++) {
				m[i][j][k] = image[y+i][x+j][k];
			}
		}
	}
	// Free matrice originala
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
		free(image[i]);
    }
	free(image);

	return m;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
	// Alocam o noua matrice, extinsa originalei
	int ***m = (int ***)malloc((N + 2*rows) * sizeof(int **));
    for (int i = 0; i < (N + 2*rows); i++) {
        m[i] = (int **)malloc((M + 2*cols) * sizeof(int *));
        for (int j = 0; j < (M + 2*cols); j++) {
            m[i][j] = (int *)malloc(COLOR_RANGE * sizeof(int));
        }
    }
	// Procesare matrice extinsa
	for (int i = 0; i < (N + 2*rows); i++) {
		for (int j = 0; j < (M + 2*cols); j++) {
			// Portiunea centrala a matricei, unde se copiaza matricea originala
			if (((rows <= i) && (i < N + rows)) && ((cols <= j) && (j < (M + cols)))) {
				for (int k = 0; k < COLOR_RANGE; k++) {
					m[i][j][k] = image[i-rows][j-cols][k];
				}
				continue;
			}
			// Portiunea extinsa, unde se introduce culoarea noua
			m[i][j][0] = new_R;
			m[i][j][1] = new_G;
			m[i][j][2] = new_B;
		}
	}
	// Free matrice originala
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
		free(image[i]);
    }
	free(image);

	return m;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
	// Procesare suprapunere matrice
	for (int i = y; (i < N_dst) && ((i-y) < N_src); i++) {
		for (int j = x; (j < M_dst) && ((j-x) < M_src); j++) {
			for (int k = 0; k < COLOR_RANGE; k++) {
				image_dst[i][j][k] = image_src[i-y][j-x][k];
			}
		}
	}
	return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
	// Alocam o noua matrice = matrice originala + filtru
	int ***m = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        m[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            m[i][j] = (int *)malloc(COLOR_RANGE * sizeof(int));
        }
    }
	// Procesare matrice filtrata
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < COLOR_RANGE; k++) {
				float new_color = 0;

				for (int fi = 0, a = i - (filter_size/2); fi < filter_size; fi++, a++) {
					for (int fj = 0, b = j - (filter_size/2); fj < filter_size; fj++, b++) {
						if ((0 <= a) && (a < N) && (0 <= b) && (b < M)) {
							new_color += (float) image[a][b][k] * filter[fi][fj];
						}
					}
				}

				if (new_color <= MIN_COLOR)
					new_color = MIN_COLOR;
				else if (new_color >= MAX_COLOR)
					new_color = MAX_COLOR;

				m[i][j][k] = (int) new_color;
			}
		}
	}
	// Free matrice originala
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
		free(image[i]);
    }
	free(image);

	return m;
}
