#include <assert.h>
#include <stdio.h>

#include "llist.h"

llist list_union(llist list1, llist list2);

int main(void) {
  int v[] = {1, 4, 5, 6, 7, 8};
  int w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int x[] = {2, 3, 9};

  llist l1 = from_array(v, 6);
  llist l2 = from_array(w, 9);
  llist l3 = list_union(l1, l2);
  assert(check_elems(l3, w, 9));
  list_free(l3);

  l3 = list_union(l2, l1);
  assert(check_elems(l3, w, 9));
  list_free(l3);

  l3 = list_union(l2, l2);
  assert(check_elems(l3, w, 9));
  list_free(l3);

  l3 = list_union(l2, NULL);
  assert(check_elems(l3, w, 9));
  list_free(l3);

  l3 = list_union(NULL, l2);
  assert(check_elems(l3, w, 9));
  list_free(l3);
  list_free(l1);
  list_free(l2);

  l1 = from_array(v, 6);
  l2 = from_array(x, 3);
  l3 = list_union(l1, l2);
  list_free(l1);
  list_free(l2);
  assert(check_elems(l3, w, 9));
  list_free(l3);


  printf("OK!\n");
  return 0;
}

llist list_union(llist list1, llist list2) {
  if (list_empty(list1) && list_empty(list2)) return NULL;

  if (list_empty(list1) || (!list_empty(list2) && list1->elem > list2->elem))
    return list_insert(list_union(list1, list2->tail), list2->elem);

  if (list_empty(list2) || list1->elem < list2->elem)
    return list_insert(list_union(list1->tail, list2), list1->elem);

  return list_insert(list_union(list1->tail, list2->tail), list1->elem);
}
