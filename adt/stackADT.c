#include <stdlib.h>

#include "stackADT.h"

#define BLOCK_SIZE 16

typedef struct stackCDT {
  int *data;
  size_t size;
  size_t capacity;
} stackCDT;

static int grow(stackADT stack) {
  stack->capacity += BLOCK_SIZE;
  int *new_data = realloc(stack->data, stack->capacity * sizeof(int));
  if (!new_data) return 0;

  stack->data = new_data;
  return 1;
}

stackADT new_stack(void) {
  stackADT stack = calloc(1, sizeof(stackCDT));
  return stack;
}

void free_stack(stackADT stack) {
  free(stack->data);
  free(stack);
}

int is_empty(const stackADT stack) {
  return stack->size == 0;
}

size_t size(const stackADT stack) {
  return stack->size;
}

void push(stackADT stack, int elem) {
  if (stack->size == stack->capacity) grow(stack);
  stack->data[(stack->size)++] = elem;
}

int pop(stackADT stack) {
  return stack->data[--(stack->size)];
}

int peek(const stackADT stack) {
  return stack->data[stack->size - 1];
}
