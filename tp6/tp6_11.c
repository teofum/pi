#include <assert.h>
#include <stdio.h>

#include "utils.h"

#define MAX_COL 10

void swap_rows(int m[][MAX_COL], int cols, int a, int b);

void sort_by_column(int m[][MAX_COL], int rows, int cols, int sort_col);

int vec_equals(const int v1[], const int v2[], int size) {
  for (int i = 0; i < size; i++)
    if (v1[i] != v2[i])
      return 0;
  return 1;
}

int main(void) {
  int m[][MAX_COL] = {
    {1, 2, 3, 4, 5},
    {6, 2, 8, 9, 10},
    {3, 5, 8, 2, 1},
    {8, 7, 3, 6, 7}
  };

  int m2[][MAX_COL] = {
    {1, 2, 3, 4, 5},
    {6, 2, 8, 9, 10},
    {3, 5, 8, 2, 1},
    {8, 7, 3, 6, 7}
  };

  sort_by_column(m, 4, 5, 2);

  for (int i = 0; i < 4; i++)
    assert(vec_equals(m[i], m2[i], 5));

  sort_by_column(m, 4, 5, 1);
  assert(vec_equals(m[0], m2[0], 5));
  assert(vec_equals(m[1], m2[2], 5));
  assert(vec_equals(m[2], m2[1], 5));
  assert(vec_equals(m[3], m2[3], 5));

  sort_by_column(m, 4, 5, 3);
  assert(vec_equals(m[0], m2[0], 5) || vec_equals(m[0], m2[3], 5));
  assert(vec_equals(m[1], m2[0], 5) || vec_equals(m[1], m2[3], 5));
  assert(vec_equals(m[2], m2[1], 5) || vec_equals(m[2], m2[2], 5));
  assert(vec_equals(m[3], m2[1], 5) || vec_equals(m[3], m2[2], 5));

  printf("OK!\n");
  return 0;
}

void swap_rows(int m[][MAX_COL], int cols, int a, int b) {
  for (int j = 0; j < cols; j++)
    swap_int(&m[a][j], &m[b][j]);
}

// Stable selection sort
void sort_by_column(int m[][MAX_COL], int rows, int cols, int sort_col) {
  sort_col--;
  for (int i = 0; i < rows; i++) {
    int j_min = i;
    for (int j = i + 1; j < rows; j++)
      if (m[j][sort_col] < m[i][sort_col])
        j_min = j;

    swap_rows(m, cols, i, j_min);
  }
}
