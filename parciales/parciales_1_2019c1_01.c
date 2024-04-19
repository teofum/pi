#include <stdio.h>

// fills out with elements from v1 that are not in v1
// does not assume arrays are sorted
void subtract(const int v1[], const int v2[], int out[]);

// returns 1 if n is in v, 0 if not
int includes(const int v[], int n);

void print_array(const int v[]);

int main(void) {
  int v1[] = {1, 9, 2, 6, 3, 6, -1};
  int v2[] = {3, 2, 8, 2, -1};

  int res[10];
  subtract(v1, v2, res);
  print_array(res);

  subtract(v2, v1, res);
  print_array(res);

  subtract(v1, v1, res);
  print_array(res);

  return 0;
}

// note: this is O(n^2) by design, sorting the arrays first then assuming sorted
// would be actually faster (as you can quicksort in O(nlogn) time)
void subtract(const int v1[], const int v2[], int out[]) {
  int i = 0, j = 0;
  while (v1[i] != -1) {
    if (!includes(v2, v1[i])) {
      out[j++] = v1[i];
    }
    i++;
  }
  out[j] = -1;
}

int includes(const int v[], int n) {
  for (int i = 0; v[i] != -1; i++) {
    if (v[i] == n) {
      return 1;
    }
  }

  return 0;
}

void print_array(const int v[]) {
  for (int i = 0; v[i] != -1; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
}
