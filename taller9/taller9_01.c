#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

llist concat_list(llist list1, llist list2);

int main(void) {
  int vec1[] = {4, 3, 7};
  int vec2[] = {3, 2, 6};
  llist list1 = from_array(vec1, 3);
  llist list2 = from_array(vec2, 3);

  llist concat = concat_list(list1, list2);
  print_list(concat, "%d");

  int res[] = {4, 3, 7, 3, 2, 6};
  assert(check_elems(concat, res, 6));

  list_free(list2);
  list_free(concat);
  printf("OK!\n");
}

//llist concat_list(llist list1, llist list2) {
//  if (list_empty(list1)) return list_clone(list2);
//
//  list1->tail = concat_list(list1->tail, list2);
//  return list1;
//}

llist concat_list(llist list1, llist list2) {
  if (list1 == NULL) {
    if (list2 == NULL) return NULL;

    llist head = malloc(sizeof(lnode));
    head->elem = list2->elem;
    head->tail = concat_list(list1, list2->tail);
    return head;
  }

  list1->tail = concat_list(list1->tail, list2);
  return list1;
}
