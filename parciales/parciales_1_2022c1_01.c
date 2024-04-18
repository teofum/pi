#include <math.h>
#include <stdio.h>

#define COLS 5

void xor_sets(int m1[][COLS], int m2[][COLS], int m3[][COLS], int rows);
void xor_set(int v1[COLS], int v2[COLS], int out[COLS]);

void print_mat(int m[][COLS], int rows);

int main(void) {
  int m1[][COLS] = {
      {1, 2, 3, 4, -1}, //
      {3, 4, 5, -1},    //
      {10, 15, 20, -1}, //
      {-1},             //
      {-1},             //
      {5, 6, 7, -1}     //
  };
  int m2[][COLS] = {
      {3, 4, 5, 6, -1}, //
      {3, 4, 5, -1},    //
      {10, 20, -1},     //
      {1, 2, 3, 4, -1}, //
      {-1},             //
      {1, 2, 7, -1}     //
  };
  int m3[6][COLS] = {{0}};

  printf("m1:\n");
  print_mat(m1, 6);
  printf("m2:\n");
  print_mat(m2, 6);

  xor_sets(m1, m2, m3, 6);
  printf("m3:\n");
  print_mat(m3, 6);

  return 0;
}

void xor_sets(int m1[][COLS], int m2[][COLS], int m3[][COLS], int rows) {
  for (int i = 0; i < rows; i++)
    xor_set(m1[i], m2[i], m3[i]);
}

// doesn't check for overflow!
void xor_set(int v1[COLS], int v2[COLS], int out[COLS]) {
  int i = 0, j = 0, k = 0;

  while (v1[i] != -1 || v2[j] != -1) {
    if (v1[i] == -1 || v2[j] < v1[i]) {
      out[k++] = v2[j++]; // v1 end or v2 elem is smaller so we know not in v1
    } else if (v2[j] == -1 || v1[i] < v2[j]) {
      out[k++] = v1[i++]; // v2 end or v1 elem is smaller so we know not in v2
    } else {
      // v1[i] == v2[j], skip
      i++;
      j++;
    }
  }

  out[k] = -1; // add -1 terminator
}

void print_mat(int m[][COLS], int rows) {
  for (int i = 0; i < rows; i++) {
    printf("| ");
    for (int j = 0; m[i][j] != -1; j++)
      printf("%2d ", m[i][j]);
    printf("\n");
  }
}
