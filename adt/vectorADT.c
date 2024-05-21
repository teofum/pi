#include <stdlib.h>

#include "vectorADT.h"

typedef struct vec_elem {
  int empty;
  vec_elem_t elem;
} vec_elem;

typedef struct vectorCDT {
  vec_elem *data;
  size_t size;
  vec_comp_fn comp;
} vectorCDT;

vectorADT vec_new(vec_comp_fn comp) {
  vectorADT vec = malloc(sizeof(vectorCDT));
  vec->data = NULL;
  vec->size = 0;
  vec->comp = comp;

  return vec;
}

void vec_free(vectorADT v) {
  free(v->data);
  free(v);
}

size_t vec_put(vectorADT v, const vec_elem_t *elems, size_t dim, size_t index) {
  size_t need_size = index + dim;
  if (v->size < need_size) {
    v->data = realloc(v->data, need_size * sizeof(vec_elem)); // NOLINT(*)
    for (size_t i = v->size; i < need_size; i++) {
      v->data[i].empty = 1;
    }
    v->size = need_size;
  }

  size_t put_amt = 0;
  for (size_t i = 0; i < dim; i++) {
    if (v->data[index + i].empty) {
      v->data[index + i].elem = elems[i];
      v->data[index + i].empty = 0;
      put_amt++;
    }
  }

  return put_amt;
}

int vec_get_idx(vectorADT v, vec_elem_t elem) {
  for (int i = 0; i < v->size; i++) {
    if (!v->data[i].empty && !v->comp(v->data[i].elem, elem))
      return i;
  }

  return -1;
}

void vec_delete(vectorADT v, size_t index) {
  if (index < v->size) {
    v->data[index].empty = 1;
  }
}

size_t vec_elem_count(vectorADT v) {
  int count = 0;
  for (int i = 0; i < v->size; i++) {
    if (!v->data[i].empty) count++;
  }

  return count;
}


