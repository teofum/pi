#include <stdlib.h>

#include "listADT.h"

typedef struct node {
  list_elem_t elem;
  struct node *next_asc;
  struct node *next_insert;
} node;

typedef node *list;

typedef struct listCDT {
  list elems_asc;
  list elems_insert;
  node *it_asc;
  node *it_insert;
  list_comp_fn comp;
} listCDT;

listADT list_new(list_comp_fn comp) {
  listADT list = malloc(sizeof(listCDT));
  list->elems_asc = NULL;
  list->elems_insert = NULL;
  list->comp = comp;
  list->it_asc = NULL;
  list->it_insert = NULL;

  return list;
}

static node *new_node(list_elem_t elem) {
  node *n = malloc(sizeof(node));
  n->elem = elem;
  n->next_insert = NULL;
  n->next_asc = NULL;

  return n;
}

static node *add_node_asc(
  node *list,
  list_elem_t elem,
  list_comp_fn comp,
  node **added
) {
  if (!list) {
    node *to_insert = new_node(elem);
    *added = to_insert;
    return to_insert;
  } else {
    int cmp_res = comp(list->elem, elem);
    if (!cmp_res) return list;
    else if (cmp_res > 0) {
      node *to_insert = new_node(elem);
      to_insert->next_asc = list;
      *added = to_insert;
      return to_insert;
    } else {
      list->next_asc = add_node_asc(list->next_asc, elem, comp, added);
      return list;
    }
  }
}

static node *add_node(node *list, node *to_insert) {
  if (!list) return to_insert;
  list->next_insert = add_node(list->next_insert, to_insert);
  return list;
}

void list_add(listADT list, list_elem_t elem) {
  node *added = NULL;
  list->elems_asc = add_node_asc(
    list->elems_asc,
    elem,
    list->comp,
    &added
  );
  if (added) {
    list->elems_insert = add_node(list->elems_insert, added);
  }
}

static node *remove_node_asc(node *n, list_elem_t elem, list_comp_fn comp) {
  if (!n) return NULL;
  if (!comp(n->elem, elem)) {
    return n->next_asc; // Remove from ordered list
  }

  n->next_asc = remove_node_asc(n->next_asc, elem, comp);
  return n;
}

static node *remove_node(node *n, list_elem_t elem, list_comp_fn comp) {
  if (!n) return NULL;
  if (!comp(n->elem, elem)) {
    // Remove from ordered list
    node *next = n->next_insert;
    free(n);
    return next;
  }

  n->next_insert = remove_node(n->next_insert, elem, comp);
  return n;
}

void list_remove(listADT list, list_elem_t elem) {
  list->elems_asc = remove_node_asc(list->elems_asc, elem, list->comp);
  list->elems_insert = remove_node(list->elems_insert, elem, list->comp);
}

void list_to_begin(listADT list) {
  list->it_insert = list->elems_insert;
}

int list_has_next(listADT list) {
  return list->it_insert != NULL;
}

list_elem_t list_next(listADT list) {
  list_elem_t elem = list->it_insert->elem;
  list->it_insert = list->it_insert->next_insert;
  return elem;
}

void list_to_begin_asc(listADT list) {
  list->it_asc = list->elems_asc;
}

int list_has_next_asc(listADT list) {
  return list->it_asc != NULL;
}

list_elem_t list_next_asc(listADT list) {
  list_elem_t elem = list->it_asc->elem;
  list->it_asc = list->it_asc->next_asc;
  return elem;
}

static void free_node(node *node) {
  if (node) {
    free_node(node->next_asc);
    free(node);
  }
}

void list_free(listADT list) {
  free_node(list->elems_asc);
  free(list);
}
