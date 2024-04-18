#include <stdio.h>

#define COLS 4
#define SIZE 4

typedef unsigned int uint;

void clear_if_sum(int m[][COLS], uint rows, uint cols, uint row);

void clear_row(int m[][COLS], uint cols, uint row);

/**
 * Returns 1 if row c is the sum of rows a and b, 0 otherwise
 */
int row_is_sum(int m[][COLS], uint cols, uint row_a, uint row_b, uint row_c);

void print_mat(int m[][COLS], uint rows, uint cols);

int main(void) {
  int mat[][COLS] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 5}, {6, 8, 10, 12}};
  int mat2[][COLS] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 5}, {6, 8, 10, 12}};
  int mat3[][COLS] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 5}, {6, 8, 10, 12}};
  int mat4[][COLS] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 5}, {6, 8, 10, 12}};
  printf("Matrix =\n");
  print_mat(mat, SIZE, SIZE);

  clear_if_sum(mat, SIZE, SIZE, 0);
  printf("Called clear_if_sum with row = 0:\n");
  print_mat(mat, SIZE, SIZE);

  clear_if_sum(mat2, SIZE, SIZE, 1);
  printf("Called clear_if_sum with row = 1:\n");
  print_mat(mat2, SIZE, SIZE);

  clear_if_sum(mat3, SIZE, SIZE, 2);
  printf("Called clear_if_sum with row = 2:\n");
  print_mat(mat3, SIZE, SIZE);

  clear_if_sum(mat4, SIZE, SIZE, 3);
  printf("Called clear_if_sum with row = 3:\n");
  print_mat(mat4, SIZE, SIZE);

  return 0;
}

void clear_if_sum(int m[][COLS], uint rows, uint cols, uint row) {
  if (row >= rows || cols > COLS) // Sanity check
    return;

  // For each pair of rows i != row, k != row test if row is the sum i + k
  for (int i = 0; i < rows - 1; i++)
    for (int k = i + 1; k < rows; k++)
      if (i != row && k != row && row_is_sum(m, cols, i, k, row)) {
        clear_row(m, cols, row);
        return; // No need to check more rows if we found a valid pair
      }

  return;
}

void clear_row(int m[][COLS], uint cols, uint row) {
  for (int j = 0; j < cols; j++)
    m[row][j] = 0;
}

int row_is_sum(int m[][COLS], uint cols, uint row_a, uint row_b, uint row_c) {
  for (int j = 0; j < cols; j++)
    if (m[row_a][j] + m[row_b][j] != m[row_c][j])
      return 0;

  return 1;
}

void print_mat(int m[][COLS], uint rows, uint cols) {
  for (int i = 0; i < rows; i++) {
    printf("| ");
    for (int j = 0; j < cols; j++) {
      printf("%2d ", m[i][j]);
    }
    printf("|\n");
  }
}
