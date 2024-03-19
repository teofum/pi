#include <stdio.h>

#include "my_getnum.h"

#define abs(x) ((x) < 0 ? -(x) : (x))
#define EPSILON 1e-12

/* Note: the following program will only work correctly for numbers with an
 * exact floating-point representation. Anything else will get bogus digits
 * added at the end and will return nonsense answers.
 */
int main(void) {
  float a = get_float("Enter a number: ");
  a = abs(a);
  a = a - (int)a; // Remove integer part

  int digit_sum = 0;
  while (a > EPSILON) {
    a *= 10.0; // Multiply by 10 to get first decimal digit to integer place
    int last_digit = (int)a; // Isolate this digit by truncating decimal part
    digit_sum += last_digit;
    a = a - (int)a; // Then keep the remaining digits
  }

  printf("The sum of decimal digits is %d\n", digit_sum);

  return 0;
}
