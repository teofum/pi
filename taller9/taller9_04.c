#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef int (*predicate)(int);

llist remove_if(llist list, predicate f);

int even(int n) {
  return n % 2 == 0;
}

int main(void) {
  int v[] = {2, 3, 4, 5};
  llist list = from_array(v, 4);

  list = remove_if(list, even);
  print_list(list, "%d");

  list_free(list);
  return 0;
}

llist remove_if(llist list, predicate f) {
  if (list == NULL) return NULL;

  if (f(list->elem)) {
    llist tail = list->tail;
    free(list);
    return remove_if(tail, f);
  }

  list->tail = remove_if(list->tail, f);
  return list;
}
