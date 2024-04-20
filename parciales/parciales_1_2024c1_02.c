#include <assert.h>
#include <stdio.h>

#define isqueen(c) ((c) == '1')
#define inbounds(j, n) ((j) >= 0 && (j) < (n))

// type aliases to keep things short
typedef unsigned int uint;

// this is valid C as of later standards
// for older standards: int nQueens(uint n, char board[][N]), with N a #define
// constant
int nQueens(uint n, char board[][n]);

// returns the index of the queen in this row, or -1 if there is more than one
// or if there are none
int checkRow(uint n, char board[][n], int i);

// given the position of a queen, checks column and diagonals, returns 0 if
// threatened, 1 if not
int checkQueen(uint n, char board[][n], int i0, int j0);

int main(void) {
  char board[][8] = {
      {'0', '0', '0', '0', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '1', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '0'},
      {'0', '1', '0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '1', '0'},
      {'1', '0', '0', '0', '1', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '1'},
  };
  // por ejemplo, hay tres reinas en la columna 4 y dos en la fila 6
  assert(nQueens(8, board) == 0);

  char board2[][6] = {
      {'0', '0', '0', '1', '0', '0'}, {'1', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '1', '0'}, {'0', '1', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '1'}, {'0', '0', '1', '0', '0', '0'}
  };
  // Hay 6 reinas y no se atacan, retorna true
  assert(nQueens(6, board2));

  char board3[][6] = {
      {'0', '0', '1', '0', '0', '0'}, {'1', '0', '0', '0', '0', '0'},
      {'0', '1', '0', '0', '0', '0'}, {'0', '0', '0', '0', '1', '0'},
      {'0', '0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0', '1'}
  };
  // Las reinas en (1,0) y (2,1) se amenazan en forma diagonal
  assert(nQueens(6, board3) == 0);

  char board4[][6] = {
      {'0', '0', '0', '1', '0', '0'}, {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '1', '0'}, {'0', '1', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '1'}, {'0', '0', '1', '0', '0', '0'}
  };
  // No se amenazan pero hay menos de 6 reinas
  assert(nQueens(6, board4) == 0);

  // No hay solución para tableros de dimensión 2 o 3
  assert(nQueens(3, board2) == 0);
  assert(nQueens(2, board2) == 0);

  // En un tablero de 1x1 debe haber una reina
  char board1[][1] = {{'1'}};
  assert(nQueens(1, board1));

  puts("OK!");

  return 0;
}

int nQueens(uint n, char board[][n]) {
  int valid = 1;

  // handle special cases
  if (n == 1) {
    valid = isqueen(board[0][0]);
  } else if (n <= 3) {
    valid = 0; // no solutions exist for n=2, n=3
  } else {
    // general case (n >= 4)
    for (int i = 0; i < n && valid; i++) {
      int queenCol = checkRow(n, board, i);
      if (queenCol == -1) {
        valid = 0; // either more than one queen in this row, or none
        // to have exactly n queens in n rows there must be exactly one per row
        // if there is none, either we don't have n queens or some other row has
        // more than one, in either case the board is invalid
      } else {
        // found exactly one queen, validate it's not threatened
        valid = checkQueen(n, board, i, queenCol);
      }
    }
  }

  // no need to check total # of queens, if the board is valid there is exactly
  // one queen per row and thus there are n queens
  return valid;
}

int checkRow(uint n, char board[][n], int i) {
  int queenJ = -1, found = 0;
  // early exit if we find a second queen (row is immediately invalid)
  for (int j = 0; j < n && found < 2; j++) {
    if (isqueen(board[i][j])) {
      queenJ = found ? -1 : j; // reset to -1 if this is the second queen
      found++;
    }
  }

  return queenJ; // if no queen was found, queenJ stays at -1
}

int checkQueen(uint n, char board[][n], int i0, int j0) {
  int threatened = 0;

  // note we only need to check "downstream" from the current queen: because
  // queens threaten each other symetrically, and we're going through the board
  // top to bottom, if the board so far is valid we can be sure no queen above
  // this one threatens it, because in that case this queen would have
  // threatened it in turn and the board would've been invalid﻿﻿

  // first, check column, exit early if threatened
  for (int i = i0 + 1; i < n && !threatened; i++) {
    threatened = isqueen(board[i][j0]);
  }

  // check diagonals, exit early if threatened
  for (int i = i0 + 1; i < n && !threatened; i++) {
    int di = i - i0;
    int j1 = j0 + di;
    int j2 = j0 - di;

    threatened = (inbounds(j1, n) && isqueen(board[i][j1])) ||
                 (inbounds(j2, n) && isqueen(board[i][j2]));
  }

  return !threatened; // return 1 if valid (not threatened), 0 if threatened
}
