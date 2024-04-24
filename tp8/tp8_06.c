#include <stdio.h>
#include <math.h>

#include "vector.h"

#define PRECISION 100000.0
#define EPSILON 1e-12

typedef struct {
  double min, max;
} interval;

vector eval(double (*f)(double), interval d);

double f(double x) {
  return (x * x - x) / 100;
}

int main(void) {
  interval d = {-100, 100};
  vector roots = eval(sin, d);

  interval root;
  for (int i = 0; i < roots.size; i++) {
    vec_get(&roots, i, &root);
    printf("[ %8.3f ; %8.3f ]\n", root.min, root.max);
  }

  vec_delete(&roots);
  return 0;
}

vector eval(double (*f)(double), interval d) {
  double delta = (d.max - d.min) / PRECISION;

  vector roots = vec(interval);
  interval temp_root = {0, 0};
  int in_root = 0;

  double last_fx = 0;
  for (double x = d.min; x <= d.max; x += delta) {
    double fx = f(x);
    if (fabs(fx) < EPSILON) {
      in_root = 1;
    } else {
      if (in_root || fx * last_fx < 0) {
        temp_root.max = x;
        vec_push(&roots, &temp_root);
      }

      in_root = 0;
      temp_root.min = x;
    }

    last_fx = fx;
  }

  return roots;
}
