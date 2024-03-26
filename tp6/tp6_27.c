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
  int j = 0;
  for (int i = 0; i < CHARS; i++) {
    if (str[i] != '\0')
      str[j++] = str[i];
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
