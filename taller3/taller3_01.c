#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

int isprime(int n);

int main(void) {
  int n = get_int("Enter a positive integer: ");
  printf("%d is %sprime\n", n, isprime(n) ? "" : "not ");

  return 0;
}

int isprime(int n) {
  if (n < 2)
    return 0;

  for (int i = 2; i * i <= n; i++)
    if (n % i == 0)
      return 0;

  return 1;
}
