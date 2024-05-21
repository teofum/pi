#include <stdlib.h>

#include "setADT.h"

typedef struct set_node {
  set_elem_t elem;
  struct set_node *tail;
} set_node;

typedef struct setCDT {
  set_node *data;
  set_comp_fn comp;
} setCDT;

setADT set_new(set_comp_fn comp) {
  setADT set = malloc(sizeof(setCDT));
  set->data = NULL;
  set->comp = comp;

  return set;
}

static void free_node(set_node *node) {
  if (node != NULL) {
    free_node(node->tail);
    free(node);
  }
}

void set_free(setADT set) {
  free_node(set->data);
  free(set);
}

static int node_includes(set_node *node, set_elem_t elem, set_comp_fn comp) {
  if (node == NULL) return 0;

  int cmp_res = comp(node->elem, elem);
  if (cmp_res > 0) return 0;
  if (cmp_res == 0) return 1;
  return node_includes(node->tail, elem, comp);
}

int set_includes(setADT set, set_elem_t elem) {
  return node_includes(set->data, elem, set->comp);
}

static size_t node_size(set_node *node) {
  if (node == NULL) return 0;
  return node_size(node->tail) + 1;
}

size_t set_size(setADT set) {
  return node_size(set->data);
}

int set_empty(setADT set) {
  return set->data == NULL;
}

static set_node *node_new(set_elem_t elem, set_node *tail) {
  set_node *new_node = malloc(sizeof(set_node));
  new_node->elem = elem;
  new_node->tail = tail;

  return new_node;
}

static set_node *node_insert(
  set_node *node,
  set_elem_t elem,
  set_comp_fn comp,
  int *exists
) {
  if (node == NULL) return node_new(elem, NULL); // Set is empty, insert node
  int cmp_res = comp(node->elem, elem);

  // Set contains elem, flag exists and change nothing
  if (cmp_res == 0) {
    *exists = 1;
    return node;
  }
  // Node elem > elem, insert elem before
  if (cmp_res > 0) return node_new(elem, node);

  // Node elem < elem, check tail
  node->tail = node_insert(node->tail, elem, comp, exists);
  return node;
}

int set_insert(setADT set, set_elem_t elem) {
  int exists = 0;
  set->data = node_insert(set->data, elem, set->comp, &exists);
  return !exists;
}

static set_node *node_remove(
  set_node *node,
  set_elem_t elem,
  set_comp_fn comp
) {
  if (node == NULL) return NULL;
  int cmp_res = comp(node->elem, elem);

  if (cmp_res > 0) return node; // Node elem > elem, elem not in set
  if (cmp_res == 0) {
    set_node *tail = node->tail;
    free(node);
    return tail; // Remove, we know it's not repeated
  }

  // Node elem < elem, check tail
  node->tail = node_remove(node->tail, elem, comp);
  return node;
}

void set_remove(setADT set, set_elem_t elem) {
  set->data = node_remove(set->data, elem, set->comp);
}

static set_node *node_union(set_node *a, set_node *b, set_comp_fn comp) {
  if (a == NULL && b == NULL) return NULL;

  if (a == NULL || (b != NULL && comp(a->elem, b->elem) > 0))
    return node_new(b->elem, node_union(a, b->tail, comp));

  if (b == NULL || comp(a->elem, b->elem) < 0)
    return node_new(a->elem, node_union(a->tail, b, comp));

  // a.elem = b.elem
  return node_new(a->elem, node_union(a->tail, b->tail, comp));
}

setADT set_union(setADT a, setADT b) {
  setADT union_set = set_new(a->comp);
  union_set->data = node_union(a->data, b->data, a->comp);

  return union_set;
}

static set_node *node_intersection(set_node *a, set_node *b, set_comp_fn comp) {
  if (a == NULL || b == NULL) return NULL;

  int cmp_res = comp(a->elem, b->elem);
  if (cmp_res > 0) return node_intersection(a, b->tail, comp);
  if (cmp_res < 0) return node_intersection(a->tail, b, comp);

  // a.elem = b.elem
  return node_new(a->elem, node_intersection(a->tail, b->tail, comp));
}

setADT set_intersection(setADT a, setADT b) {
  setADT intersection_set = set_new(a->comp);
  intersection_set->data = node_intersection(a->data, b->data, a->comp);

  return intersection_set;
}

static set_node *node_diff(set_node *a, set_node *b, set_comp_fn comp) {
  if (a == NULL) return NULL;
  if (b == NULL) return node_new(a->elem, node_diff(a->tail, b, comp));

  int cmp_res = comp(a->elem, b->elem);
  if (cmp_res > 0) return node_diff(a, b->tail, comp);
  if (cmp_res == 0) return node_diff(a->tail, b->tail, comp);

  // a.elem < b.elem, then a.elem is not in b
  return node_new(a->elem, node_diff(a->tail, b, comp));
}

setADT set_diff(setADT a, setADT b) {
  setADT diff_set = set_new(a->comp);
  diff_set->data = node_diff(a->data, b->data, a->comp);

  return diff_set;
}
