#include <stdio.h>

int main(void) {
  char letra;
  printf("\nIngrese una letra:");
  letra = getchar();
  if (letra >= 'a' && letra <= 'z')
    printf("\n%c es una letra min�scula\n", letra);
  else if (letra >= 'A' && letra <= 'Z')
    printf("\n%c es una letra may�scula\n", letra);
  return 1;
}
