#include <stdio.h>

#include "utils.h"

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// quicksort
void sort(int v[], int size) {
  if (size <= 1)
    return;

  if (size == 2) {
    if (v[0] > v[1])
      swap(v, v + 1);

    return;
  }

  int pivot = v[0];
  int small = 0, big = 0;
  int buf[size];

  for (int i = 1; i < size; i++) {
    if (v[i] < pivot) {
      buf[small++] = v[i];
    } else {
      buf[size - 1 - (big++)] = v[i];
    }
  }

  buf[small] = pivot;

  sort(buf, small);
  sort(buf + small + 1, big);

  for (int i = 0; i < size; i++) {
    v[i] = buf[i];
  }
}
