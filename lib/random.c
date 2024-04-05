#include "random.h"

void seed_with_timestamp(void) {
  time_t t = time(NULL);
  srand(t);
}

double random() { return rand() / ((double)RAND_MAX + 1.0); }

double random_range(double min, double max) {
  return random() * (max - min) + min;
}

int random_int(int min, int max) {
  return (int)(random() * (max - min + 1)) + min;
}
