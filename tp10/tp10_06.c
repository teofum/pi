#include <assert.h>
#include <stdio.h>

#include "llist.h"

/**
** En esta versión dejamos el primer elemento de una secuencia de repetidos
** Puede ser void porque el head de la lista no cambia
*/
void dedupe(llist list);

/*
** Dejamos el ultimo de la secuencia, por lo que la lista puede cambiar
*/
llist dedupe2(llist list);

int main(void) {

  // Secuencias sin repetir, cantidad par e impar de repetidos
  // Probar repetidos en el medio, al principio y al final
  // En realidad no hace falta que esten ordenados, deberia funcionar igual
  int v[] = {1, 2, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8};
  int w[] = {1, 2, 3, 4, 5, 6, 7, 8};

  llist l1 = from_array(v, 16);
  dedupe(l1);
  assert(check_elems(l1, w, 8));
  list_free(l1);

  l1 = from_array(v, 16);
  l1 = dedupe2(l1);
  assert(check_elems(l1, w, 8));
  list_free(l1);

  l1 = from_array(v, 1);
  dedupe(l1);
  assert(check_elems(l1, w, 1));
  list_free(l1);

  l1 = from_array(v, 1);
  l1 = dedupe2(l1);
  assert(check_elems(l1, w, 1));
  list_free(l1);

  l1 = from_array(v, 2);
  dedupe(l1);
  assert(check_elems(l1, w, 2));
  list_free(l1);

  l1 = from_array(v, 2);
  l1 = dedupe2(l1);
  assert(check_elems(l1, w, 2));
  list_free(l1);

  l1 = from_array(v, 4);
  dedupe(l1);
  assert(check_elems(l1, w, 3));
  list_free(l1);

  l1 = from_array(v, 4);
  l1 = dedupe2(l1);
  assert(check_elems(l1, w, 3));
  list_free(l1);

  l1 = from_array(v + 2, 5);
  dedupe(l1);
  assert(check_elems(l1, w + 2, 2));
  list_free(l1);

  l1 = from_array(v + 2, 5);
  l1 = dedupe2(l1);
  assert(check_elems(l1, w + 2, 2));
  list_free(l1);

  printf("OK!\n");
  return 0;
}

void dedupe(llist list) {
  if (!list_empty(list) && !list_empty(list->tail)) {
    dedupe(list->tail);

    list_t next = list->tail->elem;
    if (list->elem == next)
      list->tail = list_delete(list->tail);
  }
}

llist dedupe2(llist list) {
  if (!list_empty(list) && !list_empty(list->tail)) {
    list_t next = list->tail->elem;
    if (list->elem == next)
      return dedupe2(list_delete(list));

    list->tail = dedupe2(list->tail);
  }

  return list;
}
