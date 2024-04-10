#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 0.000001

// Expects a 0-terminated array
double max_diff(const double vec[]);

int main(void) {
  double v[] = {1.0, 0.0};
  assert(fabs(max_diff(v)) == 0.0);

  double v2[] = {1.0, 1.0, 1.0, 0.0};
  assert(fabs(max_diff(v2)) == 0.0);

  double v3[] = {1.5, 3.0, -1.0, 0.0};
  assert(fabs(max_diff(v3) - 4.0) < EPSILON);

  double v4[] = {1.5, 3.0, 4.5, 3.0, 0.0};
  assert(fabs(max_diff(v4) - 1.5) < EPSILON);

  double v5[] = {2.5, 1.0, 1.5, 2.0, 0.0};
  assert(fabs(max_diff(v5) - 1.5) < EPSILON);

  double v6[] = {1.5, -1.0, 3.0, 0.0};
  assert(fabs(max_diff(v6) - 4.0) < EPSILON);

  puts("OK!");
  return 0;
}

double max_diff(const double vec[]) {
  double max_d = 0.0;

  if (vec[0] == 0.0)
    return 0.0;

  for (int i = 1; vec[i] != 0.0; i++) {
    double d = fabs(vec[i] - vec[i - 1]);
    if (d > max_d)
      max_d = d;
  }

  return max_d;
}
