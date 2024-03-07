#include <stdio.h>

int main(void) {
  unsigned char a = getchar();
  unsigned char b = getchar();

  printf("%c\n", a > b ? a : b);

  return 0;
}