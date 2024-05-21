#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <llist.h>

llist remove_if(llist list, int (*criteria)(int));

int is_even(int n) {
  return n % 2 == 0;
}

int is_odd(int n) {
  return n % 2;
}

int true(int n) {
  return 1;
}


int main(void) {
  int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int v_i[] = {1, 3, 5, 7, 9};
  int v_p[] = {2, 4, 6, 8};
  int p[] = {2, 4, 6, 8, 4, 2, 0, -10};

  llist l1 = from_array(v, 9);
  l1 = remove_if(l1, is_even);
  assert(check_elems(l1, v_i, 5));
  list_free(l1);

  l1 = from_array(v, 9);
  l1 = remove_if(l1, is_odd);
  assert(check_elems(l1, v_p, 4));
  list_free(l1);

  l1 = from_array(v, 9);
  l1 = remove_if(l1, true);
  assert(l1 == NULL);
  list_free(l1);

  l1 = from_array(p, 8);
  l1 = remove_if(l1, is_even);
  assert(l1 == NULL);
  list_free(l1);

  l1 = from_array(p, 8);
  l1 = remove_if(l1, is_odd);
  assert(check_elems(l1, p, 8));
  list_free(l1);

  l1 = remove_if(NULL, is_odd);
  assert(l1 == NULL);
  list_free(l1);

  printf("OK!\n");
  return 0;
}

llist remove_if(llist list, int (*criteria)(int)) {
  if (list == NULL) return NULL;

  if (criteria(list->elem)) {
    llist tail = list->tail;
    free(list);
    list = remove_if(tail, criteria);
  } else {
    list->tail = remove_if(list->tail, criteria);
  }
  return list;
}
