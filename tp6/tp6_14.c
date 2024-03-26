#include <assert.h>
#include <stdio.h>

typedef unsigned int uint;

int included_in(const int v1[], uint s1, const int v2[], uint s2);
int contains(const int v1[], uint s1, const int v2[], uint s2);

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

/**
 * Returns 1 if v1 is included in v2, 0 otherwise.
 */
int included_in(const int v1[], uint s1, const int v2[], uint s2) {
  for (int i = 0; i < s1; i++) {
    int item = v1[i], in_v2 = 0;
    for (int j = 0; j < s2 && !in_v2; j++) {
      if (v2[j] == item)
        in_v2 = 1;
    }
    if (!in_v2)
      return 0;
  }
  return 1;
}

/**
 * Returns 1 if v1 is included in v2, 2 if v2 is included in v1, 0 otherwise.
 */
int contains(const int v1[], uint s1, const int v2[], uint s2) {
  if (included_in(v1, s1, v2, s2))
    return 1;

  return included_in(v2, s2, v1, s1) ? 2 : 0;
}
