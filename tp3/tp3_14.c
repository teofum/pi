#include <limits.h>
#include <stdio.h>

#define SPACE ' '

#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'z')
#define IS_LETTER(c) (IS_UPPERCASE_LETTER(c) || IS_LOWERCASE_LETTER(c))

#define IGNORE 999

#define ALPHA_VALUE(c) (IS_LOWERCASE_LETTER(c) ? c - 'a' : c - 'A')

int main(void) {
  int c, value;
  unsigned char min = UCHAR_MAX;

  while ((c = getchar()) == SPACE || IS_LETTER(c)) {
    value = c == SPACE ? IGNORE : ALPHA_VALUE(c);
    if (value < ALPHA_VALUE(min))
      min = c;
  }

  printf("%c\n", min);

  return 0;
}
