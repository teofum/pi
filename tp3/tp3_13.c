#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int side = -1;
  do {
    side = get_int("Enter square size: ");
  } while (side < 0);

#ifdef A

  printf("Solution A, nested loops:\n");
  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      putchar('*');
    }
    putchar('\n');
  }

#else

  printf("Solution B, single loop:\n");
  int side_squared = side * side;
  for (int i = 1; i <= side_squared; i++) {
    putchar('*');
    if (i % side == 0)
      putchar('\n');
  }

#endif

  return 0;
}
