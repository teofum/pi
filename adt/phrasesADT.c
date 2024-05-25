#include <stdlib.h>
#include <string.h>

#include "phrasesADT.h"

#define BLOCK_SIZE 256

typedef struct phrasesCDT {
  const char **phrases;
  size_t key_from;
  size_t key_to;
  size_t key_count;
} phrasesCDT;

phrasesADT phrases_new(size_t key_from, size_t key_to) {
  if (key_from > key_to) return NULL;

  phrasesADT phrases = malloc(sizeof(phrasesCDT));

  // Use calloc so all pointers init to NULL
  size_t key_count = key_to - key_from + 1;
  phrases->phrases = calloc(key_count, sizeof(char *));
  phrases->key_from = key_from;
  phrases->key_to = key_to;
  phrases->key_count = key_count;

  return phrases;
}

void phrases_free(phrasesADT ph) {
  for (size_t i = 0; i < ph->key_count; i++) {
    free((void *) ph->phrases[i]);
  }
  free(ph->phrases);
  free(ph);
}

int phrases_put(phrasesADT ph, size_t key, const char *phrase) {
  if (key < ph->key_from || key > ph->key_to) return 0;

  size_t i = key - ph->key_from;
  free((void *) ph->phrases[i]);
  ph->phrases[i] = strdup(phrase);
  return 1;
}

char *phrases_get(const phrasesADT ph, size_t key) {
  if (key < ph->key_from || key > ph->key_to) return NULL;

  size_t i = key - ph->key_from;
  return strdup(ph->phrases[i]);
}

size_t phrases_size(const phrasesADT ph) {
  size_t count = 0;
  for (int i = 0; i < ph->key_count; i++) {
    count += ph->phrases[i] != NULL;
  }

  return count;
}

const char *phrases_concat_all(const phrasesADT ph) {
  return phrases_concat(ph, ph->key_from, ph->key_to);
}

// Copies src to the end of dst, expanding dst as necessary.
// Does not copy the null terminator.
static void cat(char **dst, size_t *dst_len, size_t *dst_cap, const char *src) {
  for (int i = 0; src[i] != '\0'; i++) {
    if (*dst_len == *dst_cap) {
      (*dst_cap) += BLOCK_SIZE;
      *dst = realloc(*dst, *dst_cap * sizeof(char));
    }

    (*dst)[(*dst_len)++] = src[i];
  }
}

const char *phrases_concat(const phrasesADT ph, size_t from, size_t to) {
  if (from < ph->key_from || from > ph->key_to ||
      to < ph->key_from || to > ph->key_to)
    return NULL;

  char *concat = NULL;
  size_t concat_len = 0;
  size_t concat_cap = 0;

  from -= ph->key_from;
  to -= ph->key_from;
  for (size_t i = from; i < to; i++) {
    if (ph->phrases[i] != NULL) {
      cat(&concat, &concat_len, &concat_cap, ph->phrases[i]);
    }
  }

  concat = realloc(concat, (concat_len + 1) * sizeof(char));
  concat[concat_len] = '\0';
  return concat;
}
