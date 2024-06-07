#include <stdlib.h>
#include <string.h>

#include "bibleADT.h"

#define N_BOOKS 76
#define BLOCK_SIZE 256

typedef struct verse {
  char *data;
  size_t len;
} verse_t;

typedef struct book {
  verse_t *verses;
  size_t size;
} book_t;

typedef struct bibleCDT {
  book_t books[N_BOOKS];
} bibleCDT;

bibleADT new_bible(void) {
  bibleADT bible = malloc(sizeof(bibleCDT));
  for (size_t i = 0; i < N_BOOKS; i++) {
    bible->books[i].size = 0;
    bible->books[i].verses = NULL;
  }
  return bible;
}

static void copy_verse(verse_t *verse, const char *verse_str) {
  char c;
  while ((c = verse_str[verse->len]) != '\0') {
    if (verse->len % BLOCK_SIZE == 0)
      verse->data = realloc(verse->data, verse->len + BLOCK_SIZE);

    verse->data[verse->len++] = c;
  }

  verse->data = realloc(verse->data, verse->len + 1);
  verse->data[verse->len] = '\0';
}

int add_verse(
  bibleADT bible,
  size_t n_book,
  size_t n_verse,
  const char *verse_str
) {
  book_t *book = &bible->books[n_book - 1];
  if (n_verse > book->size) {
    book->verses = realloc(book->verses, n_verse * sizeof(verse_t));
    for (size_t i = book->size; i < n_verse; i++) {
      book->verses[i].data = NULL;
      book->verses[i].len = 0;
    }
    book->size = n_verse;
  }

  if (book->verses[n_verse - 1].data) return 0;
  copy_verse(&book->verses[n_verse - 1], verse_str);
  return 1;
}

const char *get_verse(bibleADT bible, size_t n_book, size_t n_verse) {
  if (n_book >= N_BOOKS || n_verse >= bible->books[n_book - 1].size)
    return NULL;

  verse_t *verse = &bible->books[n_book - 1].verses[n_verse - 1];
  if (!verse->data) return NULL;

  char *text = malloc(verse->len + 1);
  strcpy(text, verse->data);

  return text;
}

void free_bible(bibleADT bible) {
  for (size_t i = 0; i < N_BOOKS; i++) {
    for (size_t j = 0; j < bible->books[i].size; j++)
      free(bible->books[i].verses[j].data);
    free(bible->books[i].verses);
  }
  free(bible);
}
