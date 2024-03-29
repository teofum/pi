#include <assert.h>
#include <stdio.h>

int dedupe(const int vec[], int size, int out[]);

int main(void) {
  int v[] = {3, 5, 1, 3, -3, 3, 5, 1};
  int out[20];
  int out_size;

  out_size = dedupe(v, 0, out);
  assert(out_size == 0);

  out_size = dedupe(v, 1, out);
  assert(out_size == 1);
  assert(out[0] == 3);

  out_size = dedupe(v, 2, out);
  assert(out_size == 2);
  assert(out[0] == 3);
  assert(out[1] == 5);

  out_size = dedupe(v, 4, out);
  assert(out_size == 3);
  assert(out[0] == 3);
  assert(out[1] == 5);
  assert(out[2] == 1);

  out_size = dedupe(v, 8, out);
  assert(out_size == 4);
  assert(out[0] == 3);
  assert(out[1] == 5);
  assert(out[2] == 1);
  assert(out[3] == -3);

  for (int i = 0; i < 8; i++)
    v[i] = 10;
  out_size = dedupe(v, 8, out);
  assert(out_size == 1);
  assert(out[0] == 10);

  for (int i = 0; i < 8; i++)
    v[i] = i;
  out_size = dedupe(v, 8, out);
  assert(out_size == 8);
  for (int i = 0; i < 8; i++)
    assert(out[i] == i);

  puts("OK!");
  return 0;
}

int includes(const int vec[], int size, int item) {
  for (int i = 0; i < size; i++)
    if (vec[i] == item)
      return 1;
  return 0;
}

int dedupe(const int vec[], int size, int out[]) {
  int out_i = 0;
  for (int i = 0; i < size; i++)
    if (!includes(vec, out_i, vec[i]))
      out[out_i++] = vec[i];

  return out_i;
}
