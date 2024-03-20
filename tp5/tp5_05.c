#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 0.00001

double power(double base, double exp);

int main(void) {
  assert(power(0, 0) == -1);

  for (int i = -10, j = 1; i < 10; i++, (i % 2 == 0 ? j++ : 0)) {
    assert(fabs(power(i, j) - pow(i, j)) <= EPSILON);
  }
  assert(fabs(power(-2, -4) - pow(-2, -4)) <= EPSILON);

  puts("OK!");
  return 0;
}

double power(double base, double exp) {
  if (base == 0)
    return exp == 0 ? -1 : 0;
  if (exp == 0)
    return 1;
  double res = 1;
  if (exp > 0) {
    for (int i = 0; i < exp; i++)
      res *= base;
  } else {
    for (int i = 0; i < -exp; i++)
      res /= base;
  }

  return res;
}
