#include <stdio.h>

/*
 * This code has many useless/superfluous comments
 * This is intentional! The file is its own test input :)
 */
int main(void) {
  int c;
  int inside_comment = 0;
  int inside_quotes = 0;

  printf("This /*comment*/ is inside quotes and should stay\n");

  while ((c = getchar()) != EOF) {
    if (c == '/' && !inside_quotes && !inside_comment) {
      if ((c = getchar()) == EOF)
        break;

      if (c == '/') {
        // This is a line comment, ignore the rest of the line
        while ((c = getchar()) != EOF && c != '\n') // Another line comment
          ;
        putchar('\n'); // Actually print the newline
      } else if (c == '*') {
        /* This is a regular C comment */
        inside_comment /* Comments can be in the middle of a line! */ = 1;
        /*
         * Comments can also
         * span multiple
         * lines
         */
      } else {
        putchar('/');
        putchar(c);
      }
    } else if (!inside_comment) {
      if (c == '"')
        inside_quotes = !inside_quotes;

      putchar(c);
    } else if (c == '*') {
      if ((c = getchar()) == EOF)
        break;

      if (c == '/')
        inside_comment = 0;
    }
  }

  putchar('\n');

  return 0;
}
