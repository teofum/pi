#include <stdio.h>
#include <stdlib.h>

#include "my_getnum.h"

#define BLOCK_SIZE 10

int *get_numbers(int *size);

int contains(const int *arr, int size, int n);

void push_int(int **arr, int *size, int n);

int main(void) {
  int size;
  int *arr = get_numbers(&size);

  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  putchar('\n');

  free(arr);
  return (0);
}

int *get_numbers(int *size) {
  *size = 0;
  int *arr = NULL, end = 0;

  while (!end) {
    int n = get_int("Enter a number: ");
    end = contains(arr, *size, n);
    if (!end) push_int(&arr, size, n);
  }

  arr = realloc(arr, *size * sizeof(int));
  return arr;
}

int contains(const int *arr, int size, int n) {
  for (int i = 0; i < size; i++)
    if (arr[i] == n) return 1;

  return 0;
}

void push_int(int **arr, int *size, int n) {
  if (*size % BLOCK_SIZE == 0)
    *arr = realloc(*arr, (*size + BLOCK_SIZE) * sizeof(int));

  (*arr)[(*size)++] = n;
}
