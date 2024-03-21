#include <assert.h>
#include <stdio.h>

#include "utils.h"

#define MAX_SIZE 6

void transpose(unsigned int size, int m[size][size]);

int main(void) {
  int m[MAX_SIZE][MAX_SIZE] = {
      {1, 2, 3, 4, 5, 6},       //
      {11, 12, 13, 14, 15, 16}, //
      {21, 22, 23, 24, 25, 26}, //
      {31, 32, 33, 34, 35, 36}, //
      {41, 42, 43, 44, 45, 46}, //
      {51, 52, 53, 54, 55, 56}
  };

  int t[MAX_SIZE][MAX_SIZE] = {
      {1, 11, 21, 31, 41, 51}, //
      {2, 12, 22, 32, 42, 52}, //
      {3, 13, 23, 33, 43, 53}, //
      {4, 14, 24, 34, 44, 54}, //
      {5, 15, 25, 35, 45, 55}, //
      {6, 16, 26, 36, 46, 56}
  };
  transpose(1, m);
  assert(m[0][0] == 1);
  assert(m[0][1] == 2);
  assert(m[1][0] == 11);
  assert(m[1][1] == 12);

  transpose(MAX_SIZE, m);
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++)
      assert(m[i][j] == t[i][j]);
  }

  puts("OK!");
}

void transpose(unsigned int size, int m[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      swap(&m[i][j], &m[j][i]);
    }
  }
}
