#include "random.h"

void seed_with_timestamp(void) {
  srand((int) time(NULL));
  // First call to rand() in macOS always returns the same value, regardless of
  // seed. Discard it.
  rand();
}

double random_double(void) {
  return rand() / ((double) RAND_MAX + 1.0);
}

double random_range(double min, double max) {
  return random_double() * (max - min) + min;
}

int random_int(int min, int max) {
  return (int) (random_double() * (max - min + 1)) + min;
}

void shuffle(void *vec, size_t el_size, size_t length) {
  size_t j;
  for (size_t i = 0; i < length; i++) {
    j = random_int(0, (int) (length - 1));
    swap(
      (void *) ((char *) vec + i * el_size),
      (void *) ((char *) vec + j * el_size),
      el_size
    );
  }
}
