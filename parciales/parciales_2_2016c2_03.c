#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <random.h>

#define BLOCK_SIZE 128

// =============================================================================
// hangmanADT.h
// =============================================================================

typedef struct hangmanCDT *hangmanADT;

/* Crea la estructura que dará soporte al almacenamiento y selección de palabras
** maxLevel: la cantidad máxima de niveles de dificultad que soportará (como mínimo 1)
** Los niveles válidos serán de 1 a maxLevel inclusive
 */
hangmanADT hg_new(unsigned max_level);

/* Agrega un conjunto de palabras asociadas a un nivel de dificultad.
** El arreglo words[] está finalizado en NULL
** Si alguna de las palabras de words[] ya existe en el hangmanADT para ese nivel de dificultad
** se ignora.
** No se realiza una copia local de cada palabra sino únicamente los punteros recibidos
** Si el nivel supera la cantidad máxima definida en newHangman, se ignora y retorna -1
** Retorna cuántas palabras se agregaron al nivel
*/
int hg_add_words(hangmanADT h, char *words[], unsigned level);

/* Retorna cuántas palabras hay en un nivel, -1 si el nivel es inválido */
int hg_size(const hangmanADT h, unsigned level);

/* Retorna una palabra al azar de un nivel determinado, NULL si no hay palabras de ese nivel
** o si el nivel es inválido.
*/
char *hg_word(const hangmanADT h, unsigned level);

/* Retorna todas las palabras de un nivel, o NULL si el nivel es inválido
** El último elemento del vector es el puntero NULL
*/
char **hg_words(const hangmanADT h, unsigned level);

void hg_free(hangmanADT h);

// =============================================================================
// hangmanADT.c
// =============================================================================

// shut up clang
#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"
#pragma ide diagnostic ignored "NullDereference"

typedef struct word_node {
  char *word;
  struct word_node *tail;
} word_node;

typedef struct word_list {
  int count;
  struct word_node *data;
} word_list;

typedef struct hangmanCDT {
  unsigned max_level;
  word_list *levels;
} hangmanCDT;

hangmanADT hg_new(unsigned max_level) {
  hangmanADT hg = malloc(sizeof(hangmanCDT));
  hg->max_level = max_level;
  hg->levels = calloc(max_level, sizeof(word_list));

  return hg;
}

static word_node *create_node(char *word, word_node *tail) {
  word_node *node = malloc(sizeof(word_node));
  node->tail = tail;
  node->word = word;
  return node;
}

static word_node *add_word(word_node *list, char *word, int *added) {
  if (!list) {
    *added = 1;
    return create_node(word, NULL);
  }

  int cmp = strcmp(word, list->word);
  if (!cmp) return list;
  if (cmp > 0) {
    *added = 1;
    return create_node(word, list);
  }

  list->tail = add_word(list->tail, word, added);
  return list;
}

int hg_add_words(hangmanADT h, char *words[], unsigned level) {
  if (level > h->max_level) return -1;

  int added_count = 0, i = 0;
  while (words[i]) {
    int added = 0;
    h->levels[level - 1].data = add_word(
      h->levels[level - 1].data,
      words[i++],
      &added
    );
    added_count += added;
  }

  h->levels[level - 1].count += added_count;
  return added_count;
}

int hg_size(const hangmanADT h, unsigned level) {
  if (level > h->max_level) return -1;
  int count = 0;
  word_node *w = h->levels[level - 1].data;
  while (w) {
    count++;
    w = w->tail;
  }

  return count;
}

char *hg_word(const hangmanADT h, unsigned level) {
  if (level > h->max_level) return NULL;

  int idx = random_int(0, h->levels[level - 1].count - 1);
  word_node *w = h->levels[level - 1].data;
  while (idx--) w = w->tail;

  return w->word;
}

char **hg_words(const hangmanADT h, unsigned level) {
  if (level > h->max_level) return NULL;

  char **words = NULL;
  unsigned words_size = 0;
  word_node *w = h->levels[level - 1].data;
  while (w) {
    if (words_size % BLOCK_SIZE == 0) {
      words = realloc(words, (words_size + BLOCK_SIZE) * sizeof(char *));
    }
    words[words_size++] = w->word;
    w = w->tail;
  }
  words = realloc(words, (words_size + 1) * sizeof(char *));
  words[words_size] = NULL;

  return words;
}

void hg_free(hangmanADT h) {
  for (int i = 0; i < h->max_level; i++) {
    word_node *w = h->levels[i].data;
    while (w) {
      word_node *tail = w->tail;
      free(w);
      w = tail;
    }
  }
  free(h->levels);
  free(h);
}

#pragma clang diagnostic pop

// =============================================================================
// test.c
// =============================================================================

int main(void) {
  seed_with_timestamp();

  hangmanADT h = hg_new(3); // Los níveles válidos serán 1, 2 y 3
  assert(hg_size(h, 1) == 0);
  assert(hg_size(h, 4) == -1);
  char *word;
  char **words;

  char *first_words[] = {"ingenieria", "informatica", NULL};
  assert(hg_add_words(h, first_words, 1) == 2);
  assert(hg_size(h, 1) == 2);

  word = hg_word(h, 1);
  assert(!strcmp(word, "ingenieria") || !strcmp(word, "informatica"));

  words = hg_words(h, 1);
  assert(!strcmp(words[0], "ingenieria"));
  assert(!strcmp(words[1], "informatica"));
  assert(words[2] == NULL);
  free(words);

  assert(hg_add_words(h, first_words, 1) == 0);
  assert(hg_add_words(h, first_words, 5) == -1);
  assert(hg_size(h, 5) == -1);
  assert(hg_word(h, 5) == NULL);

  words = hg_words(h, 5);
  assert(words == NULL);
  free(words);
  words = hg_words(h, 2);
  assert(words[0] == NULL);
  free(words);

  char *secondWords[] = {"programacion", NULL};
  assert(hg_add_words(h, secondWords, 3) == 1);
  assert(hg_size(h, 3) == 1);
  word = hg_word(h, 3);
  assert(!strcmp(word, "programacion"));

  words = hg_words(h, 3);
  assert(!strcmp(words[0], "programacion"));
  assert(words[1] == NULL);
  free(words);

  // Ejemplo que muestra cómo se copian las palabras en el TAD
  char v[20] = "cazador";
  char *third_words[] = {v, NULL};

  assert(hg_add_words(h, third_words, 2) == 1);
  printf("%s\n", hg_word(h, 2)); // -> Imprime "cazador"
  strcpy(v, "venado");
  printf("%s\n", hg_word(h, 2)); // -> Imprime "venado"

  char *last_words[] = {"cazador", "colador", NULL};
  assert(hg_add_words(h, last_words, 2) == 2);

  puts("OK");
  hg_free(h);
  return 0;
}
