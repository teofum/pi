#include "random.h"

void seed_with_timestamp(void) {
  time_t t;
  time(&t);
  srand(t);
}

int random_int(int min, int max) { return rand() % (max - min) + min; }
