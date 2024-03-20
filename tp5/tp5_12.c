#include <ctype.h>
#include <stdio.h>

int main(void) {
  int n, c;

  do
    n = getint("");
  while (n <= 0 || n % 2);

  while ((c = getchar()) != EOF && isalnum(c) && !isupper(c))
    putchar(c);

  return 0;
}