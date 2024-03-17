#include <assert.h>
#include <stdio.h>

#define SWAP(T, x, y)                                                          \
  {                                                                            \
    T tmp_##T = x;                                                             \
    x = y;                                                                     \
    y = tmp_##T;                                                               \
  }

int main(void) {
  int a = 5, b = 3;

  SWAP(int, a, b);
  assert(a == 3 && b == 5);
  a = -1;
  SWAP(int, a, a);
  assert(a == -1);

  double x = 3.0, y = 8.0;
  SWAP(double, x, y);
  assert(x == 8.0 && y == 3.0);
  SWAP(double, x, y);
  assert(x == 3.0 && y == 8.0);

  puts("OK !");
  return 0;
}
