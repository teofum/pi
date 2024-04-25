#include <stdio.h>
#include <assert.h>

int bin_search(const int *v, size_t size, int n);

int main(void) {
  int v[] = {-10, -5, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45};

  assert(bin_search(v, 0, -10) == 0);
  assert(bin_search(v, 1, -10) == 1);
  assert(bin_search(v, 2, -10) == 1);
  assert(bin_search(v, 2, -5) == 1);
  assert(bin_search(v, 2, 0) == 0);

  assert(bin_search(v + 1, 2, -10) == 0);
  assert(bin_search(v + 1, 2, -5) == 1);
  assert(bin_search(v + 1, 2, 0) == 1);

  for (int i = 0; i < 12; i++)
    assert(bin_search(v, 12, v[i]) == 1);

  for (int i = 0; i < 11; i++)
    assert(bin_search(v, 11, v[i]) == 1);

  printf("OK!\n");
  return 0;
}

int bin_search(const int *v, size_t size, int n) {
  if (size == 0) return 0;
  if (size == 1) return n == *v;

  int m = v[size / 2];
  if (n < m) return bin_search(v, size / 2, n);
  if (n > m) return bin_search(v + size / 2 + 1, size - (size / 2 + 1), n);
  return 1; // n == m
}
