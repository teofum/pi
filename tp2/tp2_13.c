#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int a = get_int("Enter an integer: ");
  int b = get_int("Enter another integer: ");

  if (b % a) {
    printf("\n%d is not a multiple of %d\n", b, a);
  } else {
    printf("\n%d is a multiple of %d\n", b, a);
  }

  return 0;
}