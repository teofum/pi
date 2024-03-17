#include <stdio.h>

#define isdigit(c) (c >= '0' && c <= '9')
#define get_digit_value(c) (c - '0')

int main(void) {
  int digit_sum = 0;
  int in_decimal_part = 0;
  int c;

  printf("Enter a number: ");
  while ((c = getchar()) != EOF && c != '\n') {
    if (isdigit(c)) {
      if (in_decimal_part) {
        digit_sum += get_digit_value(c);
      }
    } else if (c == '.' && !in_decimal_part) {
      in_decimal_part = 1;
    }
    // Ignore any non-digit characters
  }

  printf("The sum of decimal digits is %d\n", digit_sum);

  return 0;
}
