#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 1e-12

double my_round(double x, int precision) {
  double i = pow(10, precision);
  return floor(x * i + 0.5) / i;
}

int equals(double x, double y) { return fabs(x - y) < EPSILON; }

int main(void) {
  double x = 1.0;

  for (int i = 0; i < 10; i++)
    assert(my_round(x, i) == x);

  x = 1.11111;
  assert(equals(my_round(x, 0), 1.0));
  assert(equals(my_round(x, 1), 1.1));
  assert(equals(my_round(x, 2), 1.11));
  assert(equals(my_round(x, 3), 1.111));
  assert(equals(my_round(x, 4), 1.1111));
  assert(equals(my_round(x, 5), 1.11111));
  assert(equals(my_round(x, 6), 1.11111));
  assert(equals(my_round(x, 7), 1.11111));

  x = 1.15555;
  assert(equals(my_round(x, 0), 1.0));
  assert(equals(my_round(x, 1), 1.2));
  assert(equals(my_round(x, 2), 1.16));
  assert(equals(my_round(x, 3), 1.156));

  puts("OK!");
  return 0;
}
