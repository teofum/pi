#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define CHARS (UCHAR_MAX + 1)

void collapse_nulls(char *str);
void analyze(const char *text, char *chars);

int main(void) {
  char chars[CHARS];
  char chars2[CHARS];
  analyze("El zorro mete la cola, pero no la pata!", chars);
  assert(strcmp(" !,Eacelmnoprtz", chars) == 0);
  analyze("ababababab", chars2);
  assert(strcmp("ab", chars2) == 0);

  analyze("", chars);
  assert(strcmp("", chars) == 0);
  analyze(".............................", chars);
  assert(strcmp(".", chars) == 0);

  puts("OK!");
  return 0;
}

// modified version of collapse_whitespace from 6.24
void collapse_nulls(char *str) {
  int nul_start = -1, nul_span = -1;
  char c;
  for (int cursor = 0; cursor < CHARS; cursor++) {
    c = str[cursor];

    if (c == '\0') {
      if (nul_start == -1) {
        nul_start = cursor;
        nul_span = 1;
      } else {
        nul_span++;
      }
    } else {
      if (nul_span > 0) {
        // end of a span of nulls
        // shift everything right of the cursor nul_span spaces to the left
        for (; cursor < CHARS; cursor++) {
          c = str[cursor];
          str[cursor - nul_span] = str[cursor];
        }

        // reset the cursor and span variables
        cursor = nul_start;
        c = str[cursor];
      }
      nul_start = -1;
      nul_span = -1;
    }
  }

  printf("\"%s\"\n", str);
}

void analyze(const char *text, char *chars) {
  // pass 1: clear chars array
  for (int i = 0; i < CHARS; i++)
    chars[i] = 0;

  // pass 2: fill chars array with characters present in the string
  // this has the advantage that the chars are already sorted!
  int c;
  int cursor = 0;
  while ((c = text[cursor++]) != '\0') {
    chars[c] = c;
  }

  // pass 3: clear out the blanks in between characters
  collapse_nulls(chars);
}
