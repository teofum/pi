#include <math.h>
#include <stdio.h>

#define EPSILON 1e-12

double power(double b, int e) {
  double res = 1;
  for (int i = 0; i < e; i++) {
    res *= b;
  }

  return res;
}

double my_exp(double x) {
  double last_value = -999;
  double value = 0;
  int i = 0;
  long factorial = 1;

  while ((value - last_value) > EPSILON) {
    last_value = value;
    value += power(x, i) / factorial;
    i++;
    factorial *= i;
  }

  return value;
}

int main(void) {
  printf("%-20s %-20s\n", "my_exp", "exp");
  for (double x = 0; x < 10; x += 0.5) {
    printf("%20.12f %20.12f\n", my_exp(x), exp(x));
  }

  return 0;
}
