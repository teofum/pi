#include <stdio.h>

#define N 4

int check(int m[N][N]);
int check_row(int row[N], int i);

int main(void) {
  int mat1[N][N] = {
      {3, 4, 1, 2}, {8, 7, 6, 5}, {9, 10, 11, 12}, {15, 16, 13, 14}
  };
  int mat2[N][N] = {
      {3, 1, 1, 2}, {8, 7, 6, 5}, {9, 10, 11, 12}, {15, 16, 13, 14}
  };
  int mat3[N][N] = {
      {3, 4, 1, 2}, {8, 7, 6, 5}, {9, 10, 11, 12}, {15, 16, 13, 11}
  };

  printf("%d %d %d\n", check(mat1), check(mat2), check(mat3));

  return 0;
}

int check(int m[N][N]) {
  for (int i = 0; i < N; i++)
    if (!check_row(m[i], i))
      return 0;

  return 1;
}

int check_row(int row[N], int i) {
  // the ith row of the matrix should contain the numbers
  // from i * N + 1 to i * N + N, not necessarily in order
  int contains[N] = {0};

  for (int j = 0; j < N; j++) {
    // first, validate the number is in range
    int v = row[j] - i * N;
    if (v < 1 || v > N)
      return 0;

    // then, validate no numbers are repeated
    if (contains[v - 1])
      return 0;
    else
      contains[v - 1]++;
  }

  return 1;
}
