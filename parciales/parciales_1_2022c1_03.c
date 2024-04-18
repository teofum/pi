#include <stdio.h>

#define veclen(v) (sizeof(v) / sizeof(v[0]))

void ascending_sequence(int v[], int vlen, int *start, int *len);

int main(void) {
  int start, len;

  int vec1[] = {1, 1, 3, 4, 4, 7, 10, 9, 11};
  ascending_sequence(vec1, veclen(vec1), &start, &len);
  printf("start: %d, length: %d\n", start, len);

  int vec2[1]; // compiler doesn't like actual zero-size arrays
  ascending_sequence(vec2, 0, &start, &len);
  printf("start: %d, length: %d\n", start, len);

  int vec3[] = {3};
  ascending_sequence(vec3, veclen(vec3), &start, &len);
  printf("start: %d, length: %d\n", start, len);

  int vec4[] = {2, 2, 2};
  ascending_sequence(vec4, veclen(vec4), &start, &len);
  printf("start: %d, length: %d\n", start, len);

  int vec5[] = {3, 2, 1, 0, -1};
  ascending_sequence(vec5, veclen(vec5), &start, &len);
  printf("start: %d, length: %d\n", start, len);

  int vec6[] = {1, 2, 3, 4, 5, 7, 10, 90, 111};
  ascending_sequence(vec6, veclen(vec6), &start, &len);
  printf("start: %d, length: %d\n", start, len);

  return 0;
}

void ascending_sequence(int v[], int vlen, int *start, int *len) {
  *start = 0;
  *len = vlen ? 1 : 0; // return length 0 for empty array

  int current_start = 0, current_len = 1;
  for (int i = 1; i < vlen; i++) {
    if (v[i] > v[i - 1]) {
      current_len++;
      if (current_len > *len) {
        *start = current_start;
        *len = current_len;
      }
    } else {
      current_start = i;
      current_len = 1;
    }
  }
}
