#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// =============================================================================
// setADT.h
// =============================================================================

typedef struct setCDT *setADT;
typedef int set_elem_t;

typedef int (*set_comp_fn)(set_elem_t, set_elem_t);

/* Retorna un nuevo conjunto de elementos genéricos. Al inicio está vacío */
setADT set_new(set_comp_fn comp);

/* Inserta elem siempre y cuando el elemento no esté
** en el conjunto. Retorna la cantidad total de elementos luego de agregar el elemento nuevo
*/
int set_add(setADT set, set_elem_t elem);

/* Retorna cuántos elementos hay en el conjunto */
int set_size(const setADT set);

/* Retorna una copia del mayor elemento del conjunto, NULL si no hay elementos */
set_elem_t *set_max(const setADT set);

/* Retorna una copia del menor elemento del conjunto, NULL si no hay elementos */
set_elem_t *set_min(const setADT set);

/* Retorna una copia del último elemento agregado en el conjunto, NULL si está vacío */
set_elem_t *set_last(const setADT set);

/* Retorna un vector con todos los elementos del conjunto, ordenados en forma ascendente */
set_elem_t *set_to_array(const setADT set);

void set_free(setADT set);

// =============================================================================
// setADT.c
// =============================================================================

typedef struct node {
  set_elem_t elem;
  struct node *tail;
} node;

typedef struct setCDT {
  node *data;
  node *max;
  node *last_added;
  size_t size;
  set_comp_fn comp;
} setCDT;

setADT set_new(set_comp_fn comp) {
  setADT set = calloc(1, sizeof(setCDT));
  set->comp = comp;

  return set;
}

static node *create_node(set_elem_t elem, node *tail) {
  node *n = malloc(sizeof(node));
  n->elem = elem;
  n->tail = tail;
  return n;
}

static node *node_add(
  node *n,
  set_elem_t elem,
  set_comp_fn comp,
  node **added
) {
  if (!n) {
    *added = create_node(elem, NULL);
    return *added;
  }

  int cmp_res = comp(elem, n->elem);
  if (!cmp_res) return n;

  if (cmp_res < 0) {
    *added = create_node(elem, n);
    return *added;
  }

  n->tail = node_add(n->tail, elem, comp, added);
  return n;
}

int set_add(setADT set, set_elem_t elem) {
  node *added = NULL;
  set->data = node_add(set->data, elem, set->comp, &added);

  if (added) {
    set->last_added = added;
    if (!set->max || set->comp(added->elem, set->max->elem) > 0) {
      set->max = added;
    }
    set->size++;
  }

  return (int) set->size;
}

int set_size(const setADT set) {
  return (int) set->size;
}

set_elem_t *set_max(const setADT set) {
  set_elem_t *elem = malloc(sizeof(set_elem_t));
  *elem = set->max->elem;
  return elem;
}

set_elem_t *set_min(const setADT set) {
  set_elem_t *elem = malloc(sizeof(set_elem_t));
  *elem = set->data->elem;
  return elem;
}

set_elem_t *set_last(const setADT set) {
  set_elem_t *elem = malloc(sizeof(set_elem_t));
  *elem = set->last_added->elem;
  return elem;
}

set_elem_t *set_to_array(const setADT set) {
  set_elem_t *arr = malloc(set->size * sizeof(set_elem_t));
  node *n = set->data;
  size_t i = 0;
  while (n) {
    arr[i++] = n->elem;
    n = n->tail;
  }

  return arr;
}

void set_free(setADT set) {
  node *n = set->data;
  while (n) {
    node *tail = n->tail;
    free(n);
    n = tail;
  }
  free(set);
}

// =============================================================================
// test.c
// =============================================================================

int comp(int lhs, int rhs) {
  return lhs - rhs;
}

int main(void) {
  setADT set = set_new(comp);

  set_add(set, 1);
  set_add(set, 2);
  set_add(set, 6);
  set_add(set, 7);
  set_add(set, 4);

  assert(set_size(set) == 5);

  set_elem_t *el;
  el = set_min(set);
  assert(*el == 1);
  free(el);
  el = set_max(set);
  assert(*el == 7);
  free(el);
  el = set_last(set);
  assert(*el == 4);
  free(el);

  set_elem_t *arr = set_to_array(set);
  assert(arr[0] == 1);
  assert(arr[1] == 2);
  assert(arr[2] == 4);
  assert(arr[3] == 6);
  assert(arr[4] == 7);
  free(arr);

  puts("OK");
  set_free(set);
  return 0;
}
