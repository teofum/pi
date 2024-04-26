#include <stdio.h>
#include <assert.h>

void pyramid(int *cans, int *h);

int main(void) {
  int h = 0, cans = 10;
  pyramid(&cans, &h);
  assert(cans == 5 && h == 2);

  h = 0, cans = 55;
  pyramid(&cans, &h);
  assert(cans == 0 && h == 5);

  h = 0, cans = 1;
  pyramid(&cans, &h);
  assert(cans == 0 && h == 1);

  h = 0, cans = 2;
  pyramid(&cans, &h);
  assert(cans == 1 && h == 1);

  h = 0, cans = 3;
  pyramid(&cans, &h);
  assert(cans == 2 && h == 1);

  h = 0, cans = 4;
  pyramid(&cans, &h);
  assert(cans == 3 && h == 1);

  h = 0, cans = 5;
  pyramid(&cans, &h);
  assert(cans == 0 && h == 2);

  printf("OK!\n");
  return 0;
}

void pyramid(int *cans, int *h) {
  int nh = (*h) + 1;
  int needed = nh * nh;

  if (*cans >= needed) {
    *cans = (*cans) - needed;
    *h = nh;
    pyramid(cans, h);
  }
}
