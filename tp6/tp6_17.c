#include <assert.h>
#include <stdio.h>

#define N 4
#define M 5

int flatten_rows(int mat[][M], int vec[]);

int main(void) {
  int m1[N][M] = {
      {1, 2, 3, 4, 5}, {1, 2, 13, 4, 5}, {1, 2, 4, 4, 5}, {1, 2, -3, 4, 5}
  };
  int vec[N];
  int n = flatten_rows(m1, vec);
  assert(n == 2);
  assert(vec[0] == 12345);
  assert(vec[1] == 12445);

  int m2[N][M] = {
      {1, 0, 3, 4, 5}, {0, 2, 1, 4, 5}, {9, 9, 9, 9, 9}, {0, 0, 1, 4, 5}
  };
  n = flatten_rows(m2, vec);
  assert(n == 4);
  assert(vec[0] == 10345);
  assert(vec[1] == 2145);
  assert(vec[2] == 99999);
  assert(vec[3] == 145);

  int m3[N][M] = {
      {11, 0, 3, 4, 5}, {0, 2, 1, 14, 5}, {9, 9, 9, 91, 9}, {0, 0, 1, 14, 5}
  };
  n = flatten_rows(m3, vec);
  assert(n == 0);

  printf("OK!\n");
  return 0;
}

int flatten_rows(int mat[][M], int vec[]) {
  int i_out = 0;
  for (int i = 0; i < N; i++) {
    int row = 0, power = 1;

    // Iterate row backwards so we can start at last digit
    // This way we can init power to 1 and save an extra loop/pow call
    for (int j = M - 1; j >= 0; j--) {
      int v = mat[i][j];

      // If negative or multiple digits, skip entire row
      if (v < 0 || v > 9) {
        row = -1;
        break;
      }

      // Add digit
      row += v * power;
      power *= 10;
    }

    if (row >= 0)
      vec[i_out++] = row;
  }

  return i_out;
}
