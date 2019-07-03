/*
 * File Name: matrix.c
 * Author: Asis Patra
 * Date: 2019-07-03
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 1

float** accocateMatrix(int m, int n);
void initMatrix(float **matrix, int m, int n);
void freeMatrix(float **matrix, int m);
void displayMatrix(float **matrix, int m, int n);
void matrixMultiplication(float **matrixA, float **matrixB, float **matrixC, int m, int n, int k);

int main(int argc, char** argv) {
  int m, n, k;
  float **a, **b, **c;
  if (!(argc == 2 || argc == 4)) {
    fprintf(stderr, "Usage: %s <M, N, K> OR %s <N>\n", argv[0], argv[0]);
    exit(1);
  }
  if (argc == 2) {
    sscanf(argv[1], "%d", &m);
    sscanf(argv[1], "%d", &n);
    sscanf(argv[1], "%d", &k);
  } else if (argc == 4) {
    sscanf(argv[1], "%d", &m);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%d", &k);
  }
  srand(time(0));
  a = accocateMatrix(m, k);
  b = accocateMatrix(k, n);
  c = accocateMatrix(m, n);
  initMatrix(a, m, k);
  initMatrix(b, k, n);

  //printf("### Matrix A:\n");
  //displayMatrix(a, m, k);
  //printf("### Matrix B:\n");
  //displayMatrix(b, k, n);

  matrixMultiplication(a, b, c, m, m, k);

  //printf("### Matrix C:\n");
  //displayMatrix(c, m, n);

  freeMatrix(a, m);
  freeMatrix(b, k);
  freeMatrix(c, m);
  return 0;
}

float** accocateMatrix(int m, int n) {
  int i;
  float** matrix;
  matrix = (float**) malloc (m * sizeof(float*));
  for (i = 0; i < m; i++) {
    matrix[i] = (float*) malloc (n * sizeof(float));
  }
  return matrix;
}

void initMatrix(float **matrix, int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matrix[i][j] = ((float)rand()/(float)(RAND_MAX)) * RANGE;
    }
  }
}

void freeMatrix(float **matrix, int m) {
  int i;
  for (i = 0; i < m; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void displayMatrix(float **matrix, int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%f " , matrix[i][j]);
    }
    printf("\n");
  }
}

void matrixMultiplication(float **matrixA, float **matrixB, float **matrixC, int m, int n, int k) {
  int i, j, l;
  float sum;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      sum = 0.0;
      for (l = 0; l < k; l++) {
        sum += matrixA[i][l] * matrixB[l][j];
      }
      matrixC[i][j] = sum;
    }
  }
}
