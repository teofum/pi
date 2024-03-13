#include <stdio.h>

#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'z')
#define IS_LETTER(c) (IS_UPPERCASE_LETTER(c) || IS_LOWERCASE_LETTER(c))

#define IS_VOWEL_UPPER(c)                                                      \
  (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
#define IS_VOWEL_LOWER(c)                                                      \
  (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
#define IS_VOWEL(c) (IS_VOWEL_UPPER(c) || IS_VOWEL_LOWER(c))
#define IS_CONSONANT(c) (IS_LETTER(c) && !IS_VOWEL(c))

#define IS_EVEN(n) (n % 2 == 0)

#define IS_NUMBER(c) (c >= '0' && c <= '9')
#define TO_NUMBER(c) (c - '0')

int main(void) {
  int a, b, c;
  a = getchar();
  b = getchar();
  c = getchar();

  if (IS_UPPERCASE_LETTER(c) && IS_CONSONANT(c))
    printf("El caracter %c es una consonante mayúscula \n", a);
  else if (IS_LOWERCASE_LETTER(c) && IS_CONSONANT(c))
    printf("El caracter %c es una consonante minúscula \n", a);
  else if (IS_VOWEL(c))
    printf("El caracter %c es una vocal \n", a);
  else
    printf("El caracter %c no es una letra \n", a);

  if (IS_EVEN(c))
    printf("El valor ASCII de %c es par \n", b);

  if (IS_NUMBER(c) && IS_EVEN(TO_NUMBER(c)))
    printf("El caracter %c representa un dígito par \n", b);

  if (IS_VOWEL(c) || IS_UPPERCASE_LETTER(c))
    printf("El caracter %c es una vocal o es mayúscula \n", c);

  if (IS_CONSONANT(c))
    printf("El caracter %c no es una vocal pero es letra \n", c);
}
