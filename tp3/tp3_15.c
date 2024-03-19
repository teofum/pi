#include <stdio.h>

#include "my_getnum.h"

int main(void) {
  int valid_binary;
  do {
    int input = get_int("Enter a binary number: ");
    int n = input, decimal = 0, power = 1;
    valid_binary = 1;

    // Break the loop if number is invalid
    while (n > 0 && valid_binary) {
      int last_digit = n % 10;
      if (last_digit <= 1) {
        decimal += last_digit * power;
      } else {
        valid_binary = 0; // Invalid binary digit is not 0 or 1
      }

      n /= 10;
      power *= 2;
    }

    if (valid_binary) {
      printf("%d in decimal is %d\n", input, decimal);
    } else {
      printf("%d is not a valid binary number\n", input);
    }
  } while (!valid_binary);

  return 0;
}
