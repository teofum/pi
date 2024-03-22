#include <stdio.h>

#include "my_getnum.h"

int friend_of(int a, int b);
int friends(int a, int b);

int main(void) {
  int a = get_int("Enter a positive integer: ");
  int b = get_int("Enter another positive integer: ");
  printf("%d and %d are %sfriends\n", a, b, friends(a, b) ? "" : "not ");

  return 0;
}

int friend_of(int a, int b) {
  // find sum of dividers of a
  int div_sum = 1; // 1 always divides
  for (int i = 2; i * i <= a; i++)
    if (a % i == 0) {
      div_sum += i;
      div_sum += (a / i);
    }

  return div_sum == b;
}

int friends(int a, int b) { return friend_of(a, b) && friend_of(b, a); }
