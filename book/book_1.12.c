#include <stdio.h>

#define SPACE ' '
#define TAB '\t'

int main(void) {
  int c;

  while ((c = getchar()) != EOF) {
    putchar(c == SPACE || c == TAB ? '\n' : c);
  }

  return 0;
}
