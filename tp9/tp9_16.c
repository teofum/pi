#include <stdio.h>
#include <assert.h>

#define END (-1)

int ordering(const int *v);

int main(void) {
  int v[] = {-1};
  assert(ordering(v) == 0);

  int v2[] = {1, -1};
  assert(ordering(v2) == 0);

  int v3[] = {1, 2, -1};
  assert(ordering(v3) == 1);

  int v4[] = {1, 2, 3, 10, 100, 999, 2345, -1};
  assert(ordering(v4) == 1);

  int v5[] = {100, 29, 23, 19, 18, 5, 4, 0, -1};
  assert(ordering(v5) == -1);

  int v6[] = {1, 2, 3, 10, 100, 999, 998, -1};
  assert(ordering(v6) == 0);

  int v7[] = {1, 2, 3, 10, 1000, 999, 1998, -1};
  assert(ordering(v7) == 0);

  int v8[] = {1, 1, 1, 10, 1000, 1999, 2998, -1};
  assert(ordering(v8) == 0);

  int v9[] = {1, 1, -1};
  assert(ordering(v9) == 0);

  printf("OK!\n");
  return 0;
}

int ordering(const int *v) {
  int this = v[0], next = v[1];

  if (this == END || next == END) return 0;
  int cmp = (this > next) ? -1 : ((this < next) ? 1 : 0);

  if (v[2] == END) return cmp;
  return ordering(v + 1) == cmp ? cmp : 0;
}
