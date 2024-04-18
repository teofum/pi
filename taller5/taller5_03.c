#define COLS 6

enum direction { E = 1, NE = 3, N = 2, NW = 6, W = 4, SW = 12, S = 8, SE = 9 };
enum direction directions[8] = {E, NE, N, NW, W, SW, S, SE};

typedef unsigned int uint;

int get_direction(
    const char board[][COLS],
    uint rows,
    uint cols,
    uint px,
    uint py
);

int move(
    const char board[][COLS],
    uint rows,
    uint cols,
    uint px,
    uint py,
    enum direction direction
);

int in_bounds(uint rows, uint cols, int tx, int ty);

int get_direction(
    const char board[][COLS],
    uint rows,
    uint cols,
    uint px,
    uint py
) {
  int max = 0, max_dir = -1;

  for (int d = 0; d < 8; d++) {
    int dist = move(board, rows, cols, px, py, directions[d]);
    if (dist > max) {
      max = dist;
      max_dir = d * 45;
    }
  }

  return max_dir;
}

int move(
    const char board[][COLS],
    uint rows,
    uint cols,
    uint px,
    uint py,
    enum direction direction
) {
  int dx = direction & E ? 1 : (direction & W ? -1 : 0);
  int dy = direction & S ? 1 : (direction & N ? -1 : 0);

  int tx = px + dx, ty = py + dy, mv = 0;
  while (in_bounds(rows, cols, tx, ty) && board[ty][tx] == '0') {
    mv++;
    tx += dx;
    ty += dy;
  }

  return mv;
}

int in_bounds(uint rows, uint cols, int tx, int ty) {
  return tx >= 0 && tx < cols && ty >= 0 && ty < rows;
}
