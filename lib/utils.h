#ifndef _utils_h
#define _utils_h

#include <stdlib.h>

typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

// Swaps the values of two integers
void swap(int *a, int *b);

// Sort an integer array using quicksort
void sort(int v[], int size);

// Clear stdin buffer
void flush_stdin(void);

#endif
