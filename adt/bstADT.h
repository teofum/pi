#ifndef _bstADT_h_
#define _bstADT_h_

typedef int bst_elem_t;

typedef int (*bst_comp_fn)(bst_elem_t elem1, bst_elem_t elem2);

typedef struct bstCDT *bstADT;

// Crea un arbol binario de busqueda
bstADT bst_new(bst_comp_fn comp);

// Libera toda la memoria reservada por el TAD
void bst_free(bstADT bst);

// Cantidad de nodos en el arbol
size_t bst_size(const bstADT bst);

// Devuelve la altura del arbol (la longitud de la rama mas larga)
// Un arbol vacio tiene altura 0
size_t bst_height(const bstADT bst);

// Retorna 1 si el elemento estaก en el arbol, cero si no esta
int bst_belongs(const bstADT bst, bst_elem_t elem);

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int bst_insert(bstADT bst, bst_elem_t elem);

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
bst_elem_t *bst_inorder(const bstADT bst);

// TODO: borrar un elemento, recorrido preorder, postorder
// Mas avanzado aun: verificar si es balanceado por altura o no, crear iteradores inorder, preorder, postorder


#endif
