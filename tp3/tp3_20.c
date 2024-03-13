#include <stdio.h>

#define PRECISION 1e-12

int main(void) {
  double e = 0, last_e = -999;
  long int factorial = 1;
  int n = 0;

  printf("%-10c%-10c\n", 'N', 'e');
  // Keep going until each iteration increases precision by less than 10^-12
  while (e - last_e > PRECISION) {
    last_e = e;
    e += 1.0 / factorial;
    printf("%-10d%-20.12f\n", n + 1, e);
    n += 1;
    factorial *= n;
  }

  return 0;
}
