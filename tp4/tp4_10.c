#include <stdio.h>

#include "../lib/my_getnum.h"

int gcd(int a, int b);

int main(void) {
  int a = -1;
  do {
    a = get_int("Enter a positive integer: ");
  } while (a <= 0);

  int b = -1;
  do {
    b = get_int("Enter another positive integer: ");
  } while (b <= 0);

  printf("(%d : %d) = %d\n", a, b, gcd(a, b));

  return 0;
}

int gcd(int a, int b) {
  if (a < b) {
    // Swap a and b
    a += b;
    b = a - b;
    a = a - b;
  }

  int aux = a % b;

  while (aux > 0) {
    a = b;
    b = aux;
    aux = a % b;
  }

  return b;
}
