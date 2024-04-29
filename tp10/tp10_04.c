#include <stdio.h>
#include <assert.h>

#include "llist.h"

llist merge(llist list1, llist list2);

#define ELEMS 200

int main(void) {
  int even[ELEMS], odd[ELEMS];

  for (int i = 1; i <= ELEMS; i++) {
    even[i - 1] = i * 2;
    odd[i - 1] = i * 2 - 1;
  }

  llist l_even = from_array(even, ELEMS);
  llist l_odd = from_array(odd, ELEMS);

  l_even = merge(l_even, l_odd);

  int all[ELEMS * 2];
  for (int i = 1, j = 0; i <= ELEMS; i++) {
    all[j++] = i * 2 - 1;
    all[j++] = i * 2;
  }
  assert(check_elems(l_even, all, ELEMS * 2));
  list_free(l_even);

  l_even = NULL;
  l_even = merge(l_even, l_odd);
  assert(check_elems(l_even, odd, ELEMS));

  l_even = merge(l_even, l_odd);
  assert(check_elems(l_even, odd, ELEMS));
  list_free(l_even);

  l_even = from_array(even, ELEMS);
  l_odd = merge(l_odd, l_even);
  assert(check_elems(l_odd, all, ELEMS * 2));
  list_free(l_even);
  list_free(l_odd);

  int w[] = {1, 2, 3, 4, 5, 6, 7, 8};
  llist l1 = from_array(w, 3);
  llist l2 = from_array(w + 3, 5);
  l1 = merge(l1, l2);
  assert(check_elems(l1, w, 8));
  list_free(l1);
  list_free(l2);

  l1 = from_array(w, 8);
  l2 = from_array(w, 8);
  l1 = merge(l1, l2);
  assert(check_elems(l1, w, 8));
  list_free(l2);
  list_free(l1);

  printf("OK!\n");
  return 0;
}

llist merge(llist list1, llist list2) {
  if (list_empty(list2)) return list1;

  if (!list_empty(list1) && list1->elem == list2->elem) {
    list1->tail = merge(list1->tail, list2->tail); // list2 elem in list1, skip
  } else if (!list_empty(list1) && list2->elem > list1->elem) {
    list1->tail = merge(list1->tail, list2); // skip through list1 until larger
  } else {
    llist new = list_insert(list1, list2->elem);
    return merge(new, list2->tail);
  }

  return list1;
}
