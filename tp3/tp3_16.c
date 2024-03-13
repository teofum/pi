#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int input = -1;
  do {
    input = get_int("Enter a positive integer up to 255: ");
  } while (input < 0 || input > 255);

  int n = input, binary = 0, power = 1;
  while (n > 0) {
    int last_digit = n % 2;
    binary += last_digit * power;

    n /= 2;
    power *= 10;
  }

  printf("%d in binary is %08d\n", input, binary);

  return 0;
}
