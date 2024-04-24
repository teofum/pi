#include <stdio.h>

#include "vector.h"

int main(void) {
  vector vec = vec(int);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  pushi(&vec, 1);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  pushi(&vec, 2);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  pushi(&vec, 3);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  pushi(&vec, 45);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  pushi(&vec, 20);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  for (int i = 0; i < vec.size; i++) {
    printf("%d ", vgeti(vec, i));
  }
  putchar('\n');

  popi(&vec);
  popi(&vec);
  printf("size: %lu, capacity: %lu\n", vec.size, vec.capacity);

  for (int i = 0; i < vec.size; i++) {
    printf("%d ", vgeti(vec, i));
  }
  putchar('\n');

  vec_delete(&vec);
  return 0;
}
