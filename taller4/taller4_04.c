#include <stdio.h>

typedef unsigned int uint;

uint intersection_unsorted(
    const int a[],
    uint sa,
    const int b[],
    uint sb,
    int intersect[]
);
uint intersection(
    const int a[],
    uint sa,
    const int b[],
    uint sb,
    int intersect[]
);

int main(void) {
  int veca[] = {7, 9, 3, 5, 15};
  int vecb[] = {5, 6, 7, 9, 8};
  int res[5];

  int veca_s[] = {3, 5, 7, 9, 15};
  int vecb_s[] = {5, 6, 7, 8, 9};

  int count = intersection_unsorted(veca, 5, vecb, 5, res);
  printf("Intersection: ");
  for (int i = 0; i < count; i++)
    printf("%d ", res[i]);
  printf("\n");

  count = intersection(veca_s, 5, vecb_s, 5, res);
  printf("Intersection (sorted): ");
  for (int i = 0; i < count; i++)
    printf("%d ", res[i]);
  printf("\n");

  return 0;
}

int includes(int v, int vec[], uint size) {
  for (int i = 0; i < size; i++)
    if (vec[i] == v)
      return 1;
  return 0;
}

uint intersection_unsorted(
    const int a[],
    uint sa,
    const int b[],
    uint sb,
    int intersect[]
) {
  int int_size = 0;
  for (int i = 0; i < sa; i++)
    if (includes(a[i], b, sb))
      intersect[int_size++] = a[i];

  return int_size;
}

uint intersection(
    const int a[],
    uint sa,
    const int b[],
    uint sb,
    int intersect[]
) {
  int int_size = 0, i = 0, j = 0;

  while (i < sa && j < sb) {
    if (a[i] > b[j])
      j++;
    else if (b[j] > a[i])
      i++;
    else { // a[i] == b[j]
      intersect[int_size++] = a[i];
      i++;
      j++;
    }
  }

  return int_size;
}
