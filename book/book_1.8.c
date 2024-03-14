#include <stdio.h>

int main(void) {
  int c;
  int spaces = 0, tabs = 0, newlines = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
    case ' ':
      spaces += 1;
      break;
    case '\t':
      tabs += 1;
      break;
    case '\n':
      newlines += 1;
      break;

    default:
      break;
    }
  }

  printf(
      "The file has %d spaces, %d tabs and %d newlines\n", spaces, tabs,
      newlines
  );

  return 0;
}
