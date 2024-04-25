#include <stdio.h>
#include <assert.h>

int sum(const int *v, size_t size);

int main(void) {
  int v[] = {1, 2, 3, 4, 5, -5};

  assert(sum(v, 0) == 0);
  assert(sum(v, 1) == 1);
  assert(sum(v, 2) == 3);
  assert(sum(v, 3) == 6);
  assert(sum(v, 4) == 10);
  assert(sum(v, 5) == 15);
  assert(sum(v, 6) == 10);

  printf("OK!\n");
  return 0;
}

int sum(const int *v, size_t size) {
  if (size == 0) return 0;
  return *v + sum(v + 1, size - 1);
}
