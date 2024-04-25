#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "vector.h"

#define COLS 7
#define ROWS 6
#define N_DIRS 8

#define inbounds(i, j) ((i) >= 0 && (i) < ROWS && (j) >= 0 && (j) < COLS)

// encode directions as flags so we can do a neat trick later
typedef enum {
  RIGHT = 1, UP = 2, LEFT = 4, DOWN = 8
} direction;

direction directions[N_DIRS] = {
  RIGHT, RIGHT + UP, UP, LEFT + UP, LEFT, LEFT + DOWN, DOWN, RIGHT + DOWN
};

typedef struct {
  const char *word;
  size_t row, col;
  direction dir;
} position;

position *solve(const char **words, const char mat[ROWS][COLS]);

void find_word(const char *word, const char mat[ROWS][COLS], vector *found);

void find_word_at(
  const char *word,
  const char mat[ROWS][COLS],
  vector *found,
  position *pos
);

int find_word_at_dir(
  const char *word,
  const char mat[ROWS][COLS],
  position *pos
);

int main(void) {
  const char *words[] = {"ARRE", "CANCION", "CAPA", "ERROR", "ORCO", "PERRO",
                         "PERTINAZ", "REA", "RIO", ""};

  char mat[ROWS][COLS] = {
    {'X', 'X', 'X', 'O', 'X', 'X', 'X'},
    {'A', 'P', 'A', 'C', 'Y', 'Y', 'O'},
    {'Z', 'E', 'Z', 'R', 'Z', 'C', 'X'},
    {'E', 'R', 'R', 'O', 'R', 'X', 'X'},
    {'X', 'R', 'I', 'O', 'I', 'E', 'X'},
    {'X', 'O', 'X', 'X', 'O', 'X', 'X'}
  };

  position *res = solve(words, mat);

  int expected = 9;
  int count = 0;
  while (res[count].word != NULL)
    printf("%s\n", res[count++].word);
  assert(count == expected);

  assert(strcmp(res[0].word, "ARRE") == 0);
  assert(res[0].row == 1);
  assert(res[0].col == 2);
  assert(res[0].dir == RIGHT + DOWN);

  assert(strcmp(res[3].word, "ORCO") == 0);
  assert(res[3].row == 3);
  assert(res[3].col == 3);
  assert(res[3].dir == UP);

  assert(strcmp(res[4].word, "ORCO") == 0);
  assert(res[4].row == 4);
  assert(res[4].col == 3);
  assert(res[4].dir == RIGHT + UP);

  assert(strcmp(res[6].word, "REA") == 0);
  assert(res[6].row == 3);
  assert(res[6].col == 2);
  assert(res[6].dir == LEFT + UP);

  puts("All OK!");

  free(res);
  return 0;
}

position *solve(const char **words, const char mat[ROWS][COLS]) {
  vector found = vec(position);

  for (int w = 0; words[w][0] != '\0'; w++)
    find_word(words[w], mat, &found);

  position term = {NULL, 0, 0, 0};
  vec_push(&found, &term);

  return found.data;
}

void find_word(const char *word, const char mat[ROWS][COLS], vector *found) {
  position pos = {word, 0, 0, 0};

  for (int i = 0; i < ROWS; i++) {
    pos.row = i;
    for (int j = 0; j < COLS; j++) {
      pos.col = j;
      find_word_at(word, mat, found, &pos);
    }
  }
}

void find_word_at(
  const char *word,
  const char mat[ROWS][COLS],
  vector *found,
  position *pos
) {
  // Early exit if the first letter doesn't match
  if (mat[pos->row][pos->col] != word[0]) return;

  for (int d = 0; d < N_DIRS; d++) {
    pos->dir = directions[d];
    if (find_word_at_dir(word, mat, pos)) {
      vec_push(found, pos);
    }
  }
}

int find_word_at_dir(
  const char *word,
  const char mat[ROWS][COLS],
  position *pos
) {
  size_t di = pos->dir & DOWN ? 1 : (pos->dir & UP ? -1 : 0);
  size_t dj = pos->dir & RIGHT ? 1 : (pos->dir & LEFT ? -1 : 0);
  size_t i = pos->row + di, j = pos->col + dj;

  for (int k = 1; word[k] != '\0'; k++) {
    if (!inbounds(i, j) || mat[i][j] != word[k])
      return 0;

    i += di;
    j += dj;
  }

  return 1;
}
