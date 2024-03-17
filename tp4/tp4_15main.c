#include <stdio.h>

#include "../lib/my_getnum.h"
#include "tp4_15a.h"
#include "tp4_15b.h"

int main(void) {
  int x, y, z;

  x = get_int("Ingrese un numero: ");
  y = get_int("\nIngrese otro numero: ");
  z = get_int("\nIngrese ultimo numero: ");

  printf("\nEl mayor es %d\n", mayor3(x, y, z));
  printf("El promedio es %.2g\n", promedio3(x, y, z));

  return 0;
}
