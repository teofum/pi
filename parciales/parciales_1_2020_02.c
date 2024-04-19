#include <assert.h>
#include <limits.h>
#include <stdio.h>

int dedupe_sort(unsigned char v[], int size);

int main(void) {
  unsigned char v[] = {1, 3, 1, 5, 2, 1, 5, 1, 0, 100, 95, 100, 3};

  int n = dedupe_sort(v, sizeof(v) / sizeof(v[0]));
  assert(n == 7);
  assert(v[0] == 0);
  assert(v[1] == 1);
  assert(v[2] == 2);
  assert(v[3] == 3);
  assert(v[4] == 5);
  assert(v[5] == 95);
  assert(v[6] == 100);

  printf("OK!\n");
  return 0;
}

int dedupe_sort(unsigned char v[], int size) {
  int values[UCHAR_MAX + 1];
  for (int i = 0; i < UCHAR_MAX + 1; i++) {
    values[i] = -1;
  }

  for (int i = 0; i < size; i++) {
    values[v[i]] = v[i];
  }

  int j = 0;
  for (int i = 0; i < UCHAR_MAX + 1; i++) {
    if (values[i] != -1) {
      v[j++] = values[i];
    }
  }

  return j;
}
