#include <assert.h>
#include <math.h>
#include <stdio.h>

typedef int rational[2];
#define NUM(f) f[0]
#define DEN(f) f[1]

void simplify(rational f);
void add_fractions(const rational x, const rational y, rational result);

int main(void) {
  rational f1, f2, fSum;

  printf("Simplify...\n");
  NUM(f1) = 10;
  DEN(f1) = 15;
  simplify(f1);
  assert(NUM(f1) == 2 && DEN(f1) == 3);
  simplify(f1);
  assert(NUM(f1) == 2 && DEN(f1) == 3);

  NUM(f1) = 150;
  DEN(f1) = 15;
  simplify(f1);
  assert(NUM(f1) == 10 && DEN(f1) == 1);
  simplify(f1);
  assert(NUM(f1) == 10 && DEN(f1) == 1);

  NUM(f1) = 1;
  DEN(f1) = 10;
  simplify(f1);
  assert(NUM(f1) == 1 && DEN(f1) == 10);

  NUM(f1) = 12 * 5;
  DEN(f1) = 36 * 7;
  simplify(f1);
  assert(NUM(f1) == 5 && DEN(f1) == 21);
  NUM(f1) = 0;
  DEN(f1) = 36;
  simplify(f1);
  assert(NUM(f1) == 0 && DEN(f1) == 1);
  printf("Simplify OK!\n");

  printf("Add...\n");
  NUM(f1) = 150;
  DEN(f1) = 15;
  NUM(f2) = 15;
  DEN(f2) = 5;
  add_fractions(f1, f2, fSum);
  assert(NUM(fSum) == 13 && DEN(fSum) == 1);
  assert(NUM(f1) == 150 && DEN(f1) == 15);

  NUM(f2) = 7;
  DEN(f2) = 4;
  add_fractions(f1, f2, fSum);
  assert(NUM(fSum) == 47 && DEN(fSum) == 4);
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

void simplify(rational f) {
  int d = gcd(NUM(f), DEN(f));
  NUM(f) /= d;
  DEN(f) /= d;
}

void add_fractions(const rational x, const rational y, rational result) {
  NUM(result) = (NUM(x) * DEN(y)) + (NUM(y) * DEN(x));
  DEN(result) = DEN(x) * DEN(y);

  simplify(result);
}
