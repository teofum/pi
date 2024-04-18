#include <stdio.h>

#define N 6
#define NUM_DIRS 8

// encode directions as flags so we can do a neat trick later
enum direction { RIGHT = 1, UP = 2, LEFT = 4, DOWN = 8 };
enum direction directions[NUM_DIRS] = {RIGHT, RIGHT + UP,  UP,   LEFT + UP,
                                       LEFT,  LEFT + DOWN, DOWN, RIGHT + DOWN};

int in_bounds(int i, int j);
int find_word(const int m[N][N], int i0, int j0, const char *str);
int find_word_dir(
    const int m[N][N],
    int i0,
    int j0,
    const char *str,
    enum direction dir
);

int main(void) {
  int mat[N][N] = {
      {'L', 'O', 'B', 'R', 'A', 'Z'}, //
      {'F', 'H', 'R', 'G', 'O', 'R'}, //
      {'C', 'O', 'S', 'A', 'D', 'A'}, //
      {'R', 'L', 'A', 'H', 'N', 'N'}, //
      {'W', 'A', 'O', 'Y', 'U', 'T'}, //
      {'Q', 'S', 'G', 'S', 'M', 'A'}  //
  };

  printf("Should be all 1:\n");
  printf("%d ", find_word(mat, 5, 1, "SAL"));
  printf("%d ", find_word(mat, 2, 0, "COSA"));
  printf("%d ", find_word(mat, 2, 0, "CHB"));
  printf("%d ", find_word(mat, 2, 0, "CLOS"));
  printf("%d ", find_word(mat, 2, 0, ""));
  printf("%d\n", find_word(mat, 2, 0, "C"));

  printf("Should be all 0:\n");
  printf("%d ", find_word(mat, 5, 1, "sal"));
  printf("%d ", find_word(mat, 5, 1, "SALA"));
  printf("%d ", find_word(mat, 2, 0, "COSADAS"));
  printf("%d\n", find_word(mat, 6, 3, "OUTOFBOUNDS"));

  return 0;
}

int in_bounds(int i, int j) { return i >= 0 && i < N && j >= 0 && j < N; }

int find_word(const int m[N][N], int i0, int j0, const char *str) {
  // check starting position is in bounds to begin with
  if (!in_bounds(i0, j0))
    return 0;

  // search for the word in each direction, return as soon as we find it
  for (int d = 0; d < NUM_DIRS; d++) {
    if (find_word_dir(m, i0, j0, str, directions[d]))
      return 1;
  }

  return 0;
}

int find_word_dir(
    const int m[N][N],
    int i0,
    int j0,
    const char *str,
    enum direction dir
) {
  // using flags for directions makes calculating deltas super easy!
  int di = (dir & UP) ? -1 : (dir & DOWN ? 1 : 0);
  int dj = (dir & LEFT) ? -1 : (dir & RIGHT ? 1 : 0);

  int i = i0, j = j0, k = 0;
  while (str[k] != '\0') {
    // we went out of bounds or found a letter that doesn't match, in either
    // case the word is not found in this direction
    if (!in_bounds(i, j) || m[i][j] != str[k])
      return 0;

    i += di;
    j += dj;
    k++;
  }

  return 1;
}
