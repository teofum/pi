#ifndef _vector_h
#define _vector_h

#include <stdlib.h>

#include "utils.h"

#define vec(t) vec_new(sizeof(t))
#define el(v, t, i) (((t *)((v).data))[(i)])

typedef struct {
  void *data;
  size_t el_size;
  size_t capacity;
  size_t size;
} vector;

vector vec_new(size_t el_size);

vector vec_with_capacity(size_t el_size, size_t capacity);

int vec_reserve(vector *v, size_t new_capacity);

int vec_push(vector *v, void *el);

int vec_pop(vector *v, void *el);

void vec_clear(vector *v);

void vec_delete(vector *v);

// Utilities for common types
int pushc(vector *v, char el);

char popc(vector *v);

char vgetc(vector v, size_t i);

int pushuc(vector *v, uchar el);

uchar popuc(vector *v);

uchar vgetuc(vector v, size_t i);

int pushi(vector *v, int el);

int popi(vector *v);

int vgeti(vector v, size_t i);

int pushu(vector *v, uint el);

uint popu(vector *v);

uint vgetu(vector v, size_t i);

int pushl(vector *v, long el);

long popl(vector *v);

long vgetl(vector v, size_t i);

int pushul(vector *v, ulong el);

ulong popul(vector *v);

ulong vgetul(vector v, size_t i);

int pushf(vector *v, float el);

float popf(vector *v);

float vgetf(vector v, size_t i);

int pushd(vector *v, double el);

double popd(vector *v);

double vgetd(vector v, size_t i);

int pushp(vector *v, void *el);

void *popp(vector *v);

void *vgetp(vector v, size_t i);

int pushs(vector *v, char *el);

char *pops(vector *v);

char *vgets(vector v, size_t i);

#endif
