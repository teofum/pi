#include <stdio.h>

#define TAB_SIZE 8

// Read a line from stdin and print it back to stdout
// with tabs changed to spaces
// Returns 1 if EOF, 0 otherwise
int entab_line() {
  int c;
  int i_in = 0;
  int cursor = 0;

  // Read characters into c until EOF
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      // If we find a tab character...
      // Calculate spaces until next tab stop (in output string)
      int spaces = TAB_SIZE - (cursor % TAB_SIZE);

      // Then print that many spaces
      for (int j = 0; j < spaces; j++) {
        putchar(' ');
        cursor++;
      }
    } else {
      // Not a tab, just print out the character
      putchar(c);
      cursor++;
    }

    // End on newline
    if (c == '\n')
      break;
  }

  return c == EOF;
}

int main(void) {
  int eof = 0;
  while (!eof)
    eof = entab_line();

  putchar('\n');

  return 0;
}