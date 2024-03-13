#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int input = -1;
  do {
    input = get_int("Enter a positive integer: ");
  } while (input < 0);

  long factorial = 1;
  for (int i = 1; i <= input; i++)
    factorial *= i;

  printf("%d! = %ld\n", input, factorial);

  return 0;
}
