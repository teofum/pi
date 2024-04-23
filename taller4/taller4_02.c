#include <stdio.h>

#include "random.h"
#include "utils.h"

void shuffle_int(int vec[], int size);

void shuffle_terminated(int vec[]);

int main(void) {
  seed_with_timestamp();

  int arr[5] = {3, 5, 7, 9, 15};
  int arr_t[6] = {3, 5, 7, 9, 15, -1};

  shuffle_int(arr, 5);
  shuffle_terminated(arr_t);

  printf("Shuffled (length): ");
  for (int i = 0; i < 5; i++)
    printf("%d ", arr[i]);
  printf("\n");

  printf("Shuffled (-1-terminated): ");
  for (int i = 0; arr_t[i] != -1; i++)
    printf("%d ", arr_t[i]);
  printf("\n");

  return 0;
}

void shuffle_int(int vec[], int size) {
  int j;
  for (int i = 0; i < size; i++) {
    j = random_int(0, size - 1);
    swap_int(&vec[i], &vec[j]);
  }
}

void shuffle_terminated(int vec[]) {
  int j;
  for (int i = 0; vec[i] != -1; i++) {
    j = random_int(0, i);
    swap_int(&vec[i], &vec[j]);
  }
}
