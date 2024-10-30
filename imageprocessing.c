#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#define zero 0
#define max 255
// TODO(aureliu.antonie) Task 1
int ***flip_horizontal(int ***image, int N, int M) {
        for (int i = 0; i < N; i++) {
           for (int j = 0; j < M/2; j++) {
              for (int j2 = 0; j2 < 3; j2++) {
                 int aux = image[i][j][j2];
                 image[i][j][j2] = image[i][M-j-1][j2];
                 image[i][M-j-1][j2] = aux;
              }
           }
        }
        return image;
}

// TODO(aureliu.antonie) Task 2
int ***rotate_left(int ***image, int N, int M) {
    int ***a = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        a[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
          for (int i = 0; i < M; i++) {
           for (int j = 0; j < N; j++) {
              for (int j2 = 0; j2 < 3; j2++) {
               a[i][j][j2] = image[j][M-i-1][j2];
              }
           }
        }
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
            free(image[i]);
        }
        free(image);

        return a;
}
// TODO(aureliu.antonie) Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
       int ***a = (int ***)malloc(h * sizeof(int **));
       for (int i = 0; i < h; i++) {
        a[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

        for (int i = y; i < y+h; i++) {
          for (int j = x; j < x+w; j++) {
           for (int j2 = 0; j2 < 3; j2++) {
           a[i-y][j-x][j2] = image[i][j][j2];
           }
          }
        }

        for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
            free(image[i]);
        }
        free(image);

  return a;
}
// TODO(aureliu.antonie) Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
        int n = N + 2 * rows;
        int m = M + 2 * cols;
        int ***a = (int ***)malloc(n * sizeof(int **));
        for (int i = 0; i < n; i++) {
        a[i] = (int **)malloc(m * sizeof(int *));
        for (int j = 0; j < m; j++) {
            a[i][j] = (int *)malloc(4 * sizeof(int));
        }
    }

        for (int i = 0; i < N+2*rows; i++) {
        for (int j = 0; j < M+2*cols; j++) {
        if (i<rows || i >= N + rows) {
        a[i][j][0] = new_R;
        a[i][j][1] = new_G;
        a[i][j][2] = new_B;
        } else {
        if (j<cols || j >= M + cols) {
        a[i][j][0] = new_R;
        a[i][j][1] = new_G;
        a[i][j][2] = new_B;
        } else {
        for (int j2 = 0; j2 < 3; j2++) {
        a[i][j][j2] = image[i-rows][j-cols][j2];
        }
        }
        }
        }
        }

        for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
            free(image[i]);
        }
        free(image);

  return a;
}

// TODO(aureliu.antonie) Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
        for (int i = y; i < N_dst && i-y < N_src; i++) {
        for (int j = x; j < M_dst && j-x <M_src; j++) {
        for (int j2 = 0; j2 < 3; j2++) {
        image_dst[i][j][j2] = image_src[i-y][j-x][j2];
        }
        }
        }
return image_dst;
}

// TODO(aureliu.antonie) Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
        int n = N;
        int m = M;
        int ***R = (int ***)malloc(n * sizeof(int **));
        for (int i = 0; i < n; i++) {
        R[i] = (int **)malloc(m * sizeof(int *));
        for (int j = 0; j < m; j++) {
            R[i][j] = (int *)malloc(4 * sizeof(int));
        }
    }
        for (int i=0; i < N; i++) {
        for (int j=0; j < M; j++) {
        int val = filter_size/2;
        float a = 0, b = 0, c = 0;
        for (int i2 = i-val; i2 <= i+val; i2++) {
        for (int j2 = j-val; j2 <= j+val; j2++) {
        if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M) {
        a += ((float)image[i2][j2][0]) * filter[i2-i+val][j2-j+val];
        b += ((float)image[i2][j2][1]) * filter[i2-i+val][j2-j+val];
        c += ((float)image[i2][j2][2]) * filter[i2-i+val][j2-j+val];
        }
        }
        }
        if (a < zero)
        a = zero;
        if (b < zero)
        b = zero;
        if (c < zero)
        c = zero;
        if (a > max)
        a = max;
        if (b > max)
        b = max;
        if (c > max)
        c = max;
        R[i][j][0] = ((int)a);
        R[i][j][1] = ((int)b);
        R[i][j][2] = ((int)c);
        }
        }

       for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
            free(image[i]);
        }
        free(image);
        return R;
}
