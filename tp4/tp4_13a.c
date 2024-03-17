#include "../lib/my_getnum.h" // Redundant, only so my run script autodetects lib use
#include "tp4_13.h"

int main(void) {
  float x, y, z;
  x = get_float("Ingrese un número real: ");
  putchar('\n');

  y = f1(x);
  z = f2(x);

  printf("El doble de %g es %g\n", x, y);
  printf("El triple de %g es %g\n", x, z);
  return 0;
}

float f1(float x) { return 2 * x; }
