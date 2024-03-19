#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

int digit_at(int num, int pos);

int main(void) {
  int ticket, palindrome = 1;
  int j;

  ticket = get_int("Enter a number: ");

  int num_digits = 0, tmp = ticket;
  while (tmp > 0) {
    num_digits++;
    tmp /= 10;
  }
  // If ticket = 0 then num_digits = 0 and we skip the whole calculation,
  // correctly returning that 0 is a palindrome

  for (j = 1; j <= num_digits / 2; j++)
    if (digit_at(ticket, j) != digit_at(ticket, num_digits - j + 1)) {
      palindrome = 0;
      break;
    }
  printf("The ticket is %sa palindrome\n", (palindrome) ? "" : "not ");
  return palindrome;
}

int digit_at(int num, int pos) { return (num / (int)pow(10, pos - 1)) % 10; }
