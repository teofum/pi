#include <assert.h>
#include <stdio.h>

#define BLOCK_SIZE 3
#define SIZE 9

void clear(int v[]);
int validate_row(char m[][SIZE], int i);
int validate_col(char m[][SIZE], int j);
int validate_block(char m[][SIZE], int ib, int jb);
int sudoku_validate(char m[][SIZE]);

int main(void) {
  char sudoku[SIZE][SIZE] = {{0}};

  assert(sudoku_validate(sudoku) == 0);
  printf("Test 1 OK!\n");

  char sudoku2[SIZE][SIZE] = {
      {3, 8, 1, 9, 7, 6, 5, 4, 2}, //
      {2, 4, 7, 5, 3, 8, 1, 9, 6}, //
      {5, 6, 9, 2, 1, 4, 8, 7, 3}, //
      {6, 7, 4, 8, 5, 2, 3, 1, 9}, //
      {1, 3, 5, 7, 4, 9, 6, 2, 8}, //
      {9, 2, 8, 1, 6, 3, 7, 5, 4}, //
      {4, 1, 2, 6, 8, 5, 9, 3, 7}, //
      {7, 9, 6, 3, 2, 1, 4, 8, 5}, //
      {8, 5, 3, 4, 9, 7, 2, 6, 1}
  };

  assert(sudoku_validate(sudoku2) == 1);
  printf("Test 2 OK!\n");

  char sudoku3[SIZE][SIZE] = {
      {2, 8, 1, 9, 7, 6, 5, 4, 2}, //
      {3, 4, 7, 5, 3, 8, 1, 9, 6}, //
      {5, 6, 9, 2, 1, 4, 8, 7, 3}, //
      {6, 7, 4, 8, 5, 2, 3, 1, 9}, //
      {1, 3, 5, 7, 4, 9, 6, 2, 8}, //
      {9, 2, 8, 1, 6, 3, 7, 5, 4}, //
      {4, 1, 2, 6, 8, 5, 9, 3, 7}, //
      {7, 9, 6, 3, 2, 1, 4, 8, 5}, //
      {8, 5, 3, 4, 9, 7, 2, 6, 1}
  };

  assert(sudoku_validate(sudoku3) == 0);
  printf("Test 3 OK!\n");

  // Cuando se tomó este ejercicio en un parcial, en una de las respuestas
  // sólo chequeaban que la suma de cada fila, columna y cuadrado fuera 45
  char sudoku4[SIZE][SIZE] = {
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}, //
      {5, 5, 5, 5, 5, 5, 5, 5, 5}
  };

  assert(sudoku_validate(sudoku4) == 0);
  printf("Test 4 OK!\n");

  char sudoku5[SIZE][SIZE] = {
      {3, 8, 1, 9, 7, 6, 5, 4, 12}, //
      {2, 4, 7, 5, 3, 8, 1, 9, 6},  //
      {5, 6, 9, 2, 1, 4, 8, 7, 3},  //
      {6, 7, 4, 8, 5, 2, 3, 1, 9},  //
      {1, 3, 5, 7, 4, 9, 6, 2, 8},  //
      {9, 2, 8, 1, 6, 3, 7, 5, 4},  //
      {4, 1, 2, 6, 8, 5, 9, 3, 7},  //
      {7, 9, 6, 3, 2, 1, 4, 8, 5},  //
      {8, 5, 3, 4, 9, 7, 2, 6, 1}
  };

  assert(sudoku_validate(sudoku5) == 0);
  printf("Test 5 OK!\n");

  printf("All tests OK!\n");

  return 0;
}

// Helper function to clear a buffer
void clear(int v[]) {
  for (int i = 0; i < SIZE; i++)
    v[i] = 0;
}

// Validates a Sudoku row
// Does bound-checks on the cell values, so this should be called first!
int validate_row(char m[][SIZE], int i) {
  // We'll use this to check for repeats: when we find a cell with value N,
  // we'll check the Nth position, then increment it. If we find the Nth
  // position in the buffer is one, the value is repeated.
  static int validation_buffer[SIZE] = {0};
  clear(validation_buffer);

  for (int j = 0; j < SIZE; j++) {
    int val = m[i][j];
    if (val < 1 || val > SIZE || validation_buffer[val - 1]++)
      return 0;
  }

  return 1;
}

// Validates a Sudoku column
// Doesn't do any bound-checks on the cell values.
int validate_col(char m[][SIZE], int j) {
  static int validation_buffer[SIZE] = {0};
  clear(validation_buffer);

  for (int i = 0; i < SIZE; i++) {
    int val = m[i][j];
    if (validation_buffer[val - 1]++)
      return 0;
  }

  return 1;
}

// Validates a Sudoku block (3x3 square)
// Doesn't do any bound-checks on the cell values.
int validate_block(char m[][SIZE], int ib, int jb) {
  static int validation_buffer[SIZE] = {0};
  clear(validation_buffer);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      int val = m[ib + i][jb + j];
      if (validation_buffer[val - 1]++)
        return 0;
    }
  }

  return 1;
}

int sudoku_validate(char m[][SIZE]) {

  // Pass 1: validate rows
  for (int i = 0; i < SIZE; i++)
    if (!validate_row(m, i))
      return 0;

  // Since the first pass checks every cell, we don't need to bother with bounds
  // checks on subsequent passes: if any values were out of bounds, the function
  // will never reach this point.

  // Pass 2: validate columns
  for (int j = 0; j < SIZE; j++)
    if (!validate_col(m, j))
      return 0;

  // Pass 2: validate blocks
  for (int ib = 0; ib < SIZE; ib += BLOCK_SIZE) {
    for (int jb = 0; jb < SIZE; jb += BLOCK_SIZE) {
      if (!validate_block(m, ib, jb))
        return 0;
    }
  }

  return 1; // Yay!
}
