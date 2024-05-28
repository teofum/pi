#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <listADT.h>

static int compare(list_elem_t e1, list_elem_t e2) {
  return e1 - e2;
}

int
main(void) {
  listADT c = list_new(sk_comp_fn); // una lista, en este caso de int
  list_to_begin(c);
  assert(!list_has_next(c));
  assert(!list_has_next_asc(c));
  list_add(c, 3);
  list_add(c, 1);
  list_add(c, 5);
  list_add(c, 2);
  list_to_begin(c);         // iterador por orden de insercià¸£à¸“n
  int n = list_next(c);    // n = 3
  assert(n == 3);
  n = list_next(c);        // n = 1
  assert(n == 1);

  list_to_begin_asc(c);      // iterador por orden ascendente

  assert(list_has_next(c));
  assert(list_has_next_asc(c));

  n = list_next_asc(c);     // n = 1
  assert(n == 1);

  n = list_next(c);        // n = 5
  assert(n == 5);

  n = list_next(c);        // n = 2
  assert(n == 2);
  assert(!list_has_next(c));

  n = list_next_asc(c);     // n = 2
  assert(n == 2);

  n = list_next_asc(c);     // n = 3
  assert(n == 3);

  n = list_next_asc(c);     // n = 5
  assert(n == 5);

  assert(!list_has_next_asc(c));

  list_free(c);

  puts("OK!");

  return 0;
}
