#ifndef _movetofront__h
#define _movetofront__h

typedef struct moveToFrontCDT *moveToFrontADT;

typedef struct {
  int code;
  char name[20];
} mtf_elem_t;

/*
** Retorna 0 si los elementos son iguales, negativo si e1 es "menor" que e2 y positivo
** si e1 es "mayor" que e2
*/
typedef int (*mtf_comp_fn)(mtf_elem_t e1, mtf_elem_t e2);

/* Retorna un nuevo conjunto de elementos genéricos. Al inicio está vacío */
moveToFrontADT mtf_new(mtf_comp_fn cmp);

/* Libera toda la memoria reservada por el TAD */
void mtf_free(moveToFrontADT mtf);

/* Inserta un elemento si no está. Lo inserta al final.
** Retorna 1 si lo agregó, 0 si no.
*/
unsigned int mtf_add(moveToFrontADT mtf, mtf_elem_t value);

/* Retorna la cantidad de elementos que hay en la colección */
unsigned int mtf_size(moveToFrontADT mtf);

/* Se ubica al principio del conjunto, para poder iterar sobre el mismo */
void mtf_to_begin(moveToFrontADT mtf);

/* Retorna 1 si hay un elemento siguiente en el iterador, 0 si no */
int mtf_has_next(moveToFrontADT mtf);

/* Retorna el siguiente elemento. Si no hay siguiente elemento, aborta */
mtf_elem_t mtf_next(moveToFrontADT mtf);

/* Retorna una copia del elemento. Si no existe retorna NULL.
** Para saber si el elemento está, usa la función compare.
** Si el elemento estaba lo ubica al principio.
 */
mtf_elem_t *mtf_get(moveToFrontADT mtf, mtf_elem_t value);

#endif
