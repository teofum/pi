#include <stdio.h>

#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'z')

#define TO_UPPERCASE 'A' - 'a'

int main(void) {
  printf("Enter a character:\n");
  unsigned char c = getchar();

  if (IS_LOWERCASE_LETTER(c)) {
    printf("%c\n", c + TO_UPPERCASE);
  } else if (IS_UPPERCASE_LETTER(c)) {
    printf("%c is already uppercase\n", c);
  } else {
    printf("%c is not a letter\n", c);
  }

  return 0;
}