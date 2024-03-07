#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int n;
  do {
    n = get_int("Enter a positive integer\n");
  } while (n <= 0);

  printf("%d / 2 = %d\n", n, n >> 1);

  return 0;
}