#include <stdio.h>

#define SPACE ' '

int main(void) {
  int c;
  int consecutive_spaces = 0;

  while ((c = getchar()) != EOF) {
    if (c == SPACE) {
      if (!consecutive_spaces)
        putchar(c); // Output the first space only

      consecutive_spaces = 1;
    } else {
      consecutive_spaces = 0;
      putchar(c);
    }
  }

  return 0;
}
