#include <stdio.h>

#include "my_getnum.h"

#define abs(x) ((x) < 0 ? -(x) : (x))

int main(void) {
  int a = get_int("Enter an integer number: ");
  a = abs(a);

  int digit_sum = 0;
  while (a > 0) {
    int last_digit = a % 10;
    digit_sum += last_digit;
    a /= 10;
  }

  printf("The sum of digits is %d\n", digit_sum);

  return 0;
}
