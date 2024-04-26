#include <stdio.h>
#include <assert.h>

#define MAX 10
#define N_DIRS 4

#define inbounds(i, j, s) ((i) >= 0 && (i) < (s) && (j) >= 0 && (j) < (s))

typedef enum {
  RIGHT = 1, UP = 2, LEFT = 4, DOWN = 8
} direction;

direction directions[N_DIRS] = {
  RIGHT + UP, LEFT + UP, LEFT + DOWN, RIGHT + DOWN
};

void flip(int *v);

void replace_diagonals(int mat[][MAX], int dim, size_t i0, size_t j0);

void replace_diagonals_dir(
  int mat[][MAX],
  int dim,
  size_t i,
  size_t j,
  direction dir
);

int main(void) {
  int m[5][MAX] = {{1, 0, 1, 0, 1},
                   {0, 1, 1, 1, 1},
                   {1, 0, 0, 1, 0},
                   {1, 1, 1, 0, 1},
                   {0, 0, 0, 0, 0}};
  replace_diagonals(m, 5, 1, 2);

  int m2[5][MAX] = {{1, 1, 1, 1, 1},
                    {0, 1, 0, 1, 1},
                    {1, 1, 0, 0, 0},
                    {0, 1, 1, 0, 0},
                    {0, 0, 0, 0, 0}};

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      assert(m[i][j] == m2[i][j]);

  replace_diagonals(m, 5, 1, 2);
  replace_diagonals(m, 5, 1, 2);

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      assert(m[i][j] == m2[i][j]);

  printf("OK!\n");
  return 0;
}

void flip(int *v) {
  *v = !(*v);
}

void replace_diagonals(int mat[][MAX], int dim, size_t i0, size_t j0) {
  flip(&mat[i0][j0]);
  for (int d = 0; d < N_DIRS; d++) {
    replace_diagonals_dir(mat, dim, i0, j0, directions[d]);
  }
}

void replace_diagonals_dir(
  int mat[][MAX],
  int dim,
  size_t i,
  size_t j,
  direction dir
) {
  size_t di = dir & DOWN ? 1 : (dir & UP ? -1 : 0);
  size_t dj = dir & RIGHT ? 1 : (dir & LEFT ? -1 : 0);
  i += di;
  j += dj;

  if (inbounds(i, j, dim)) {
    flip(&mat[i][j]);
    replace_diagonals_dir(mat, dim, i, j, dir);
  }
}
