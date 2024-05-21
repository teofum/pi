#include <stdio.h>
#include <assert.h>

#include <vectorADT.h>

int comp_int(vec_elem_t a, vec_elem_t b) {
  return a - b;
}

int main(void) {
  vectorADT v = vec_new(comp_int);
  vec_elem_t elems[] = {1, 2, 10, 20, 100, -2, 4};
  vec_elem_t elems2[] = {1, 3, 4, 10, 22, 33};

  assert(vec_get_idx(v, elems[2]) == -1);

  assert(vec_put(v, elems, 7, 3) == 7);
  assert(vec_elem_count(v) == 7);
  assert(vec_get_idx(v, 1) == 3);
  assert(vec_get_idx(v, 2) == 4);
  assert(vec_get_idx(v, 10) == 5);
  assert(vec_get_idx(v, 22) == -1);
  assert(vec_put(v, elems2, 6, 0) == 3);
  assert(vec_get_idx(v, 22) == -1);
  assert(vec_get_idx(v, 1) == 0);
  assert(vec_get_idx(v, 3) == 1);
  assert(vec_elem_count(v) == 10);
  assert(vec_put(v, elems2, 6, 0) == 0);   // v queda igual
  assert(vec_get_idx(v, 1) == 0);
  assert(vec_elem_count(v) == 10);
  vec_delete(v, 100);
  assert(vec_elem_count(v) == 10);
  vec_delete(v, 0);
  assert(vec_get_idx(v, 1) == 3);
  assert(vec_elem_count(v) == 9);
  // Volvemos a borrar el 0, no deberia decrementar la cantidad
  vec_delete(v, 0);
  assert(vec_elem_count(v) == 9);
  assert(vec_get_idx(v, 1) == 3);

  assert(vec_put(v, elems2 + 5, 1, 12) == 1);
  assert(vec_elem_count(v) == 10);
  assert(vec_get_idx(v, 33) == 12);
  assert(vec_get_idx(v, 0) == -1);

  vec_free(v);

  puts("OK!");

  return 0;
}
