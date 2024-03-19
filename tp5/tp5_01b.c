#include <stdio.h>

int a, b, c;

void primero(void);
void segundo(void);

int main(void) {
  a = 1;

  // c = 0 (global variables are initialized to 0)
  printf("El valor de c es %d\n", c);
  segundo();
  printf("El valor de a es %d, el de b es %d\n", a, b); // a = 1, b = -2
  primero();
  printf("El valor de a es %d, el de c es %d\n", a, c); // a = 1, c = 0
  return 0;
}

void primero(void) {
  int a; // Shadows a
  a = 3;
  c = 0;
}

void segundo(void) {
  int a; // Shadows a
  c = 0;
  a = 2;
  b = -a;
}
