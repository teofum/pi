#include <math.h>
#include <stdio.h>

#define SQUARE(x) ((x) * (x))
#define LENGTH(x0, y0, x1, y1) sqrt(SQUARE((x1) - (x0)) + SQUARE((y1) - (y0)))
#define DIAGONAL(x0, y0, x1, y1)                                               \
  (((x0) > (x1) || (y0) > (y1)) ? 0 : LENGTH(x0, y0, x1, y1))

#define DELTA 5

int main(void) {
  printf("%.2f\n", DIAGONAL(1, 2, 4, 6));                 // 5
  printf("%.2f\n", DIAGONAL(1, 2, 1 + DELTA, 2 + DELTA)); // 7.07
  printf("%.2f\n", DIAGONAL(1, 2, 3, 0));                 // 0
  return 0;
}
