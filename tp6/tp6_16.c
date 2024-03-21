#include <assert.h>
#include <stdio.h>

#define ROWS 3
#define COLS 4

int asc_or_desc(const int m[][COLS]);

int main(void) {
  int m1[ROWS][COLS] = {{-6, -5, 2, 6}, {7, 9, 9, 14}, {21, 32, 45, 46}};
  assert(asc_or_desc(m1) == 1);
  puts("m1 OK");

  int m2[ROWS][COLS] = {{19, 13, 12, 8}, {7, 7, 5, -1}, {-6, -10, -14, -16}};
  assert(asc_or_desc(m2) == -1);
  puts("m2 OK");

  int m3[ROWS][COLS] = {{-6, -5, -6, 6}, {7, 9, 10, 14}, {21, 32, 45, 46}};
  assert(asc_or_desc(m3) == 0);
  puts("m3 OK");

  int m4[ROWS][COLS] = {{19, 13, 18, 8}, {7, 5, 2, -1}, {-6, -10, -14}};
  assert(asc_or_desc(m4) == 0);
  puts("m4 OK");

  int m5[ROWS][COLS] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
  int res_m5 = asc_or_desc(m5);
  assert(res_m5 == 1 || res_m5 == -1);
  puts("m5 OK");

  int m6[ROWS][COLS] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 10}};
  int res_m6 = asc_or_desc(m6);
  assert(res_m6 == 0);
  puts("m6 OK");

  int m7[ROWS][COLS] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
  int res_m7 = asc_or_desc(m7);
  assert(res_m7 == 0);
  puts("m7 OK");

  int m8[ROWS][COLS] = {{19, 19, 12, 8}, {7, 7, 5, -1}, {-6, -10, -14, -16}};
  assert(asc_or_desc(m8) == -1);
  puts("m8 OK");

  int m9[ROWS][COLS] = {{-6, -6, -6, 6}, {7, 9, 9, 14}, {21, 32, 45, 46}};
  assert(asc_or_desc(m9) == 1);
  puts("m9 OK");

  puts("All OK!");
  return 0;
}

int asc_or_desc(const int m[][COLS]) {
  int asc = 1, desc = 1;
  int last = m[0][0];
  for (int i = 0; i < ROWS; i++) {
    for (int j = !i; j < COLS; j++) { // Start at j=1 for first row, else j=0
      int val = m[i][j];
      if (val > last)
        desc = 0;
      if (val < last)
        asc = 0;

      if (!asc && !desc)
        return 0; // Early return

      last = val;
    }
  }

  return asc ? 1 : (desc ? -1 : 0);
}
