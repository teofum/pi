#include <stdlib.h>
#include <string.h>

#include "rankingADT.h"
#include "utils.h"

#define BLOCK_SIZE 16

typedef struct rankingCDT {
  rank_elem_t *elems;
  size_t size;
  size_t capacity;
  rank_comp_fn cmp;
} rankingCDT;

rankingADT rank_new(rank_elem_t *elems, size_t dim, rank_comp_fn cmp) {
  rankingADT r = malloc(sizeof(rankingCDT));
  r->cmp = cmp;
  r->elems = NULL;
  r->size = dim;
  r->capacity = dim;

  if (dim > 0) {
    r->elems = realloc(r->elems, dim * sizeof(rank_elem_t));
    memcpy(r->elems, elems, dim * sizeof(rank_elem_t));
  }

  return r;
}

void rank_free(rankingADT r) {
  free(r->elems);
  free(r);
}

void rank_add(rankingADT ranking, rank_elem_t elem) {
  for (size_t i = 0; i < ranking->size; i++) {
    if (!ranking->cmp(elem, ranking->elems[i])) {
      if (i > 0) {
        swap(&ranking->elems[i - 1], &ranking->elems[i], sizeof(rank_elem_t));
      }
      return;
    }
  }

  if (ranking->size == ranking->capacity) {
    ranking->capacity += BLOCK_SIZE;
    ranking->elems = realloc(
      ranking->elems,
      ranking->capacity * sizeof(rank_elem_t));
  }

  ranking->elems[ranking->size++] = elem;
}

size_t rank_size(const rankingADT ranking) {
  return ranking->size;
}

int rank_get_by_ranking(rankingADT ranking, size_t n, rank_elem_t *elem) {
  if (n == 0 || n > ranking->size) return 0;
  *elem = ranking->elems[--n];
  if (n > 0) {
    swap(&ranking->elems[n - 1], &ranking->elems[n], sizeof(rank_elem_t));
  }
  return 1;
}

rank_elem_t *rank_get_top(const rankingADT ranking, size_t *top) {
  if (*top > ranking->size) *top = ranking->size;
  if (*top == 0) return NULL;

  rank_elem_t *top_elems = malloc(*top * sizeof(rank_elem_t));
  memcpy(top_elems, ranking->elems, *top * sizeof(rank_elem_t));
  return top_elems;
}

int rank_contains(rankingADT ranking, rank_elem_t elem) {
  for (int i = 0; i < ranking->size; i++) {
    if (!ranking->cmp(ranking->elems[i], elem)) {
      if (i > 0) {
        swap(&ranking->elems[i - 1], &ranking->elems[i], sizeof(rank_elem_t));
      }
      return 1;
    }
  }
  return 0;
}

void rank_down(rankingADT ranking, size_t n) {
  if (n >= ranking->size - 1) return;
  n--;
  swap(&ranking->elems[n], &ranking->elems[n + 1], sizeof(rank_elem_t));
}

int rank_get_pos(const rankingADT ranking, rank_elem_t elem) {
  for (int i = 0; i < ranking->size; i++) {
    if (!ranking->cmp(ranking->elems[i], elem)) {
      return i + 1;
    }
  }
  return 0;
}
