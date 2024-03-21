#include <assert.h>
#include <stdio.h>

#define MAX_SIZE 4

void mat_mul(unsigned int n, const int m1[][n], const int m2[][n], int m3[][n]);
int mat_product_at(
    unsigned int n,
    const int m1[][n],
    const int m2[][n],
    unsigned int i,
    unsigned int j
);

int main(void) {
  int m1[MAX_SIZE][MAX_SIZE] = {
      {1, 2, 3, 4},
      {11, 12, 13, 14},
      {21, 22, 23, 24},
      {31, 32, 33, 34},
  };

  int m2[MAX_SIZE][MAX_SIZE] = {
      {2, 1, 3, 4},
      {3, 4, 5, 2},
      {2, 5, 10, 11},
      {21, 12, 13, 14},
  };

  int zero[MAX_SIZE][MAX_SIZE] = {{0}};

  int out[MAX_SIZE][MAX_SIZE];

  mat_mul(MAX_SIZE, m1, zero, out);

  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++)
      assert(out[i][j] == 0);
  }

  for (int i = 0; i < MAX_SIZE; i++) {
    zero[i][i] = 1;
  }
  mat_mul(MAX_SIZE, m1, zero, out);
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++)
      assert(out[i][j] == m1[i][j]);
  }

  int res[][MAX_SIZE] = {
      {98, 72, 95, 97},
      {378, 292, 405, 407},
      {658, 512, 715, 717},
      {938, 732, 1025, 1027}
  };

  mat_mul(MAX_SIZE, m1, m2, out);
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++)
      assert(out[i][j] == res[i][j]);
  }

  int res3[][3] = {{14, 24, 43}, {84, 124, 223}, {154, 224, 403}};

  int m4[3][3] = {{1, 2, 3}, {11, 12, 13}, {21, 22, 23}};

  int m5[3][3] = {{2, 1, 3}, {3, 4, 5}, {2, 5, 10}};

  int m6[3][3];

  mat_mul(3, m4, m5, m6);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      assert(m6[i][j] == res3[i][j]);
    }
  }

  puts("OK!");
}

void mat_mul(
    unsigned int n,
    const int m1[][n],
    const int m2[][n],
    int m3[][n]
) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m3[i][j] = mat_product_at(n, m1, m2, i, j);
    }
  }
}

int mat_product_at(
    unsigned int n,
    const int m1[][n],
    const int m2[][n],
    unsigned int i,
    unsigned int j
) {
  int product = 0;
  for (int k = 0; k < n; k++) {
    product += m1[i][k] * m2[k][j];
  }
  return product;
}
