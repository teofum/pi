#include <assert.h>
#include <stdio.h>

#include "random.h"
#include "utils.h"

// Shuffle an array in place
void shuffle_int(int vec[], int size);

int main(void) {
  seed_with_timestamp();

  int v[] = {1, 2, 3, 4, 5, 6, 7, 8};
  shuffle_int(v, 8);

  printf("Shuffled:");
  for (int i = 0; i < 8; i++) {
    printf(" %d", v[i]);
  }
  putchar('\n');

  return 0;
}

void shuffle_int(int vec[], int size) {
  int j;
  for (int i = 0; i < size; i++) {
    j = random_int(0, size - 1);
    swap_int(&vec[i], &vec[j]);
  }
}
