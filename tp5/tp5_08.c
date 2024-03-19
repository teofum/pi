#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

double my_round(double x, int precision);

int main(void) {
  double x = get_double("Enter a number: ");
  int p = get_int("Enter # of decimal digits or 0 for round to integer: ");

  printf("%g\n", my_round(x, p));

  return 0;
}

double my_round(double x, int precision) {
  double i = pow(10, precision);
  return floor(x * i + 0.5) / i;
}
