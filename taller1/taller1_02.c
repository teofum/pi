#include <stdio.h>

#include "../lib/my_getnum.h"

int main() {
  int a = get_int("Enter an integer: ");
  int b = get_int("Enter an integer: ");
  int c = get_int("Enter an integer: ");

  printf("%d\n", a > b ? (c > a ? c : a) : (c > b ? c : b));

  return 0;
}