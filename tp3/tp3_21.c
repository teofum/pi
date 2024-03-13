#include <stdio.h>

#include "../lib/my_getnum.h"

int main(void) {
  int input = -1;
  do {
    input = get_int("Enter a positive integer: ");
  } while (input < 0);

  // First, we need to know the number of digits
  int digits = 0, n = input, left = 1;
  while (n > 0) {
    digits += 1;
    n /= 10;
    left *= 10;
  }
  left /= 10;

  if (digits <= 1) {
    // All single-digit numbers are palindromes
    printf("%d is palindromic\n", input);
  } else {
    int palindromic = 1;
    int right = 1;

    for (int i = 0; i < digits / 2; i++) {
      int ith_right = input / right % 10;
      int ith_left = input / left % 10;

      if (ith_right != ith_left) {
        palindromic = 0;
        break;
      }

      right *= 10;
      left /= 10;
    }

    printf("%d is%s palindromic\n", input, palindromic ? "" : " not");
  }

  return 0;
}
