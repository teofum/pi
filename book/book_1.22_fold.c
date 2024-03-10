#include <stdio.h>

#define MAX_LENGTH 80
#define TAB_SIZE 8

// Read a line from stdin and print it back to stdout, inserting newlines where
// necessary to keep line length below a threshold
// Returns 1 if EOF, 0 otherwise
int fold_line(void) {
  int c;
  int cursor = 0;

  char word[MAX_LENGTH + 1];
  int wi = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      word[wi] = '\0';
      printf(word);
      cursor += wi;

      putchar(c);
      if (c == '\t')
        cursor += TAB_SIZE - (cursor % TAB_SIZE);
      else if (c == ' ')
        cursor++;

      wi = 0;
    } else {
      word[wi] = c;
      wi++;

      // If a word is over MAX_LENGTH characters long, cut it
      if (wi >= MAX_LENGTH) {
        word[wi] = '\0';
        printf(word);
        cursor += wi;
        wi = 0;
      }
    }

    if (cursor + wi >= MAX_LENGTH) {
      putchar('\n');
      cursor = 0;
    }

    // End on newline
    if (c == '\n')
      break;
  }

  word[wi] = '\0';
  printf(word);

  return c == EOF;
}

int main(void) {
  int eof = 0;
  while (!eof)
    eof = fold_line();

  putchar('\n');

  return 0;
};