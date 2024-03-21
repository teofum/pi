#include <assert.h>
#include <stdio.h>

void join(const int vec1[], const int vec2[], int out[]);

void check(const int v1[], const int v2[]) {
  int i;
  for (i = 0; v1[i] != -1; i++)
    assert(v1[i] == v2[i]);
  assert(v1[i] == -1);
  assert(v2[i] == -1);
}

int main(void) {
  int v1[] = {1, 5, 15, 30, 35, 45, 55, -1};
  int v2[] = {-1};
  int v3[] = {1, -1};
  int v4[] = {2, 3, 15, 16, 33, 35, 45, 65, -1};
  int out[30];

  join(v1, v2, out);
  check(v1, out);
  printf("Test 1 OK!\n");

  join(v2, v2, out);
  check(v2, out);
  printf("Test 2 OK!\n");

  join(v1, v1, out);
  check(v1, out);
  printf("Test 3 OK!\n");

  join(v1, v3, out);
  check(v1, out);
  printf("Test 4 OK!\n");

  int expected[] = {1, 2, 3, 5, 15, 16, 30, 33, 35, 45, 55, 65, -1};
  join(v1, v4, out);
  check(expected, out);

  printf("All OK!\n");
  return 0;
}

void join(const int vec1[], const int vec2[], int out[]) {
  int i = 0, j = 0, k = 0, a = 0, b = 0;
  while (a != -1 || b != -1) {
    a = vec1[i];
    b = vec2[j];

    if ((b == -1 || a < b) && a != -1) {
      out[k++] = a;
      i++;
    } else if ((a == -1 || b < a) && b != -1) {
      out[k++] = b;
      j++;
    } else {
      // a = b
      out[k++] = a;
      i++;
      j++;
    }
  }

  out[k] = -1;
}
