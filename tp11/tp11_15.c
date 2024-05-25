#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <moveToFrontADT.h>

static int compare(mtf_elem_t e1, mtf_elem_t e2) {
  return e1.code - e2.code;
}

int
main(void) {
  moveToFrontADT p = mtf_new(compare);

  mtf_elem_t aux = {1, "uno"};
  assert(mtf_add(p, aux) == 1);
  strcpy(aux.name, "dos");
  assert(mtf_add(p, aux) == 0);
  aux.code = 2;
  assert(mtf_add(p, aux) == 1);
  aux.code = 3;
  strcpy(aux.name, "tres");
  assert(mtf_add(p, aux) == 1);
  aux.code = 4;
  strcpy(aux.name, "cuatro");
  assert(mtf_add(p, aux) == 1);
  mtf_to_begin(p);

  while (mtf_has_next(p)) {
    aux = mtf_next(p);
    printf("%d %s ", aux.code, aux.name);
  }
  putchar('\n');

  aux.code = 5;
  mtf_elem_t *q = mtf_get(p, aux);
  assert(q == NULL);

  aux.code = 3;
  q = mtf_get(p, aux);
  printf("%d %s\n", q->code, q->name);
  assert(q->code == 3);
  assert(strcmp(q->name, "tres") == 0);
  free(q);

  // Volvemos a pedir el 3, que ahora debe estar al principio
  aux.code = 3;
  q = mtf_get(p, aux);
  printf("%d %s\n", q->code, q->name);
  assert(q->code == 3);
  assert(strcmp(q->name, "tres") == 0);
  free(q);

  mtf_to_begin(p);
  printf("Debe imprimir 3 tres 1 uno 2 dos 4 cuatro\n");
  int vec[] = {3, 1, 2, 4};
  int i = 0;
  while (mtf_has_next(p)) {
    aux = mtf_next(p);
    printf("%d %s ", aux.code, aux.name);
    int x = vec[i++];
    assert(aux.code == x);
  }
  putchar('\n');

  aux.code = 5;
  strcpy(aux.name, "cinco");
  assert(mtf_add(p, aux) == 1);
  q = mtf_get(p, aux);
  assert(q->code == 5);
  assert(strcmp(q->name, "cinco") == 0);
  free(q);
  mtf_to_begin(p);
  assert(mtf_next(p).code == 5);
  assert(mtf_next(p).code == 3);

  mtf_free(p);
  puts("OK primera parte!");

  // Insertamos miles de elementos
  int dim = 50000;
  p = mtf_new(compare);
  for (int i = 1; i <= dim; i++) {
    mtf_elem_t aux = {i, "foo"};
    assert(mtf_add(p, aux));
  }
  assert(mtf_size(p) == dim);
  aux.code = dim + 1;
  q = mtf_get(p, aux);
  assert(q == NULL);

  aux.code = dim - 10;
  q = mtf_get(p, aux);
  assert(q != NULL);
  assert(q->code == dim - 10);
  free(q);
  mtf_to_begin(p);
  assert(mtf_next(p).code == dim - 10);
  assert(mtf_next(p).code == 1);

  mtf_free(p);
  puts("OK segunda parte!");
  return 0;
}
