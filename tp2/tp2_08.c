#include <stdio.h>

#include "../lib/my_getnum.h"

#define SECONDS_PER_HOUR (60 * 60)
#define METERS_PER_KM 1000.0

#define MPS_TO_KPH SECONDS_PER_HOUR / METERS_PER_KM

int main(void) {
  float meters_per_second = get_float("Enter a speed in m/s:\n");

  printf("%.2f m/s = %.2f km/h\n", meters_per_second * MPS_TO_KPH);

  return 0;
}