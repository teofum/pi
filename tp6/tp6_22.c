#include <assert.h>
#include <stdio.h>

void asc_seq(const int vec[], size_t size, int *start, int *len);

int main(void) {
  // Para el vector {1, 1, 3, 4, 4, 7, 10, 9, 11} el comienzo es 1 y su longitud
  // es 3
  int v1[] = {1, 1, 3, 4, 4, 7, 10, 9, 11};
  int dim1 = sizeof(v1) / sizeof(v1[0]);
  int start1, len1;
  asc_seq(v1, dim1, &start1, &len1);
  assert(start1 == 1 && len1 == 3);

  // Para el vector vacío comienzo y longitud son 0 (cero)
  asc_seq(v1, 0, &start1, &len1);
  assert(start1 == 0 && len1 == 0);

  // Para los vectores {3}, {2, 2, 2} y  {3, 2, 1, 0, -1}  el comienzo es 0 y la
  // longitud es 1
  int v2[] = {3};
  int start2, len2;
  asc_seq(v2, 1, &start2, &len2);
  assert(start2 == 0 && len2 == 1);
  int v3[] = {2, 2, 2};
  int start3, len3;
  asc_seq(v3, 3, &start3, &len3);
  assert(start3 == 0 && len3 == 1);
  int v4[] = {3, 2, 1, 0, -1};
  int start4, len4;
  asc_seq(v4, 5, &start4, &len4);
  assert(start4 == 0 && len4 == 1);

  // Para el vector {1, 2, 3, 4, 5, 7, 10, 90, 111}  el comienzo es 0 y la
  // longitud 9
  int v5[] = {1, 2, 3, 4, 5, 7, 10, 90, 111};
  int dim5 = sizeof(v5) / sizeof(v5[0]);
  int start5, len5;
  asc_seq(v5, dim5, &start5, &len5);
  assert(start5 == 0 && len5 == 9);

  // Para el vector {1, 2, 1, 4, 5, 7, 1, 90, 111}  el comienzo es 2 y la
  // longitud 4
  int v6[] = {1, 2, 1, 4, 5, 7, 1, 90, 111};
  int dim6 = sizeof(v6) / sizeof(v6[0]);
  int start6, len6;
  asc_seq(v6, dim6, &start6, &len6);
  assert(start6 == 2 && len6 == 4);

  puts("OK!");
  return 0;
}

void asc_seq(const int vec[], size_t size, int *start, int *len) {
  *start = *len = 0; // we'll use outputs to keep track of longest sequence
  if (!size)
    return; // handle size = 0 case, we don't need to do anything

  int current_start = 0, current_len = 1;

  for (int i = 1; i < size; i++) {
    int el = vec[i], last = vec[i - 1];
    if (el > last) {
      current_len++;
    } else {
      // check if longer than longest seq
      if (current_len > *len) {
        *start = current_start;
        *len = current_len;
      }
      // reset counters
      current_start = i;
      current_len = 1;
    }
  }

  // check last sequence on array end
  if (current_len > *len) {
    *start = current_start;
    *len = current_len;
  }
}
