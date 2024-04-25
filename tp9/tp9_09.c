#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "utils.h"

#define EPSILON 0.01

double nr_sqrt(double last, uint iter, double x);

int main(void) {
  assert(fabs(nr_sqrt(4, 3, 8) - 2.833) <= EPSILON);
  assert(nr_sqrt(0, 0, 0) <= EPSILON);
  assert(nr_sqrt(0, 0, 4) <= EPSILON);

  printf("OK!\n");
}

double nr_sqrt(double last, uint iter, double x) {
  if (iter == 0 || last == 0) return 0;

  double res = (last + (x / last)) / 2;
  if (iter <= 1) return res;
  return nr_sqrt(res, iter - 1, x);
}
