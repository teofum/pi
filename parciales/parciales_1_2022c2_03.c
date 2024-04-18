#include <assert.h>
#include <stdio.h>

long factor(int v[]);

int main(void) {
  int factors[] = {2, 2, 2, 3, 3, 4, 5, 5, 6, 6, 6, 6, 7, -1};
  long res = factor(factors);
  assert(res == 65318400);
  assert(factors[0] == 2);
  assert(factors[1] == 3);
  assert(factors[2] == 4);
  assert(factors[3] == 5);
  assert(factors[4] == 6);
  assert(factors[5] == 7);
  assert(factors[6] == -1);
  int factores2[] = {2, -1};
  res = factor(factores2);
  assert(res == 2);
  assert(factores2[0] == 2);
  assert(factores2[1] == -1);
  int factores3[] = {11, 11, 13, -1};
  res = factor(factores3);
  assert(res == 1573); // 11 * 11 * 13
  assert(factores3[0] == 11);
  assert(factores3[1] == 13);
  assert(factores3[2] == -1);
  int factores4[] = {-1};
  res = factor(factores4);
  assert(res == 0);
  assert(factores4[0] == -1);
  int factores5[] = {1, -1};
  res = factor(factores5);
  assert(res == 1);
  assert(factores5[0] == 1);
  assert(factores5[1] == -1);
  puts("OK!");

  return 0;
}

long factor(int v[]) {
  int i = 1, j = 1;
  long n = v[0];

  // handle special empty vector case
  if (n == -1)
    return 0;

  while (v[i] != -1) {
    n *= v[i];

    // remove duplicate factors
    if (v[i] > v[i - 1]) {
      v[j++] = v[i];
    }

    i++;
  }

  v[j] = -1;
  return n;
}
