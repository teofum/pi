#include <stdio.h>

#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'z')
#define IS_LETTER(c) IS_LOWERCASE_LETTER(c) || IS_UPPERCASE_LETTER(c)

int main(void) {
  printf("Enter a character:\n");
  unsigned char c = getchar();

  if (IS_LETTER(c)) {
    printf("%c is a letter\n", c);
  } else {
    printf("%c is not a letter\n", c);
  }

  return 0;
}