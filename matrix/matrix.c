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
double getTime();
float** matrixTranspose(float **matrix, int m, int n);
void matrixMultiplicationT(float **matrixA, float **matrixB, float **matrixC, int m, int n, int k);

int main(int argc, char** argv) {
  int m, n, k;
  float **a, **b, **c, **t;
  struct timespec start, end;
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

  double s = getTime();
  matrixMultiplicationT(a, b, c, m, m, k);
  printf("Time Taken: %0.9lf\n", getTime() - s);
  s = getTime();
  matrixMultiplication(a, b, c, m, m, k);
  printf("Time Taken: %0.9lf\n", getTime() - s);

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

double getTime() {
  struct timespec var;
  //clock_gettime(CLOCK_MONOTONIC, &var);
  clock_gettime(CLOCK_BOOTTIME, &var);
  return (var.tv_sec + var.tv_nsec * 1e-9);
}

float** matrixTranspose(float **matrix, int m, int n) {
  float **matrixT = accocateMatrix(n, m);
  int i, j;
  /*
  if (m == n) {
    for (i = 0; i < m; i++) {
      matrixT[i][i] = matrix[i][i];
      for (j = i+1; j < n; j++) {
        matrixT[i][j] = matrix[j][i];
        matrixT[j][i] = matrix[i][j];
      }
    }
  } else {
  */
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        matrixT[j][i] = matrix[i][j];
      }
    }
  //}
  return matrixT;
}

void matrixMultiplicationT(float **matrixA, float **matrixB, float **matrixC, int m, int n, int k) {
  float **matrixT = matrixTranspose(matrixB, k, n);
  int i, j, l;
  float sum = 0.0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      sum = 0.0;
      for (l = 0; l < k; l++) {
        sum += matrixA[i][l] * matrixT[j][l];
      }
      matrixC[i][j] = sum;
    }
  }
}
