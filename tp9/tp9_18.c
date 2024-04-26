#include <stdio.h>
#include <assert.h>

int sum_match(const int *v);

int main(void) {
  int v1[] = {1, 2, 3, 6, 4, 3, 2, 9, 1, 2, 3, -1}; // 1+2+3=6, 4+3+2=9, 1+2=3
  assert(sum_match(v1) == 0);
  int v2[] = {1, 1, 2, 4, 5, 5, 14, -1};            // 14=5+5+4, 2=1+1
  assert(sum_match(v2) == 0);
  int v3[] = {3, 3, -1};                            // 3=3
  assert(sum_match(v3) == 0);
  int v4[] = {1, 1, 2, 2, 90, 90, -1};              // 90=90, 2=2, 1=1
  assert(sum_match(v4) == 0);
  int v5[] = {1, 0, 1, 2, 2, 2, 6, -1};             // 6=2+2+2, 1=0+1
  assert(sum_match(v5) == 0);
  int v6[] = {-1};
  assert(sum_match(v6) == 0);
  int v7[] = {0, -1};
  assert(sum_match(v7) == 0);

  int w1[] = {1, 1, 2, 3, 6, 4, 3, 2, 9, 1, 2, 3, -1};
  assert(sum_match(w1) != 0);
  int w2[] = {1, 1, 2, 4, 5, 5, 14, 10, -1};
  assert(sum_match(w2) != 0);
  int w3[] = {4, 3, -1};
  assert(sum_match(w3) != 0);
  int w4[] = {1, -1};
  assert(sum_match(w4) != 0);
  int w5[] = {1, 0, 1, 2, 1, 2, 2, 2, -1};
  assert(sum_match(w5) != 0);

  printf("OK!\n");
  return 0;
}

int sum_match(const int *v) {
  if (*v == -1) return 0;

  int next = sum_match(v + 1);
  if (next == 0) return next + *v;
  if (next > 0) return next - *v;
  return next;
}
