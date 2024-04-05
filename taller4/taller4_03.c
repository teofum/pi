#include <stdio.h>

#include "my_getnum.h"

typedef unsigned int uint;

uint find(int v, const int vec[], uint size, int positions[]);

int main(void) {
  int arr[] = {3, 5, 5, 5, 5, 6, 7, 7, 8, 9, 12, 15};
  uint len = sizeof(arr) / sizeof(arr[0]);

  printf("Array: ");
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);
  printf("\n");

  int val = get_int("Enter a number to find: ");
  int res[len];
  uint count = find(val, arr, len, res);

  if (count) {
    printf("%d is in positions: ", val);
    for (int i = 0; i < count; i++)
      printf("%d ", res[i]);
    printf("\n");
  } else {
    printf("%d is not in the array\n", val);
  }

  return 0;
}

uint find(int v, const int vec[], uint size, int positions[]) {
  int count = 0;
  for (int i = 0; i < size && vec[i] <= v; i++) {
    if (vec[i] == v)
      positions[count++] = i;
  }

  return count;
}
