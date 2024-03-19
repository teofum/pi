#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

int digit_at(int num, int pos);

int main(void) {
  int boleto, esCapicua = 1;
  int j;

  boleto = get_int("Ingrese un número de 5 dígitos: ");
  if (boleto < 10000 || boleto > 99999) {
    puts("Ingreso incorrecto de datos");
    return 1;
  }

  for (j = 1; j <= 2; j++)
    if (digit_at(boleto, j) != digit_at(boleto, 5 - j + 1)) {
      esCapicua = 0;
      break;
    }
  printf("El boleto %ses capicúa\n", (esCapicua) ? "" : "no ");
  return 0;
}

int digit_at(int num, int pos) { return (num / (int)pow(10, pos - 1)) % 10; }
