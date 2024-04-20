#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#define caselesscmp(a, b) (tolower(a) == tolower(b))

typedef unsigned int uint;

// valid C as of later standards, replace with char mat[][COLS], COLS a symbolic
// constant for older std
int isWordLadder(uint words, int len, char mat[][len]);

// returns the position of a different letter between words, or -1 if there are
// multiple or no different letters
int changePos(int len, char word1[len], char word2[len]);

int main(void) {
  char wordMatrix[][4] = {
      {'T', 'e', 'S', 't'},
      {'b', 'e', 'S', 'T'},
      {'B', 'E', 's', 'o'},
      {'B', 'E', 'S', 'A'}
  };
  // Considerando todas las filas no es escalera pues los últimos dos cambios
  // son en la última letra
  assert(!isWordLadder(4, 4, wordMatrix));
  // Considerando una sola fila es escalera
  assert(isWordLadder(1, 4, wordMatrix) == 1);
  // Considerando las tres primeras filas es escalera
  assert(isWordLadder(3, 4, wordMatrix) == 1);

  char wordMatrix2[][3] = {
      {'T', 'e', 'S'}, {'t', 'b', 'e'}, {'S', 'b', 'E'}, {'B', 'b', 'e'}
  };
  // TeS -> Tbe cambian dos letras
  assert(!isWordLadder(4, 3, wordMatrix2));

  char wordMatrix3[][3] = {{'a', 'm', 'o'}, {'a', 'r', 'o'}, {'o', 's', 'a'}};
  // aro -> osa cambian tres letras
  assert(!isWordLadder(3, 3, wordMatrix3));

  puts("OK!");

  return 0;
}

int isWordLadder(uint words, int len, char mat[][len]) {
  if (words == 0)
    return 0;
  if (words == 1)
    return 1;

  int ladder = 1, lastChange = -1;
  for (int i = 1; i < words && ladder; i++) {
    int change = changePos(len, mat[i - 1], mat[i]);
    // if the difference is not exactly one letter, or the same position changed
    // twice, matrix is not a word ladder
    ladder = change != -1 && change != lastChange;
    lastChange = change;
  }

  return ladder;
}

int changePos(int len, char word1[len], char word2[len]) {
  int change = -1, found = 0;
  for (int i = 0; i < len && found < 2; i++) {
    if (!caselesscmp(word1[i], word2[i])) {
      change = found ? -1 : i;
      found++;
    }
  }

  return change; // -1 if no change or multiple changes, otherwise change idx
}
