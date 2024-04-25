#include <stdio.h>
#include <assert.h>

int sum_digits(int n);

int main(void) {
  assert(sum_digits(0) == 0);
  assert(sum_digits(1) == 1);
  assert(sum_digits(12) == 3);
  assert(sum_digits(100000) == 1);
  assert(sum_digits(123456) == 21);
  assert(sum_digits(-123456) == 21);
  assert(sum_digits(999999) == 54);

  printf("OK!\n");
  return 0;
}

int sum_digits(int n) {
  if (n < 0) return sum_digits(-n);
  if (n < 10) return n;
  return n % 10 + sum_digits(n / 10);
}
