#include "skipListADT.h"

#include <random.h>
#include <stdio.h>

typedef struct sk_node {
  struct sk_node **tails;
  sk_elem_t key;
  uchar level;
} sk_node;

typedef struct skipListCDT {
  sk_node *head;
  sk_comp_fn comp;
  uchar max_level;
  sk_node *it;
} skipListCDT;

static sk_node *create_node(sk_elem_t key, uchar level) {
  sk_node *node = malloc(sizeof(sk_node));
  node->key = key;
  node->level = level;
  node->tails = calloc(level, sizeof(sk_node *));
  return node;
}

skipListADT sk_new(uchar max_level, sk_comp_fn cmp) {
  seed_with_timestamp(); // Seed randomness

  skipListADT list = malloc(sizeof(skipListCDT));
  list->max_level = max_level;
  list->head = create_node(sk_min_value, list->max_level);
  list->comp = cmp;

  sk_node *sentinel = create_node(sk_max_value, list->max_level);
  for (int i = 0; i < max_level; i++)
    list->head->tails[i] = sentinel;

  return list;
}

// assumes node != NULL && level <= node->max_level
void node_insert(
  sk_node *node,
  uchar level,
  sk_node *to_insert,
  sk_comp_fn comp
) {
  sk_node *next = node->tails[level];
  int cmp_res = comp(to_insert->key, next->key);
  if (cmp_res >= 0) {
    node_insert(next, level, to_insert, comp);
  } else {
    // Add node at this level
    if (level < to_insert->level) {
      node->tails[level] = to_insert;
      to_insert->tails[level] = next;
    }

    // Add node at lower levels
    if (level > 0) node_insert(node, level - 1, to_insert, comp);
  }
}

void sk_insert(skipListADT list, sk_elem_t key) {
  uchar level = 1;
  while (random_int(0, 1) && level < list->max_level) level++;

  sk_node *to_insert = create_node(key, level);
  node_insert(list->head, list->max_level - 1, to_insert, list->comp);
}

// assumes node != NULL && level <= node->max_level
sk_node *node_search(
  sk_node *node,
  uchar level,
  sk_elem_t key,
  sk_comp_fn comp
) {
  sk_node *next = node->tails[level];
  int cmp_res = comp(key, next->key);
  if (!cmp_res) return next;
  if (cmp_res > 0) return node_search(next, level, key, comp);
  if (level > 0) return node_search(node, level - 1, key, comp);
  return NULL;
}

int sk_search(skipListADT list, sk_elem_t key) {
  return node_search(list->head, list->max_level - 1, key, list->comp) != NULL;
}

void sk_begin(skipListADT list) {
  list->it = list->head->tails[0];
}

int sk_has_next(const skipListADT list) {
  return list->it->tails[0] != NULL;
}

sk_elem_t sk_next(skipListADT list) {
  sk_elem_t key = list->it->key;
  list->it = list->it->tails[0];
  return key;
}

static void node_free(sk_node *node) {
  if (node) {
    node_free(node->tails[0]);
    free(node->tails);
    free(node);
  }
}

void sk_free(skipListADT list) {
  node_free(list->head);
  free(list);
}

void sk_display(skipListADT list) {
  for (int level = 0; level < list->max_level; level++) printf("=== ");
  putchar('\n');

  sk_begin(list);
  while (sk_has_next(list)) {
    for (int level = 0; level < list->max_level; level++) {
      if (level < list->it->level) printf(" ↓  ");
      else printf(" |  ");
    }
    putchar('\n');
    for (int level = 0; level < list->max_level; level++) {
      if (level < list->it->level) printf("%3d ", list->it->key);
      else printf(" |  ");
    }
    putchar('\n');
    sk_next(list);
  }

  for (int level = 0; level < list->max_level; level++) printf("=== ");
  putchar('\n');
}
