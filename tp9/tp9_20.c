#include <assert.h>
#include <stdio.h>
#include <string.h>

#define DIM 9

int sudoku_solver(char board[DIM][DIM]);

int validate_cell(char board[DIM][DIM], int i0, int j0);

int main(void) {
  // Una vacia tiene que tener solucion
  char sudoku[DIM][DIM] = {{0}};

  assert(sudoku_solver(sudoku) == 1);
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      printf("%1d ", sudoku[i][j]);
    }
    putchar('\n');
  }

  printf("\nUno sin solucion\n");
  char sudoku2[DIM][DIM] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {5, 6, 7, 8, 9, 1, 2, 3, 4},
    {8, 9, 1, 2, 3, 7, 5, 6, 0},
  };

  assert(sudoku_solver(sudoku2) == 0);
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      printf("%1d ", sudoku2[i][j]);
    }
    putchar('\n');
  }

  printf("\nUno con solucion pero con celdas no vacias\n");
  char sudoku3[DIM][DIM] = {
    {0, 2, 0, 3, 0, 0, 0, 0, 0},
    {9, 4, 0, 6, 8, 7, 0, 0, 0},
    {1, 6, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 9, 2, 5, 4, 0},
    {0, 0, 0, 0, 6, 0, 0, 0, 0},
    {8, 0, 0, 4, 0, 3, 0, 1, 6},
    {0, 1, 0, 0, 7, 6, 0, 8, 2},
    {0, 0, 0, 9, 0, 0, 6, 0, 0},
    {7, 0, 6, 0, 0, 4, 9, 3, 0}
  };

  assert(sudoku_solver(sudoku3) == 1);
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      printf("%1d ", sudoku3[i][j]);
    }
    putchar('\n');
  }

  return 0;
}

int sudoku_solver(char board[DIM][DIM]) {
  // find the first empty cell
  int i = 0, j = 0;
  while (i < DIM && board[i][j] != 0) {
    j++;
    if (j == DIM) {
      j = 0;
      i++;
    }
  }

  if (i == DIM) return 1; // full board assumed valid

  // try each value from 1-9
  for (int k = 1; k <= 9; k++) {
    board[i][j] = k;

    // if it's valid for this place,
    if (validate_cell(board, i, j)) {
      // try to solve the rest of the board with this value in place
      int sol = sudoku_solver(board);
      if (sol) return 1;
    }
  }

  // no valid value for this place, there is no solution
  // backtrack or end if root call
  board[i][j] = 0;
  return 0;
}

int validate_cell(char board[DIM][DIM], int i0, int j0) {
  char buf[DIM] = {0};

  // check row
  for (int j = 0; j < DIM; j++) {
    char val = board[i0][j];
    if (val != 0 && buf[(int) val - 1]++)
      return 0;
  }

  // check column
  memset(buf, 0, DIM);
  for (int i = 0; i < DIM; i++) {
    char val = board[i][j0];
    if (val != 0 && buf[(int) val - 1]++)
      return 0;
  }

  // check block
  memset(buf, 0, DIM);
  i0 = (i0 / 3) * 3;
  j0 = (j0 / 3) * 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      char val = board[i0 + i][j0 + j];
      if (val != 0 && buf[(int) val - 1]++)
        return 0;
    }
  }

  return 1;
}
