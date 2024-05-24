#ifndef _listADT_h
#define _listADT_h

typedef struct listCDT *listADT;

typedef int list_elem_t;    // Tipo de elemento a insertar, por defecto int
typedef int (*list_comp_fn)(list_elem_t e1, list_elem_t e2);

/* Retorna una lista vacía.
** compare retorna 0 si los elementos son iguales, negativo si e1 es "menor" que e2 y
** positivo si e1 es "mayor" que e2
*/
listADT list_new(list_comp_fn comp);

/* Agrega un elemento. Si ya estaba no lo agrega */
void list_add(listADT list, list_elem_t elem);

/* Elimina un elemento. */
void list_remove(listADT list, list_elem_t elem);

/* Resetea el iterador que recorre la lista en el orden de inserción */
void list_to_begin(listADT list);

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en el orden de inserción. Sino retorna 0
*/
int list_has_next(listADT list);

/* Retorna el elemento siguiente del iterador que recorre la lista
** en el orden de inserción.
** Si no hay un elemento siguiente o no se invocó a toBegin aborta la ejecución.
*/
list_elem_t list_next(listADT list);

/* Resetea el iterador que recorre la lista en forma ascendente */
void list_to_begin_asc(listADT list);

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en forma ascendente. Sino retorna 0
*/
int list_has_next_asc(listADT list);

/* Retorna el elemento siguiente del iterador que recorre la lista en forma ascendente.
** Si no hay un elemento siguiente o no se invocó a toBeginAsc aborta la ejecución.
*/
list_elem_t list_next_asc(listADT list);

/* Libera la memoria reservada por la lista */
void list_free(listADT list);

#endif
