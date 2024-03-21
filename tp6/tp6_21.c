#include <assert.h>
#include <math.h>
#include <stdio.h>

void simplify(int *num, int *den);
void add_fractions(int x1, int y1, int x2, int y2, int *r1, int *r2);

int gcd(int a, int b);

int main(void) {
  int num1, num2, den1, den2, numS, denS;

  printf("Simplify...\n");
  num1 = 10;
  den1 = 15;
  simplify(&num1, &den1);
  assert(num1 == 2 && den1 == 3);
  simplify(&num1, &den1);
  assert(num1 == 2 && den1 == 3);

  num1 = 150;
  den1 = 15;
  simplify(&num1, &den1);
  assert(num1 == 10 && den1 == 1);
  simplify(&num1, &den1);
  assert(num1 == 10 && den1 == 1);
  simplify(&den1, &num1);
  assert(num1 == 10 && den1 == 1);
  num1 = 12 * 5;
  den1 = 36 * 7;
  simplify(&num1, &den1);
  assert(num1 == 5 && den1 == 21);
  num1 = 0;
  den1 = 36;
  simplify(&num1, &den1);
  assert(num1 == 0 && den1 == 1);
  printf("Simplify OK!\n");

  printf("Add...\n");
  num1 = 150;
  den1 = 15;
  num2 = 15;
  den2 = 5;
  add_fractions(num1, num2, den1, den2, &numS, &denS);
  assert(numS == 13 && denS == 1);

  num2 = 7;
  den2 = 4;
  add_fractions(num1, num2, den1, den2, &numS, &denS);
  assert(numS == 47 && denS == 4);
  printf("Add OK!\n");

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

void simplify(int *num, int *den) {
  int d = gcd(*num, *den);
  *num /= d;
  *den /= d;
}

void add_fractions(int x1, int y1, int x2, int y2, int *r1, int *r2) {
  *r1 = (x1 * y2) + (y1 * x2);
  *r2 = x2 * y2;

  simplify(r1, r2);
}
