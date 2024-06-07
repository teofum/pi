#ifndef _bibleADT_h
#define _bibleADT_h

typedef struct bibleCDT *bibleADT;

bibleADT new_bible(void);

int add_verse(
  bibleADT bible,
  size_t n_book,
  size_t n_verse,
  const char *verse
);

const char *get_verse(
  bibleADT bible,
  size_t n_book,
  size_t n_verse
);

void free_bible(bibleADT bible);

#endif
