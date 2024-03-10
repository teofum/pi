#include <stdio.h>

#define TAB_SIZE 8
#define LINE_LENGTH 256 // Max input line length
// In this case, we don't need to define an output length because our output
// will always have less characters than the input

// Read a line from stdin and print it back to stdout
// with spaces changed to tabs+spaces
// Returns 1 if EOF, 0 otherwise
int entab_line() {
  int c, i_in;
  int cursor = 0;
  int spaces = 0;

  // Read characters into c until max input length is reached or EOF
  for (i_in = 0; i_in < LINE_LENGTH && (c = getchar()) != EOF; i_in++) {
    if (c == ' ') {
      // If we find a space character, count it
      spaces++;
    } else {
      // If we had spaces before this character...
      if (spaces) {
        // Length to next tab stop
        int to_next_stop = TAB_SIZE - (cursor % TAB_SIZE);

        if (                        //
          spaces > 1                // Never insert tab for a single space
          && spaces >= to_next_stop
        ) {
          // If there are enough spaces to reach a tab stop...
          // Insert the first tab
          putchar('\t');
          cursor += to_next_stop;
          spaces -= to_next_stop;

          // Insert any additional tabs needed
          while (spaces >= TAB_SIZE) {
            putchar('\t');
            cursor += TAB_SIZE;
            spaces -= TAB_SIZE;
          }
        }

        // Print leftover spaces
        for (int i = 0; i < spaces; i++) {
          putchar(' ');
          cursor++;
        }

        // Reset space counter
        spaces = 0;
      }

      // Print the character
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