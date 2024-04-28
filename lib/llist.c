#include <stdlib.h>

#include "llist.h"

int list_empty(llist l) {
  return l == NULL;
}

llist list_new(list_t value) {
  llist head = malloc(sizeof(lnode));
  head->elem = value;
  head->tail = NULL;

  return head;
}

llist from_array(list_t *arr, size_t size) {
  if (size == 0) return NULL;

  llist head = list_new(arr[0]);
  head->tail = from_array(arr + 1, size - 1);
  return head;
}

list_t list_get(llist l, size_t i) {
  if (i == 0) return l->elem;
  return list_get(l->tail, i - 1);
}

llist list_delete(llist l) {
  if (list_empty(l)) return l;

  llist tail = l->tail;
  l->tail = NULL;
  list_free(l);
  return tail;
}

void list_free(llist l) {
  if (l->tail != NULL) list_free(l->tail);
  free(l);
}

int check_elems(llist l, const list_t *v, size_t size) {
  if (size == 0) return list_empty(l);
  return !list_empty(l) && l->elem == *v &&
         check_elems(l->tail, v + 1, size - 1);
}
