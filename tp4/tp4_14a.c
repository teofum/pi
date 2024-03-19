#include "my_getnum.h" // Redundant, only so my run script autodetects lib use
#include "tp4_14.h"

int main(void) {
  float x, y, z;
  x = get_float("Ingrese un número real: ");
  putchar('\n');

  y = f1(x);
  z = f2(x);

  printf("El doble absoluto de %g es %g\n", x, y);
  printf("El triple absoluto de %g es %g\n", x, z);
  return 0;
}

float f1(float x) { return 2 * funAuxiliar(x); }
