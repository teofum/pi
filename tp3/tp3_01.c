#include <stdio.h>

#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'z')

int main(void) {
  int c = getchar();

  if (IS_UPPERCASE_LETTER(c))
    printf("%c is uppercase\n", c);
  else if (IS_LOWERCASE_LETTER(c))
    printf("%c is lowercase\n", c);

  return 0;
}
