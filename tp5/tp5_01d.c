#include <stdio.h>

static int m;
int b;
static void este(void);

int main(void) {
  m = 2;
  b = 3;

  este();
  printf("m vale : %d\n", m);
  printf("b vale : %d\n", b);

  return 0;
}

static void este(void) {
  static int m; // static var still shadows global static!

  m++;
  b = -3;
  printf("Dentro de este() m vale %d y b vale %d\n", m, b);

  return;
}
