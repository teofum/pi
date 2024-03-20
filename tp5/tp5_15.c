#include <assert.h>
#include <stdio.h>

#define ABS(a) (((a) > 0) ? (a) : -(a))
#define MINUTES(h, m) ((h) * 60 + (m))
#define ELAPSED(h1, m1, h2, m2) ABS(MINUTES(h1, m1) - MINUTES(h2, m2))

int main(void) {
  int h1, h2, m1, m2;
  h1 = 2;
  m1 = 10;
  h2 = 3;
  m2 = 15;

  assert(ELAPSED(h1, m1, h2, m2) == 65);
  assert(ELAPSED(h1, m1, h2, m2) + 1 == 66);

  assert(ELAPSED(2, 20, 3, 10) == 50);
  assert(ELAPSED(3, 10, 2, 20) == 50);

  assert(ELAPSED(2, 10, 3, 15) == 65);
  assert(ELAPSED(3, 15, 2, 10) == 65);
  assert(ELAPSED(h1, m1, h1 + 1, m1) == 60);
  assert(ELAPSED(h1, m1, h1 + 1, m1) / 2 == 30);
  assert(ELAPSED(h1, m1, h1 + 1, (m1 > 0) ? m1 : m2) == 60);

  puts("OK!");
}
