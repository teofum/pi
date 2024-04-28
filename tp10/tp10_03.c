#include <stdio.h>
#include <assert.h>

#include "llist.h"

void order(llist list);

int main(void) {
  int v[] = {1, 1, 2, 1, 0, -1, 3, 3, 3, 3, 3, 10, 9, 100, 100, 998};
  int dimV = sizeof(v) / sizeof(v[0]);
  llist list = from_array(v, dimV);

  order(list);
  int o[] = {1, 2, 3, 10, 100, 998};
  assert(check_elems(list, o, sizeof(o) / sizeof(o[0])) == 1);

  order(list);
  assert(check_elems(list, o, sizeof(o) / sizeof(o[0])) == 1);
  list_free(list);

  llist empty = NULL;
  order(empty);
  assert(empty == NULL);

  list = from_array(v, 1);
  order(list);
  assert(list->elem == 1 && list->tail == NULL);
  list_free(list);

  int w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  list = from_array(w, sizeof(w) / sizeof(w[0]));
  order(list);
  assert(list->elem == 1 && list->tail == NULL);
  list_free(list);

  printf("OK!\n");
  return 0;
}

void order(llist list) {
  if (list_empty(list) || list->tail == NULL) return;
  if (list->tail->elem <= list->elem) {
    list->tail = list_delete(list->tail);
    order(list);
  } else {
    order(list->tail);
  }
}
