#include "random.h"

int random_int(int min, int max) { return rand() % (max - min) + min; }
