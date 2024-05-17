#include <stdio.h>

typedef int (*func)(int, int);

int reduce(int *vec, unsigned n, func f, int initial);

int sum(int n, int m) {
  return n + m;
}

int product(int n, int m) {
  return n * m;
}

int main(void) {
  int v[] = {2, 3, 4, 5};
  printf("sum = %d\n", reduce(v, 4, sum, 0));
  printf("product = %d\n", reduce(v, 4, product, 1));

  return 0;
}

int reduce(int *vec, unsigned n, func f, int initial) {
  if (n == 0) return initial;
  return f(*vec, reduce(vec + 1, n - 1, f, initial));
}
