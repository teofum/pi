#include <stdio.h>

char letra;
void segundo(void);

int main(void) {
  printf("Ingrese un carácter: ");
  letra = getchar();
  segundo(); // does nothing because global var is shadowed in function body
  printf("letra es : %c\n", letra);
  return 0;
}

void segundo(void) {
  char letra;
  letra = 'X';
  return;
}
