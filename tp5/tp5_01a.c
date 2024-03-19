#include <stdio.h>

int a, b; // (note: global vars are bad!)
void local(void);

int main(void) {
  a = 2; // This sets global variable a
  b = 3; // This sets global variable b

  local();
  printf("a vale %d\tb vale %d\n", a, b); // a = 2, b = 10
  return 0;
}

void local(void) {
  int a; // Local variable "shadows" global var of same name in this scope

  a = -5; // This sets local variable a
  b = 10; // This sets global variable b

  return;
}
