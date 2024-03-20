#include <ctype.h>
#include <stdio.h>

#define IS_VOWEL_UPPER(c)                                                      \
  (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
#define IS_VOWEL_LOWER(c)                                                      \
  (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
#define IS_VOWEL(c) (IS_VOWEL_UPPER(c) || IS_VOWEL_LOWER(c))
#define IS_CONSONANT(c) (isalpha(c) && !IS_VOWEL(c))

#define IS_EVEN(n) (n % 2 == 0)

#define IS_NUMBER(c) (c >= '0' && c <= '9')
#define TO_NUMBER(c) (c - '0')

int main(void) {
  int a, b, c;
  a = getchar();
  b = getchar();
  c = getchar();

  if (isupper(c) && IS_CONSONANT(c))
    printf("El caracter %c es una consonante mayúscula \n", a);
  else if (islower(c) && IS_CONSONANT(c))
    printf("El caracter %c es una consonante minúscula \n", a);
  else if (is(c))
    printf("El caracter %c es una vocal \n", a);
  else
    printf("El caracter %c no es una letra \n", a);

  if (IS_EVEN(c))
    printf("El valor ASCII de %c es par \n", b);

  if (isdigit(c) && IS_EVEN(TO_NUMBER(c)))
    printf("El caracter %c representa un dígito par \n", b);

  if (IS_VOWEL(c) || isupper(c))
    printf("El caracter %c es una vocal o es mayúscula \n", c);

  if (IS_CONSONANT(c))
    printf("El caracter %c no es una vocal pero es letra \n", c);
}
