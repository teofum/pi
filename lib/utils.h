#ifndef _utils_h
#define _utils_h

#include <stdlib.h>

typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

// Swaps the values of two integers
void swap_int(int *a, int *b);

// Swaps anything
void swap(void *a, void *b, size_t el_size);

// Sort an integer array using quicksort
void sort(int v[], int size);

// Clear stdin buffer
void flush_stdin(void);

// Ensures NULL return on fail
void *safe_malloc(size_t size);

#endif
