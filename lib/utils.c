#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "utils.h"

void swap_int(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap(void *a, void *b, size_t el_size) {
  void *tmp = malloc(el_size);
  memcpy(tmp, a, el_size);
  memcpy(a, b, el_size);
  memcpy(b, tmp, el_size);
  free(tmp);
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

void flush_stdin(void) {
  int c;
  while ((c = getchar()) != EOF && c != '\n');
}

void *safe_malloc(size_t size) {
  errno = 0;
  void *ptr = malloc(size);
  if (!ptr || errno != 0)
    return NULL;

  return ptr;
}
