#include <stdio.h>

typedef int (*func)(int);

void map(int *v, unsigned n, func f);

int square(int n) {
  return n * n;
}

int main(void) {
  int v[] = {1, 2, 3, 4, 5};
  map(v, 5, square);

  for (int i = 0; i < 5; i++)
    printf("%d ", v[i]);
  putchar('\n');

  return 0;
}

void map(int *v, unsigned n, func f) {
  *v = f(*v);
  if (n > 1) map(v + 1, n - 1, f);
}
