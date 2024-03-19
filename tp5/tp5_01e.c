#include <stdio.h>

static int cubo(int num);

int main(void) {
  int x;

  for (x = 1; x <= 5; x++)
    printf("El cubo de %d es %4d\n", x, cubo(x));

  return 0;
}

static int cubo(int num) { return num * num * num; }
