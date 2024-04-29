#include <assert.h>
#include <stdio.h>

#include "llist.h"

llist list_intersect(llist list1, llist list2);

int main(void) {
  int v[] = {1, 4, 5, 6, 7, 8};
  int w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int x[] = {2, 3, 9};

  llist l1 = from_array(v, 6);
  llist l2 = from_array(w, 9);
  llist l3 = list_intersect(l1, l2);
  assert(check_elems(l3, v, 6));
  assert(check_elems(l1, v, 6));
  assert(check_elems(l2, w, 9));
  list_free(l3);

  l3 = list_intersect(l2, l1);
  assert(check_elems(l3, v, 6));
  list_free(l3);

  l3 = list_intersect(l2, l2);
  assert(check_elems(l3, w, 9));
  list_free(l3);

  l3 = list_intersect(l2, NULL);
  assert(l3 == NULL);
  l3 = list_intersect(NULL, l1);
  assert(l3 == NULL);
  l3 = list_intersect(NULL, NULL);
  assert(l3 == NULL);
  list_free(l1);
  list_free(l2);

  l1 = from_array(v, 6);
  l2 = from_array(x, 3);
  l3 = list_intersect(l1, l2);
  assert(l3 == NULL);
  list_free(l3);
  list_free(l1);
  list_free(l2);

  printf("OK!\n");
  return 0;
}

llist list_intersect(llist list1, llist list2) {
  if (list_empty(list1) || list_empty(list2)) return NULL;

  if (list1->elem == list2->elem)
    return list_insert(list_intersect(list1->tail, list2->tail), list1->elem);

  if (list1->elem < list2->elem)
    return list_intersect(list1->tail, list2);

  return list_intersect(list1, list2->tail);
}
