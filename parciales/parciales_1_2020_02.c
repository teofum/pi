#include <limits.h>
#include <stdio.h>

int dedupe_sort(unsigned char v[], int size);

int main(void) {
  // todo
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
