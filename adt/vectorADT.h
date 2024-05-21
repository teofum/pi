#ifndef _vectorADT_h
#define _vectorADT_h

#include <stddef.h>

typedef struct vectorCDT *vectorADT;

typedef int vec_elem_t;

typedef int (*vec_comp_fn)(vec_elem_t a, vec_elem_t b);

/* Crea un nuevo vector dinámico de elementos genéricos
** Inicialmente el vector está vacío
** Cada elemento a insertar será de tipo elemType
** Si no se pudo crear retorna NULL.
** La función compare retorna negativo si source es "menor" que target,
** positivo si source es "mayor""que target o cero si se los considera iguales
** (la misma convención que strcmp)
*/
vectorADT vec_new(vec_comp_fn comp);

/* Libera todos los recursos reservados por el TAD */
void vec_free(vectorADT v);

/* Almacena los elementos de elems a partir de la posición index, donde elems es
un vector de dim elementos.
** En caso de ser necesario agranda el vector.
** El resto de los elementos del vector no se modifican y permanecen en la misma
posición.
** Si se recibe NULL o no se pudo insertar retorna cero.
** Si alguna posición está ocupada, la deja como estaba.
** Retorna cuántos elementos pudo almacenar.
** Ejemplo:
** si v tiene ocupadas las posiciones 1,3 y 6
** se invoca con index=2, dim=5
** el vector actual quedará con los mismos elementos en las posiciones 1, 3 y 6
** pero además v[2]=elems[0], v[4]=elems[2], v[5]=elems[3]
** y la función retorna 3
*/
size_t vec_put(vectorADT v, const vec_elem_t *elems, size_t dim, size_t index);

/* Retorna el índice en el cual está insertado el elemento, o -1 si no lo
encuentra */
int vec_get_idx(vectorADT v, vec_elem_t elem);

/* Elimina el elemento en la posición index. Si index está fuera del vector no
hace nada */
void vec_delete(vectorADT v, size_t index);

/* Retorna cuántos elementos hay insertados en el vector */
size_t vec_elem_count(vectorADT v);

#endif
