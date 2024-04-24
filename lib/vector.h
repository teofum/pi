#ifndef _vector_h
#define _vector_h

#include <stdlib.h>

typedef struct {
  void *data;
  size_t el_size;
  size_t capacity;
  size_t size;
} vector;



#endif
