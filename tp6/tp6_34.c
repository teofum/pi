#include <assert.h>
#include <stdio.h>

#define ROWS 4
#define COLS 4

#define min(a, b) ((a) < (b)) ? (a) : (b)
#define max(a, b) ((a) < (b)) ? (b) : (a)

int step_cell(char cells[ROWS][COLS], int x, int y);
int step(char cells[ROWS][COLS]);

int main(void) {
  char cells[ROWS][COLS] = {
      {0, 1, 0, 0}, {1, 1, 1, 1}, {0, 1, 1, 0}, {1, 0, 0, 1}
  };

  assert(step(cells) == 1);

  char expected[ROWS][COLS] = {
      {1, 1, 0, 0}, {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 1, 1, 0}
  };
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      assert(cells[i][j] == expected[i][j]);

  char cells2[ROWS][COLS] = {
      {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
  };
  assert(step(cells2) == 0);

  char expected2[ROWS][COLS] = {
      {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
  };

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      assert(cells2[i][j] == expected2[i][j]);

  puts("OK!");

  return 0;
}

int step_cell(char cells[ROWS][COLS], int x, int y) {
  int was_alive = cells[y][x];

  int live_neighbors = 0;
  int xmin = max(0, x - 1);
  int xmax = min(COLS - 1, x + 1);
  int ymin = max(0, y - 1);
  int ymax = min(ROWS - 1, y + 1);
  for (int yy = ymin; yy <= ymax; yy++) {
    for (int xx = xmin; xx <= xmax; xx++) {
      if ((yy != y || xx != x) && cells[yy][xx])
        live_neighbors++;
    }
  }

  return live_neighbors == 3 || (live_neighbors == 2 && was_alive);
}

int step(char cells[ROWS][COLS]) {
  char buffer[ROWS][COLS];

  putchar('\n');
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      putchar(cells[y][x] ? '*' : '.');
      buffer[y][x] = step_cell(cells, x, y);
    }
    putchar('\n');
  }

  putchar('\n');
  int change = 0;
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      if (cells[y][x] != buffer[y][x])
        change = 1;

      putchar(buffer[y][x] ? '*' : '.');
      cells[y][x] = buffer[y][x];
    }
    putchar('\n');
  }
  return change;
}
