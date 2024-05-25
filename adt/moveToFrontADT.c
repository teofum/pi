#include <stdlib.h>
#include <string.h>

#include "moveToFrontADT.h"

typedef struct mtf_node {
  mtf_elem_t value;
  struct mtf_node *tail;
} mtf_node;

typedef struct moveToFrontCDT {
  mtf_node *data;
  mtf_node *it;
  mtf_comp_fn comp;
} moveToFrontCDT;

moveToFrontADT mtf_new(mtf_comp_fn comp) {
  moveToFrontADT mtf = malloc(sizeof(moveToFrontCDT));
  mtf->comp = comp;
  mtf->data = NULL;
  mtf->it = NULL;

  return mtf;
}

static void free_node(mtf_node *node) {
  if (node) {
    free_node(node->tail);
    free(node);
  }
}

void mtf_free(moveToFrontADT mtf) {
  free_node(mtf->data);
  free(mtf);
}

static mtf_node *new_node(mtf_elem_t value) {
  mtf_node *node = malloc(sizeof(mtf_node));
  node->tail = NULL;
  node->value = value;

  return node;
}

static mtf_node *add_node(
  mtf_node *node,
  mtf_elem_t value,
  mtf_comp_fn comp,
  unsigned *added
) {
  if (!node) {
    *added = 1;
    return new_node(value);
  }

  if (comp(node->value, value)) {
    node->tail = add_node(node->tail, value, comp, added);
  }
  return node;
}

unsigned mtf_add(moveToFrontADT mtf, mtf_elem_t value) {
  unsigned added = 0;
  mtf->data = add_node(mtf->data, value, mtf->comp, &added);
  return added;
}

static unsigned node_size(mtf_node *node) {
  if (!node) return 0;
  return node_size(node->tail) + 1;
}

unsigned mtf_size(moveToFrontADT mtf) {
  return node_size(mtf->data);
}

void mtf_to_begin(moveToFrontADT mtf) {
  mtf->it = mtf->data;
}

int mtf_has_next(moveToFrontADT mtf) {
  return mtf->it != NULL;
}

mtf_elem_t mtf_next(moveToFrontADT mtf) {
  mtf_elem_t result = mtf->it->value;
  mtf->it = mtf->it->tail;
  return result;
}

static mtf_node *node_find(
  mtf_node *node,
  mtf_node *last,
  mtf_node **last_out,
  mtf_elem_t value,
  mtf_comp_fn comp
) {
  if (!node) return NULL;
  if (!comp(node->value, value)) {
    *last_out = last;
    return node;
  }
  return node_find(node->tail, node, last_out, value, comp);
}

mtf_elem_t *mtf_get(moveToFrontADT mtf, mtf_elem_t value) {
  mtf_node *last = NULL;
  mtf_node *node = node_find(mtf->data, NULL, &last, value, mtf->comp);
  if (!node) return NULL;

  if (last) {
    last->tail = node->tail;
    mtf_node *temp = mtf->data;
    mtf->data = node;
    node->tail = temp;
  }

  mtf_elem_t *value_copy = malloc(sizeof(mtf_elem_t));
  memcpy(value_copy, &node->value, sizeof(mtf_elem_t));
  return value_copy;
}
