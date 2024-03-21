#include <assert.h>
#include <stdio.h>

int contains(const int v1[], unsigned int s1, const int v2[], unsigned int s2);

int main(void) {

  int v1[] = {1, 6, 5, 3, 2};
  int v2[] = {1, 2};
  assert(contains(v1, 5, v2, 2) == 2);
  assert(contains(v2, 2, v1, 5) == 1);
  assert(contains(v1, 1, v2, 2) == 1);
  assert(contains(v1, 0, v2, 2) == 1);
  assert(contains(v1, 5, v2, 0) == 2);

  int v3[] = {1, 2, 3, 4, 5, 6};
  assert(contains(v1, 5, v3, 6) == 1);

  int cnt = contains(v1, 0, v3, 0);
  assert(cnt == 1 || cnt == 2);

  int v4[] = {10, 20, 30, 1, 2};
  assert(contains(v2, 2, v4, 4) == 0);
  assert(contains(v2, 2, v4, 5) == 1);
  assert(contains(v4, 5, v2, 2) == 2);

  int v5[] = {1, 1, 1, 1, 1, 2, 1, 2};
  int v6[] = {1, 2, 3};
  assert(contains(v5, 8, v6, 3) == 1);
  assert(contains(v6, 3, v5, 8) == 2);

  printf("OK!\n");
  return 0;
}

int contains(const int v1[], unsigned int s1, const int v2[], unsigned int s2) {
  int v1_contains_v2 = 1;
  for (int i = 0; i < s1; i++) {
    int item = v1[i], in_v2 = 0;
    for (int j = 0; j < s2; j++) {
      if (v2[j] == item) {
        in_v2 = 1;
        break;
      }
    }
    if (!in_v2) {
      v1_contains_v2 = 0;
      break;
    }
  }
  if (v1_contains_v2)
    return 1;

  for (int i = 0; i < s2; i++) {
    int item = v2[i], in_v1 = 0;
    for (int j = 0; j < s1; j++) {
      if (v1[j] == item) {
        in_v1 = 1;
        break;
      }
    }
    if (!in_v1)
      return 0;
  }
  return 2;
}
