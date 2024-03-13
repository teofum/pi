#include <stdio.h>

#include "../lib/my_getnum.h"

#define LSB 0x00000001
#define MSB 0x80000000

int main(void) {
  int input = -1;
  do {
    input = get_int("Enter a positive integer: ");
  } while (input < 0);

  int number_of_ones = 0;
  int mask = LSB;
  while (mask != MSB) {
    if (input & mask)
      number_of_ones += 1;

    mask <<= 1;
  }

  printf("%d\n", number_of_ones);

  return 0;
}
