#include <math.h>
#include <stdio.h>

#include "my_getnum.h"

enum option { SIMPLIFY = 0, ADD_FRACT, EXIT };

enum option menu(void);

int gcd(int a, int b);
void simplify(int* a, int* b);
void add_fractions(int x1, int x2, int y1, int y2, int* r1, int* r2);

int main(void) {
  int exit = 0;

  while (!exit) {
    enum option opt = menu();
    switch (opt) {
      case SIMPLIFY: {
        int a = get_int("Enter numerator (x/_): ");
        int b = get_int("Enter denominator (%d/x): ", a);
        int s1 = a, s2 = b;
        simplify(&s1, &s2);
        printf("%d/%d = %d/%d\n", a, b, s1, s2);
        break;
      }
      case ADD_FRACT: {
        int x1 = get_int("Enter numerator for X (x/_): ");
        int x2 = get_int("Enter denominator for X (%d/x): ", x1);

        int y1 = get_int("Enter numerator for Y (x/_): ");
        int y2 = get_int("Enter denominator for Y (%d/x): ", y1);

        int r1, r2;
        add_fractions(x1, x2, y1, y2, &r1, &r2);

        printf("%d/%d + %d/%d = %d/%d\n", x1, x2, y1, y2, r1, r2);
        break;
      }
      case EXIT:
        return 0;
    }
  }

  return 0;
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

void simplify(int* a, int* b) {
  int d = gcd(*a, *b);
  *a /= d;
  *b /= d;
}

void add_fractions(int x1, int x2, int y1, int y2, int* r1, int* r2) {
  int a = (x1 * y2) + (y1 * x2);
  int b = x2 * y2;

  simplify(&a, &b);
  *r1 = a;
  *r2 = b;
}
