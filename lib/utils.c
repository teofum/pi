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

  int l = 0, r = size;
  int m = l + ((r - l) >> 1);

  int pivot = v[m];
  v[m] = v[l];

  while (l < r) {
    while (v[r] >= pivot && l < r) {
      r--;
    }
    if (l < r) {
      v[l++] = v[r];
    }
    while (v[l] <= pivot && l < r) {
      l++;
    }
    if (l < r) {
      v[r--] = v[l];
    }
  }
  v[l] = pivot;
  m = l + 1;

  sort(v, l);
  sort(v + m, size - m);
}
