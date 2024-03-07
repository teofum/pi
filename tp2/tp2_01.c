#include <stdio.h>

int main() {
  int x, y;
  x = (char)300;
  y = x++;

  printf("x = %d, y = %d\n", x, y);

  return 0;
}