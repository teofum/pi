#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef struct node_brief *llist_brief;

typedef struct node_brief {
  list_t elem;
  size_t count;
  struct node_brief *tail;
} lnode_brief;

llist_brief list_brief_new(list_t head, llist_brief tail) {
  llist_brief list = malloc(sizeof(lnode_brief));
  list->elem = head;
  list->count = 1;
  list->tail = tail;

  return list;
}

void list_brief_free(llist_brief lb) {
  if (lb == NULL) return;
  list_brief_free(lb->tail);
  free(lb);
}

llist_brief compact(llist list);

int main(void) {
  int v[] = {1, 1, 2, 3, 3, 3, 3, 3, 10, 100, 100, 998};
  llist list = from_array(v, sizeof(v) / sizeof(v[0]));
  llist_brief bf = compact(list);

  llist_brief aux = bf;
  assert(aux->elem == 1 && aux->count == 2);

  aux = aux->tail;
  assert(aux->elem == 2 && aux->count == 1);

  aux = aux->tail;
  assert(aux->elem == 3 && aux->count == 5);

  aux = aux->tail;
  assert(aux->elem == 10 && aux->count == 1);

  aux = aux->tail;
  assert(aux->elem == 100 && aux->count == 2);

  aux = aux->tail;
  assert(aux->elem == 998 && aux->count == 1);

  aux = aux->tail;
  assert(aux == NULL);

  list_free(list);
  list_brief_free(bf);

  printf("OK!\n");
  return 0;
}

llist_brief compact(llist list) {
  if (list_empty(list)) return NULL;

  llist_brief tail = compact(list->tail);
  if (tail != NULL && tail->elem == list->elem) {
    tail->count++;
    return tail;
  }

  return list_brief_new(list->elem, tail);
}
