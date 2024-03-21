#include <assert.h>
#include <stdio.h>

int dedupe_sorted(const int vec[], int size, int out[]);

int main(void) {
  int v[] = {-3, 1, 1, 3, 3, 3, 5, 5};
  int out[20];
  int out_size;

  out_size = dedupe_sorted(v, 0, out);
  assert(out_size == 0);

  out_size = dedupe_sorted(v, 1, out);
  assert(out_size == 1);
  assert(out[0] == -3);

  out_size = dedupe_sorted(v, 2, out);
  assert(out_size == 2);
  assert(out[0] == -3);
  assert(out[1] == 1);

  out_size = dedupe_sorted(v, 4, out);
  assert(out_size == 3);
  assert(out[0] == -3);
  assert(out[1] == 1);
  assert(out[2] == 3);

  out_size = dedupe_sorted(v, 8, out);
  assert(out_size == 4);
  assert(out[0] == -3);
  assert(out[1] == 1);
  assert(out[2] == 3);
  assert(out[3] == 5);

  for (int i = 0; i < 8; i++)
    v[i] = 10;
  out_size = dedupe_sorted(v, 8, out);
  assert(out_size == 1);
  assert(out[0] == 10);

  for (int i = 0; i < 8; i++)
    v[i] = i;
  out_size = dedupe_sorted(v, 8, out);
  assert(out_size == 8);
  for (int i = 0; i < 8; i++)
    assert(out[i] == i);

  puts("OK!");
  return 0;
}

// If we assume the array is sorted, we can just check the last element
// for dupes and we don't need to go through the entire array, which is O(n^2)
int dedupe_sorted(const int vec[], int size, int out[]) {
  int out_i = 0;
  for (int i = 0; i < size; i++) {
    int v = vec[i];
    if (i == 0 || v != vec[i - 1])
      out[out_i++] = v;
  }

  return out_i;
}
