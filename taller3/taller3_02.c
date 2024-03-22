#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

int isprime(int n);
void print_primes(int n);

int main(void) {
  int n = get_int("Enter a positive integer: ");
  print_primes(n);

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

void print_primes(int n) {
  int primes = 0, i = 2;
  while (primes < n) {
    if (isprime(i)) {
      printf("%d\n", i);
      primes++;
    }
    i++;
  }
}
