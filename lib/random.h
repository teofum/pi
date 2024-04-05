#ifndef _random_h
#define _random_h

#include <stdlib.h>
#include <time.h>

// Seed the RNG with current time
void seed_with_timestamp(void);

// Returns a random double in range [0, 1)
double random();

// Returns a random double in range [min, max)
double random_range(double min, double max);

// Returns a random integer in range [min, max)
int random_int(int min, int max);

#endif
