#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

#define abs(x) ((x) < 0 ? -(x) : (x))
#define EPSILON 1e-12

int main(void) {
  printf("Enter coefficients for 0 = ax² + bx + c\n");
  double a = get_double("a: ");
  while (abs(a) < EPSILON) {
    printf("a must be non-zero for the equation to be a valid quadratic\n");
    a = get_double("a: ");
  }

  double b = get_double("b: ");
  double c = get_double("c: ");

  printf("The equation 0 = %gx² + %gx + %g ", a, b, c);

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    // If the discriminant is < 0 we know there are no real roots
    printf("has no real solutions\n");
    return 0;
  }

  double sqrt_discriminant = sqrt(discriminant);
  double r1 = (-b - sqrt_discriminant) / 2.0 * a;
  double r2 = (-b + sqrt_discriminant) / 2.0 * a;

  if (abs(r1 - r2) < EPSILON) {
    // Handle special case where r1 = -0 (floating point shenanigans)
    if (r1 == -0.0)
      r1 = 0.0;

    printf("has a real solution r = %g\n", r1);
  } else {
    printf("has two real solutions r1 = %g, r2 = %g\n", r1, r2);
  }

  return 0;
}
