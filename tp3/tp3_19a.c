#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int input = get_int("Enter an integer: ");
  int n = input < 0 ? -input : input;

  int fives = 0;
  while (n > 0) {
    if (n % 10 == 5)
      fives += 1;

    n /= 10;
  }

  printf("%d has %d digits equal to 5\n", input, fives);

  return 0;
}
