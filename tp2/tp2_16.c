#include <stdio.h>

int main(void) {
  printf("Enter two characters:\n");
  unsigned char a = getchar();
  unsigned char b = getchar();

  if (a == b) {
    printf("They're the same character\n");
  } else if (a > b) {
    printf("'%c' is greater than '%c'\n", a, b);
  } else {
    printf("'%c' is less than '%c'\n", a, b);
  }

  return 0;
}
