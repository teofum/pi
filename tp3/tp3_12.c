#include <stdio.h>

int main(void) {
  int i;

  // a
  for (i = 3; i <= 23; i += 5) {
    printf("%d%s", i, i == 23 ? "" : ", ");
  }
  putchar('\n');

  // b
  for (i = 20; i >= -10; i -= 6) {
    printf("%d%s", i, i == -10 ? "" : ", ");
  }
  putchar('\n');

  // c
  for (i = 19; i <= 51; i += 8) {
    printf("%d%s", i, i == 51 ? "" : ", ");
  }
  putchar('\n');

  return 0;
}
