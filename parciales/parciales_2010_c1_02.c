#include <stdio.h>

#define SPACE ' '

int main(void) {
  int c, last = 0;
  while ((c = getchar()) != EOF && c != '\n') {
    if (last == SPACE && c != SPACE) {
      // This is the first letter in a word
      last = c;

      // Skip spaces if there are any and set single-letter flag
      int single_letter = 0;
      while ((c = getchar()) == SPACE)
        single_letter = 1;

      if (!single_letter) {
        putchar(last); // Beginning of a normal word, print both letters
      }
    }

    putchar(c);
    last = c;
  }

  putchar('\n');
  return 0;
}
