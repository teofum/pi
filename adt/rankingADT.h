#ifndef _rankingADT_h
#define _rankingADT_h

#include <stddef.h>

typedef const char *rank_elem_t;   // cambiar al tipo deseado

typedef struct rankingCDT *rankingADT;

typedef int (*rank_comp_fn)(rank_elem_t source, rank_elem_t target);

/* Crea un nuevo ranking. Recibe un vector con elementos, donde el primer
** elemento (elems[0]) está al tope del ranking (puesto 1), elems[1] en el
** puesto 2, etc. Si dim es cero significa que no hay elementos iniciales
*/
rankingADT rank_new(rank_elem_t elems[], size_t dim, rank_comp_fn cmp);

/* Agrega un elemento en la posición más baja del ranking, si no estaba.
** Si el elemento estaba, es equivalente a accederlo, por lo que sube un
** puesto en el ranking
*/
void rank_add(rankingADT ranking, rank_elem_t elem);

/* La cantidad de elementos en el ranking */
size_t rank_size(const rankingADT ranking);

/* Si n es una posición válida del ranking, guarda en elem el elemento que está
** en el puesto n y retorna 1.
** Si no hay elemento en la posición n, retorna cero y no modifica *elem
** Este acceso también hace que el elemento suba un puesto en el ranking
*/
int rank_get_by_ranking(rankingADT ranking, size_t n, rank_elem_t *elem);

/* top: entrada/salida
** Recibe cuántos elementos al tope del ranking se desean
** Almacena cuántos pudo guardar (ver ejemplos)
** Si el ranking está vacío *top queda en cero y retorna NULL
*/
rank_elem_t *rank_get_top(const rankingADT ranking, size_t *top);

/* 1 si el elemento consultado está en el ranking, cero si no
** Este acceso también hace que el elemento suba un puesto en el ranking
*/
int rank_contains(rankingADT ranking, rank_elem_t elem);

/* Baja una posición en el ranking para el elemento que está en la posición n */
void rank_down(rankingADT ranking, size_t n);

void rank_free(rankingADT r);

/* Retorna la posición en el ranking (1 es el tope) o 0 si no está en el ranking */
int rank_get_pos(const rankingADT r, rank_elem_t elem);

#endif
