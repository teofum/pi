#include <stdio.h>

#include "../lib/my_getnum.h"

#define EPSILON 1e-12

int main(void) {
  float input = get_float("Enter a number: ");
  float n = input < 0 ? -input : input;

  int integer_fives = 0;
  float power = 1.0;
  while (power <= n) {
    // Isolate the ith digit of n, with i = log10(power)

    // Put the ith integer digit in the first decimal place
    float test_i = n / (power * 10.0);
    test_i -= (long)test_i; // Keep only the fractional part
    if (test_i >= 0.5 && test_i < 0.6) {
      // If the first decimal place is 5, then the ith digit was 5
      integer_fives += 1;
    }

    power *= 10;
  }

  int decimal_fives = 0, stop = 0;
  power = 1.0;
  while (!stop) {
    // Put the ith decimal digit in the first decimal place
    float test = n * (power);
    test -= (long)test; // Keep only the fractional part
    if (test >= 0.5 && test < 0.6) {
      // If the first decimal place is 5, then the ith digit was 5
      decimal_fives += 1;
    } else if (test < EPSILON) {
      stop = 1; // Stop when we run out of decimal digits
    }

    power *= 10;
  }

  printf("%f has %d digits =5 in its integer part\n", input, integer_fives);
  printf("and %d digits =5 in its decimal part\n", decimal_fives);

  return 0;
}
