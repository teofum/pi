#include <assert.h>
#include <stdio.h>

#define COLS 4

typedef unsigned int uint;

int contains(const int v1[COLS], const int v2[COLS]);
int friendly_mat(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2);

int main(void) {
  int m1[][COLS] = {{0, 1, 3, 2}, {4, 6, 5, 6}, {9, 8, 7, 9}};
  int m2[][COLS] = {{0, 1, 2, 3}, {-3, 9, 8, 7}, {-1, 3, 4, 7}, {4, 5, 6, 8}};
  int m3[][COLS] = {{2, 3, 3, 7}};
  assert(friendly_mat(m1, 3, m2, 4) == 1);
  printf("Test 1 OK!\n");
  assert(friendly_mat(m2, 4, m1, 3) == 2);
  printf("Test 2 OK!\n");
  assert(friendly_mat(m1, 3, m3, 1) == 0);
  printf("Test 3 OK!\n");
  assert(friendly_mat(m3, 1, m1, 3) == 0);
  printf("Test 4 OK!\n");
  int res = friendly_mat(m1, 3, m1, 3);
  assert(res == 1 || res == 2);
  printf("Test 5 OK!\n");

  printf("All tests OK!\n");

  return 0;
}

// Returns 1 if `v2` contains `v1`, 0 otherwise
int contains(const int v1[COLS], const int v2[COLS]) {
  for (int i = 0; i < COLS; i++) {
    int item = v1[i], in_v2 = 0;
    for (int j = 0; j < COLS; j++) {
      if (v2[j] == item) {
        in_v2 = 1;
        break;
      }
    }
    if (!in_v2)
      return 0;
  }
  return 1;
}

// Same solution from 6.18, since it never assumed ordered rows to begin with
int friendly_mat(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2) {
  int m1_friendly_m2 = 1;
  for (int i = 0; i < r1; i++) {
    int row_friendly = 0;
    for (int j = 0; j < r2; j++) {
      int cont = contains(&m1[i][0], &m2[j][0]);
      row_friendly |= cont;
    }

    m1_friendly_m2 &= row_friendly;
  }
  if (m1_friendly_m2)
    return 1;

  // If m1 is not friendly to m2 test the other way round
  for (int i = 0; i < r2; i++) {
    int row_friendly = 0;
    for (int j = 0; j < r1; j++) {
      int cont = contains(&m2[i][0], &m1[j][0]);
      row_friendly |= cont;
    }

    if (!row_friendly)
      return 0;
  }
  return 2;
}
