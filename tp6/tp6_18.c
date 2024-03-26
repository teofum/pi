#include <assert.h>
#include <stdio.h>

#define COLS 4

typedef unsigned int uint;

int contains(const int v1[COLS], const int v2[COLS]);
int friend_of(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2);
int friendly_mat(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2);

int main(void) {
  int m1[][COLS] = {{0, 1, 2, 3}, {4, 4, 5, 6}, {7, 8, 8, 9}};
  int m2[][COLS] = {{0, 1, 2, 3}, {-3, 7, 8, 9}, {-1, 3, 4, 7}, {4, 5, 6, 8}};
  int m3[][COLS] = {{2, 3, 3, 7}};
  assert(friendly_mat(m1, 3, m2, 4) == 1);
  printf("Test 1 OK!\n");
  assert(friendly_mat(m1, 1, m2, 4) == 1);
  printf("Test 2 OK!\n");
  assert(friendly_mat(m1, 2, m2, 4) == 1);
  printf("Test 3 OK!\n");
  assert(friendly_mat(m1, 2, m2, 2) == 0);
  printf("Test 4 OK!\n");
  assert(friendly_mat(m2, 4, m1, 3) == 2);
  printf("Test 5 OK!\n");
  assert(friendly_mat(m1, 3, m3, 1) == 0);
  printf("Test 6 OK!\n");
  assert(friendly_mat(m3, 1, m1, 3) == 0);
  printf("Test 7 OK!\n");
  int res = friendly_mat(m1, 3, m1, 3);
  assert(res == 1 || res == 2);
  printf("Test 8 OK!\n");

  printf("All tests OK!\n");

  return 0;
}

// Returns 1 if `v2` contains `v1`, 0 otherwise
int contains(const int v1[COLS], const int v2[COLS]) {
  for (int i = 0; i < COLS; i++) {
    int item = v1[i], in_v2 = 0;
    for (int j = 0; j < COLS && !in_v2; j++) {
      if (v2[j] == item)
        in_v2 = 1;
    }
    if (!in_v2)
      return 0;
  }
  return 1;
}

// Returns 1 if each row of m1 is contained in some row of m2, 0 otherwise
int friend_of(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2) {
  for (int i = 0; i < r1; i++) {
    int row_in_v2 = 0;
    for (int j = 0; j < r2 && !row_in_v2; j++) {
      int cont = contains(m1[i], m2[j]);
      row_in_v2 |= cont;
    }

    if (!row_in_v2)
      return 0;
  }
  return 1;
}

// 1 if m1 is friend of m2, 2 if m2 is friend of m1, 0 otherwise
int friendly_mat(const int m1[][COLS], uint r1, const int m2[][COLS], uint r2) {
  if (friend_of(m1, r1, m2, r2))
    return 1;

  return friend_of(m2, r2, m1, r1) ? 2 : 0;
}
