#include <stdio.h>

#include "../lib/my_getnum.h"

int main() {
  int n = get_int("Enter an integer: ");

  char c = (n >= 0x0 && n <= 0x9)
               ? n + '0'
               : ((n >= 0xA && n <= 0xF) ? n + 'A' - 0xA : n);
  printf("%c\n", c);

  return 0;
}