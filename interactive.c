#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
#define sizex 5
#define sizepath 105
#define marime 15
int main() {
// TODO(aureliu.antonie) Task 7
char x[sizex] ="";
int N = 0, M = 0;
char path[sizepath]="";
int nr = 0, nrf = 0;
int ****m = (int ****)malloc(marime*sizeof(int ***));
float ***f = (float ***)malloc(marime*sizeof(float **));
int lin[marime], col[marime], sizef[marime];
for (int i = 0; i < marime; i++) {
lin[i] = 0;
col[i] = 0;
sizef[i] = 0;
}
int nr2 = 0;

while (strcmp(x, "e") != 0) {
scanf("%s", x);
if(strcmp(x, "e") == 0) {
break;
} else if (strcmp(x, "l") == 0) {
        scanf("%d", &N);
        scanf("%d", &M);
        scanf("%s", path);
        m[nr] = (int ***)malloc(N * sizeof(int **));
       for (int i = 0; i < N; i++) {
        m[nr][i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            m[nr][i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    lin[nr] = N;
    col[nr] = M;
    read_from_bmp(m[nr], N, M, path);
    nr++;
} else if (strcmp(x, "s") == 0) {
scanf("%d", &nr2);
scanf("%s", path);
write_to_bmp(m[nr2], lin[nr2], col[nr2], path);
} else if (strcmp(x, "ah") == 0) {
scanf("%d", &nr2);
m[nr2] = flip_horizontal(m[nr2], lin[nr2], col[nr2]);
} else if (strcmp(x, "ar") == 0) {
scanf("%d", &nr2);
N = lin[nr2];
M = col[nr2];
m[nr2] = rotate_left(m[nr2], N, M);
lin[nr2] = M;
col[nr2] = N;
} else if (strcmp(x, "ac") == 0) {
scanf("%d", &nr2);
N = lin[nr2];
M = col[nr2];
int x = 0, y = 0, h = 0, w = 0;
scanf("%d", &x);
scanf("%d", &y);
scanf("%d", &w);
scanf("%d", &h);
m[nr2] = crop(m[nr2], N, M, x, y, h, w);
lin[nr2] = h;
col[nr2] = w;
} else if (strcmp(x, "ae") == 0) {
scanf("%d", &nr2);
N = lin[nr2];
M = col[nr2];
int rows = 0, cols = 0, r = 0, g = 0, b = 0;
scanf("%d", &rows);
scanf("%d", &cols);
scanf("%d", &r);
scanf("%d", &g);
scanf("%d", &b);
m[nr2] = extend(m[nr2], N, M, rows, cols, r, g, b);
lin[nr2] = N + 2 * rows;
col[nr2] = M + 2 * cols;
} else if (strcmp(x, "ap") == 0) {
int dst = 0, src = 0, x = 0, y = 0;
scanf("%d", &dst);
scanf("%d", &src);
scanf("%d", &x);
scanf("%d", &y);
m[dst] = paste(m[dst], lin[dst], col[dst], m[src], lin[src], col[src], x, y);
} else if (strcmp(x, "cf") == 0) {
int size = 0;
scanf("%d", &size);
f[nrf] = (float **)malloc(size * sizeof(float *));
for (int i = 0; i < size; i++) {
f[nrf][i] = (float *)malloc(size * sizeof(float));
}
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
scanf("%f", &f[nrf][i][j]);
}
}
sizef[nrf] = size;
nrf++;
} else if (strcmp(x, "af") == 0) {
int indeximg = 0, indexfilter = 0;
scanf("%d", &indeximg);
scanf("%d", &indexfilter);
m[indeximg] = apply_filter(m[indeximg], lin[indeximg], col[indeximg], f[indexfilter], sizef[indexfilter]);
} else if (strcmp(x, "df") == 0) {
int index = 0;
scanf("%d", &index);
  for (int i = 0; i < sizef[index]; i++) {
            free(f[index][i]);
        }
        free(f[index]);
for (int i = index; i <= nrf-2; i++) {
f[i] = f[i+1];
sizef[i] = sizef[i+1];
}
sizef[nrf-1] = 0;
nrf--;
} else if (strcmp(x, "di") == 0) {
int index = 0;
scanf("%d", &index);
  for (int i = 0; i < lin[index]; i++) {
       for (int j = 0; j < col[index]; j++) {
            free(m[index][i][j]);
        }
            free(m[index][i]);
        }
        free(m[index]);
for (int i = index; i <= nr-2; i++) {
m[i] = m[i+1];
lin[i] = lin[i+1];
col[i] = col[i+1];
}
lin[nr-1] = 0;
col[nr-1] = 0;
nr--;
}
}
  for (int i2 = 0; i2 < marime; i2++) {
  if (lin[i2] != 0) {
  for (int i = 0; i < lin[i2]; i++) {
       for (int j = 0; j < col[i2]; j++) {
            free(m[i2][i][j]);
        }
            free(m[i2][i]);
        }
        free(m[i2]);
        } else {
        break;
        }
     }
     free(m);
  for (int i2 = 0; i2 < marime; i2++) {
  if (sizef[i2] != 0) {
  for (int i = 0; i < sizef[i2]; i++) {
           free(f[i2][i]);
        }
        free(f[i2]);
        } else {
        break;
        }
}
    free(f);

    return 0;
}
