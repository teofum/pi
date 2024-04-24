#include <errno.h>
#include <string.h>

#include "vector.h"

vector vec_new(size_t el_size) {
  return vec_with_capacity(el_size, 1);
}

vector vec_with_capacity(size_t el_size, size_t capacity) {
  void *data = malloc(el_size * capacity);
  vector vec = {data, el_size, capacity, 0};

  return vec;
}

int vec_reserve(vector *v, size_t new_capacity) {
  errno = 0;
  void *new_data = realloc(v->data, v->el_size * new_capacity);
  if (!new_data || errno)
    return 0;

  v->data = new_data;
  v->capacity = new_capacity;
  if (v->size > v->capacity)
    v->size = v->capacity;

  return 1;
}

static int vec_grow(vector *v) {
  size_t new_capacity = v->capacity == 1 ? 4 : v->capacity * 2;
  return vec_reserve(v, new_capacity);
}

int vec_push(vector *v, void *el) {
  if (v->size == v->capacity) {
    if (!vec_grow(v)) return 0;
  }

  void *head = (void *) (((char *) v->data) + v->el_size * (v->size++));
  memcpy(head, el, v->el_size);

  return 1;
}

int vec_pop(vector *v, void *el) {
  if (v->size == 0) return 0;

  void *head = (void *) (((char *) v->data) + v->el_size * (v->size--));
  if (el != NULL) memcpy(el, head, v->el_size);

  return 1;
}

void vec_clear(vector *v) {
  v->size = 0;
}

void vec_delete(vector *v) {
  free(v->data);
  v->data = NULL;
  v->capacity = 0;
  v->size = 0;
}

int pushc(vector *v, char el) {
  char *p_el = &el;
  return vec_push(v, p_el);
}

char popc(vector *v) {
  char el;
  vec_pop(v, &el);
  return el;
}

char vgetc(vector v, size_t i) {
  return el(v, char, i);
}

int pushuc(vector *v, uchar el) {
  uchar *p_el = &el;
  return vec_push(v, p_el);
}

uchar popuc(vector *v) {
  uchar el;
  vec_pop(v, &el);
  return el;
}

uchar vgetuc(vector v, size_t i) {
  return el(v, uchar, i);
}

int pushi(vector *v, int el) {
  int *p_el = &el;
  return vec_push(v, p_el);
}

int popi(vector *v) {
  int el;
  vec_pop(v, &el);
  return el;
}

int vgeti(vector v, size_t i) {
  return el(v, int, i);
}

int pushu(vector *v, uint el) {
  uint *p_el = &el;
  return vec_push(v, p_el);
}

uint popu(vector *v) {
  uint el;
  vec_pop(v, &el);
  return el;
}

uint vgetu(vector v, size_t i) {
  return el(v, uint, i);
}

int pushl(vector *v, long el) {
  long *p_el = &el;
  return vec_push(v, p_el);
}

long popl(vector *v) {
  long el;
  vec_pop(v, &el);
  return el;
}

long vgetl(vector v, size_t i) {
  return el(v, long, i);
}

int pushul(vector *v, ulong el) {
  ulong *p_el = &el;
  return vec_push(v, p_el);
}

ulong popul(vector *v) {
  ulong el;
  vec_pop(v, &el);
  return el;
}

ulong vgetul(vector v, size_t i) {
  return el(v, ulong, i);
}

int pushf(vector *v, float el) {
  float *p_el = &el;
  return vec_push(v, p_el);
}

float popf(vector *v) {
  float el;
  vec_pop(v, &el);
  return el;
}

float vgetf(vector v, size_t i) {
  return el(v, float, i);
}

int pushd(vector *v, double el) {
  double *p_el = &el;
  return vec_push(v, p_el);
}

double popd(vector *v) {
  double el;
  vec_pop(v, &el);
  return el;
}

double vgetd(vector v, size_t i) {
  return el(v, double, i);
}

int pushp(vector *v, void *el) {
  void **p_el = &el;
  return vec_push(v, p_el);
}

void *popp(vector *v) {
  void *el;
  vec_pop(v, &el);
  return el;
}

void *vgetp(vector v, size_t i) {
  return el(v, void *, i);
}

int pushs(vector *v, char *el) {
  char **p_el = &el;
  return vec_push(v, p_el);
}

char *pops(vector *v) {
  char *el;
  vec_pop(v, &el);
  return el;
}

char *vgets(vector v, size_t i) {
  return el(v, char *, i);
}
