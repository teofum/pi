#include <assert.h>
#include <stdio.h>

#include "llist.h"

#define ELEMS 200

llist filter(llist list1, llist list2);

int main(void) {
  int even[ELEMS], odd[ELEMS];

  for (int i = 1; i <= ELEMS; i++) {
    even[i - 1] = i * 2;
    odd[i - 1] = i * 2 - 1;
  }

  llist lPar = from_array(even, ELEMS);
  llist lImpar = from_array(odd, ELEMS);

  llist lPar2 = filter(lPar, lImpar);
  assert(check_elems(lPar2, even, ELEMS));
  // Verificamos ademas que no sean los mismos nodos
  assert(lPar2 != lPar);
  assert(lPar2->tail != lPar->tail);
  list_free(lPar2);
  list_free(lPar);
  list_free(lImpar);

  int all[ELEMS * 2];
  for (int i = 1, j = 0; i <= ELEMS; i++) {
    all[j++] = i * 2 - 1;
    all[j++] = i * 2;
  }
  llist lAll = from_array(all, ELEMS * 2);
  lPar = from_array(even, ELEMS);
  llist lImpar2 = filter(lAll, lPar);
  assert(check_elems(lImpar2, odd, ELEMS));
  list_free(lPar);

  lPar = filter(lAll, lImpar2);
  assert(check_elems(lPar, even, ELEMS));
  list_free(lPar);
  list_free(lAll);

  lPar = NULL;
  lImpar = from_array(odd, ELEMS);
  llist aux = filter(lPar, lImpar);
  assert(aux == NULL);
  list_free(lImpar);

  aux = filter(lImpar2, lImpar2);
  assert(aux == NULL);
  list_free(lImpar2);

  printf("OK!\n");
  return 0;
}

llist filter(llist list1, llist list2) {
  if (list_empty(list2) || list_empty(list1)) return list_clone(list1);

  if (list1->elem == list2->elem)
    return filter(list1->tail, list2->tail);

  if (list1->elem > list2->elem)
    return filter(list1, list2->tail);

  return list_insert(filter(list1->tail, list2), list1->elem);
}
