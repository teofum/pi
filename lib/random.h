#ifndef _random_h
#define _random_h

#include <stdlib.h>
#include <time.h>

// Seed the RNG with current time
void seed_with_timestamp(void);

// Returns a random double in range [0, 1)
double random_double(void);

// Returns a random double in range [min, max)
double random_range(double min, double max);

// Returns a random integer in range [min, max)
int random_int(int min, int max);

// Returns a random long integer in range [min, max)
long random_long(long min, long max);

// Shuffle an array in place
void shuffle(void *vec, size_t el_size, size_t length);

#endif
