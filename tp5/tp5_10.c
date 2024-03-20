#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

enum option { SIMPLIFY = 0, ADD_FRACT, EXIT };

int gcd(int a, int b);
enum option menu(void);

void simplify_fraction(void);
void add_fractions(void);

int main(void) {
  int exit = 0;

  while (!exit) {
    enum option opt = menu();
    switch (opt) {
    case SIMPLIFY:
      simplify_fraction();
      break;
    case ADD_FRACT:
      add_fractions();
      break;
    case EXIT:
      return 0;
    }
  }

  return 0;
}

int gcd(int a, int b) {
  if (a < b) {
    // Swap a and b
    a += b;
    b = a - b;
    a = a - b;
  }

  int r = a % b;

  while (r > 0) {
    a = b;
    b = r;
    r = a % b;
  }

  return b;
}

enum option menu(void) {
  printf("Select an option:\n"
         "  1) Simplify fraction\n"
         "  2) Add fractions\n"
         "  3) Exit\n");

  int opt;
  do {
    printf("Enter a number 1-3\n");
    opt = getchar();
  } while (opt < '1' || opt > '3');

  return opt - '1';
}

void simplify_fraction(void) {
  int a = get_int("Enter numerator (x/_): ");
  int b = get_int("Enter denominator (%d/x): ", a);

  int d = gcd(a, b);

  printf("%d/%d = %d/%d\n", a, b, a / d, b / d);
}

void add_fractions(void) {
  int x1 = get_int("Enter numerator for X (x/_): ");
  int x2 = get_int("Enter denominator for X (%d/x): ", x1);

  int y1 = get_int("Enter numerator for Y (x/_): ");
  int y2 = get_int("Enter denominator for Y (%d/x): ", y1);

  int a = (x1 * y2) + (y1 * x2);
  int b = x2 * y2;

  int d = gcd(a, b);

  printf("%d/%d + %d/%d = %d/%d\n", x1, x2, y1, y2, a / d, b / d);
}
