#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int a = get_int("Enter an integer: ");
  int b = get_int("Enter another integer: ");

  printf("\nThe average is %g\n", (a + b) / 2.0);
  printf("The sum is %d\n", a + b);
  if (a == b) {
    printf("The numbers are equal\n");
  } else {
    printf("The larger number is %d\n", a > b ? a : b);
    printf("The smaller number is %d\n", a < b ? a : b);
  }

  return 0;
}