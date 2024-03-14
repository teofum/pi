#include <stdio.h>

#define PI 3.141529
#define SPHERE_VOL(r) ((r) * (r) * (r) * PI * 4.0 / 3.0)

int main(void) {
  printf("Radius\tVolume\n");
  for (int r = 1; r <= 10; r++)
    printf("%6d\t%8.3f\n", r, SPHERE_VOL(r));

  return 0;
}
