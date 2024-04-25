#include <stdio.h>
#include <stddef.h>

#define my_offsetof(s, m) (size_t) (&(((s *)0)->m))

typedef struct {
  char d;
  int a, b, c;
} test;

int main(void) {
  printf("d: %lu / %lu\n", offsetof(test, d), my_offsetof(test, d));
  printf("a: %lu / %lu\n", offsetof(test, a), my_offsetof(test, a));
  printf("b: %lu / %lu\n", offsetof(test, b), my_offsetof(test, b));
  printf("c: %lu / %lu\n", offsetof(test, c), my_offsetof(test, c));
  return 0;
}
