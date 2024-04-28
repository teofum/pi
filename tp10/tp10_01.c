#include <assert.h>
#include <stdio.h>

#include "llist.h"

#define isodd(n) ((n) < 0 ? -(n) % 2 :(n) % 2)

int sum(llist list);

// Version donde la lista vacia retorna 1
int odds1(llist list);

// Version donde la lista vacia retorna cero
int odds2(llist list);

int
main(void) {
  assert(sum(NULL) == 0);
  assert(odds1(NULL) == 1);
  assert(odds2(NULL) == 0);

  int v[] = {1, 3, 5, -1, 0, 2, 4, 3};
  llist l1 = from_array(v, 8);
  assert(sum(l1) == 17);
  assert(odds1(l1) == 0);
  assert(odds2(l1) == 0);
  list_free(l1);

  l1 = from_array(v, 4);
  assert(sum(l1) == 8);
  assert(odds1(l1) == 1);
  assert(odds2(l1) == 1);
  list_free(l1);

  l1 = from_array(v + 4, 3);
  assert(sum(l1) == 6);
  assert(odds1(l1) == 0);
  assert(odds2(l1) == 0);
  list_free(l1);

  puts("OK!");
  return 0;
}

int sum(llist list) {
  if (list_empty(list)) return 0;
  return list->elem + sum(list->tail);
}

// Version donde la lista vacia retorna 1
int odds1(llist list) {
  if (list_empty(list)) return 1;
  return isodd(list->elem) ? odds1(list->tail) : 0;
}

// Version donde la lista vacia retorna cero
int odds2(llist list) {
  if (list_empty(list)) return 0;
  if (list->tail == NULL) return isodd(list->elem);
  return isodd(list->elem) ? odds2(list->tail) : 0;
}
