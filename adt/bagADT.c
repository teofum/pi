#include <stdlib.h>

#include <vector.h>

#include "bagADT.h"

typedef struct bag_node {
  bag_elem_t elem;
  struct bag_node *tail;
} bag_node;

typedef struct bagCDT {
  bag_node *data;
  bag_comp_fn comp;
} bagCDT;

bagADT bag_new(bag_comp_fn comp) {
  bagADT bag = malloc(sizeof(bagCDT));
  bag->data = NULL;
  bag->comp = comp;

  return bag;
}

static void free_node(bag_node *node) {
  if (node != NULL) {
    free_node(node->tail);
    free(node);
  }
}

void bag_free(bagADT bag) {
  free_node(bag->data);
  free(bag);
}

static int node_count(bag_node *node, bag_elem_t elem, bag_comp_fn comp) {
  if (node == NULL) return 0;

  int cmp_res = comp(node->elem, elem);
  if (cmp_res > 0) return 0;
  return (cmp_res == 0) + node_count(node->tail, elem, comp);
}

int bag_count(bagADT bag, bag_elem_t elem) {
  return node_count(bag->data, elem, bag->comp);
}

static size_t node_size(bag_node *node, bag_comp_fn comp) {
  if (node == NULL) return 0;
  return node_size(node->tail, comp) +
         (node->tail == NULL || comp(node->elem, node->tail->elem) != 0);
}

size_t bag_size(bagADT bag) {
  return node_size(bag->data, bag->comp);
}

static bag_node *node_new(bag_elem_t elem, bag_node *tail) {
  bag_node *new_node = malloc(sizeof(bag_node));
  new_node->elem = elem;
  new_node->tail = tail;

  return new_node;
}

static bag_node *node_insert(
  bag_node *node,
  bag_elem_t elem,
  bag_comp_fn comp,
  unsigned *count
) {
  if (node == NULL) return node_new(elem, NULL); // Set is empty, insert node
  int cmp_res = comp(node->elem, elem);

  // Node elem > elem, insert elem before
  if (cmp_res > 0) return node_new(elem, node);

  // Node elem <= elem, check tail
  if (cmp_res == 0) (*count)++; // Set contains elem, increase count
  node->tail = node_insert(node->tail, elem, comp, count);
  return node;
}

unsigned bag_insert(bagADT bag, bag_elem_t elem) {
  unsigned count = 1; // Count after inserting will be 1 + before
  bag->data = node_insert(bag->data, elem, bag->comp, &count);
  return count;
}

static bag_node *node_remove(
  bag_node *node,
  bag_elem_t elem,
  bag_comp_fn comp,
  unsigned *count
) {
  if (node == NULL) return NULL;
  int cmp_res = comp(node->elem, elem);

  if (cmp_res > 0) return node; // Node elem > elem, elem not in bag
  if (cmp_res == 0) {
    if (node->tail && comp(node->tail->elem, elem) > 0) {
      bag_node *tail = node->tail;
      free(node);
      return tail; // Remove, we know it's not repeated
    } else {
      (*count)++;
    }
  }

  // Node elem < elem, check tail
  node->tail = node_remove(node->tail, elem, comp, count);
  return node;
}

unsigned bag_remove(bagADT bag, bag_elem_t elem) {
  unsigned count = 0;
  bag->data = node_remove(bag->data, elem, bag->comp, &count);
  return count;
}

typedef struct elem_counter {
  unsigned count;
  bag_elem_t elem;
} elem_counter;

void node_highest(
  bag_node *node,
  bag_comp_fn comp,
  elem_counter *highest,
  elem_counter *current
) {
  if (node == NULL) return;

  int cmp_res = comp(node->elem, current->elem);
  if (cmp_res == 0) {
    current->count++;
    if (current->count > highest->count) {
      highest->elem = current->elem;
      highest->count = current->count;
    }
  } else {
    current->elem = node->elem;
    current->count = 1;
  }

  node_highest(node->tail, comp, highest, current);
}

bag_elem_t bag_highest(bagADT bag) {
  if (bag->data == NULL) abort();

  elem_counter highest = {1, bag->data->elem};
  elem_counter current = {1, bag->data->elem};
  if (bag->data->tail) {
    node_highest(bag->data->tail, bag->comp, &highest, &current);
  }

  return highest.elem;
}
