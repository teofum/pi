#include <assert.h>
#include <stdio.h>

#define DIM 4

typedef enum colors { black = 0, white, blue, red, purple, orange } colors;
typedef unsigned char uchar;

int checkBoard(uchar board[DIM][DIM]);
int checkRow(uchar row[DIM], uchar evenColor, uchar oddColor);

int main(void) {
  unsigned char t[DIM][DIM] = {
      {black, white, black, white},
      {white, black, white, black},
      {black, white, black, white},
      {white, black, white, black}
  };
  // Es un tablero válido
  assert(checkBoard(t) == 1);
  unsigned char t2[DIM][DIM] = {
      {black, white, black, white},
      {white, black, white, black},
      {black, white, black, white},
      {white, black, white, blue}
  };
  // No es válido pues se usaron más de dos colores
  assert(checkBoard(t2) == 0);
  unsigned char t3[DIM][DIM] = {
      {black, white, black, white},
      {white, black, white, black},
      {white, black, white, black},
      {black, white, black, white},
  };
  // No es válido pues hay dos posiciones adyacentes del mismo color
  assert(checkBoard(t3) == 0);

  printf("OK!\n");
  return 0;
}

int checkBoard(uchar board[DIM][DIM]) {
  // if the board is valid, the first two squares of the first row should be
  // different colors, and these will be the colors used throughout the board
  // this assumes DIM >= 2 but a 1x1 board makes no sense
  uchar color1 = board[0][0];
  uchar color2 = board[0][1];
  if (color1 == color2)
    return 0;

  int valid = 1;
  for (int i = 0; i < DIM && valid; i++) {
    if (i % 2 == 0) {
      valid = checkRow(board[i], color1, color2);
    } else {
      valid = checkRow(board[i], color2, color1);
    }
  }

  return valid;
}

int checkRow(uchar row[DIM], uchar evenColor, uchar oddColor) {
  for (int j = 0; j < DIM; j++) {
    if (row[j] != ((j % 2 == 0) ? evenColor : oddColor))
      return 0;
  }

  return 1;
}
