#include <stdio.h>

int main(void) {
  int a, b;

  if ((a = getchar()) == (b = getchar())) {
    printf("The characters are equal\n");
  } else if (a > b) {
    printf("%c is greater than %c\n", a, b);
  } else {
    printf("%c is less than %c\n", a, b);
  }
}
