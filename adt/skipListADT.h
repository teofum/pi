#ifndef _skipListADT_h
#define _skipListADT_h

#include <limits.h>

#include "utils.h"

typedef int sk_elem_t;
#define sk_min_value INT_MIN
#define sk_max_value INT_MAX

typedef int (*sk_comp_fn)(sk_elem_t, sk_elem_t);

typedef struct skipListCDT *skipListADT;

/**
 *
 * @param max_level máxima altura del vector de "tails". Si es 1 es equivalente a una lista lineal
 * @return
 */
skipListADT sk_new(uchar max_level, sk_comp_fn cmp);

/**
 * Inserta un nuevo elemento en forma ordenada. Acepta repetidos
 * @param list
 * @param key
 */
void sk_insert(skipListADT list, sk_elem_t key);

int sk_search(skipListADT list, sk_elem_t key);

void sk_begin(skipListADT list);

int sk_has_next(const skipListADT list);

/**
 * Si no hay un elemento siguiente asigna ENODATA a errno y retorna un valor incierto
 * @param list
 * @return
 */
sk_elem_t sk_next(skipListADT list);

/**
 * Libera todos los recursos de la lista
 * @param list
 */
void sk_free(skipListADT list);

/**
 * Unicamente para testing, para verificar las alturas.
 * Muestra las distintas "listas" de acuerdo a la altura, asumiendo que elemType es int
 * SOLO PARA TESTING
 * @param list
 */
void sk_display(skipListADT list);

#endif
