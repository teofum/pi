#ifndef _phrasesADT_h_
#define _phrasesADT_h_

#include <stddef.h>

typedef struct phrasesCDT *phrasesADT;

/*
* Recibe cuál será el rango de claves válidas a utilizar, por ejemplo si
* keyFrom=1001, keyTo=1500 habrá un máximo de 500 frases a almacenar
* keyFrom=1001, keyTo=3500 habrá un máximo de 2500 frases a almacenar
* Si los parámetros son inválidos retorna NULL
*/
phrasesADT phrases_new(size_t key_from, size_t key_to);

/* Libera toda la memoria reservada por el TAD */
void phrases_free(phrasesADT ph);

/*
* Agrega una frase. Si la clave key es inválida retorna 0, sinó retorna 1 (uno)
* Si ya hay una frase asociada a la clave, actualiza la frase almacenada,
* reemplazándola por el parámetro phrase.
* Se almacena una copia de la frase.
*/
int phrases_put(phrasesADT ph, size_t key, const char *phrase);

/*
* Retorna una copia de la frase asociada a la clave key. Si no hay frase asociada
* a la clave key retorna NULL, lo mismo si la clave es inválida.
*/
char *phrases_get(const phrasesADT ph, size_t key);

/*
* Cantidad de frases almacenadas
*/
size_t phrases_size(const phrasesADT ph);

/*
* Retorna un string con todas las frases concatenadas
* Si no hay frases retorna un string vacío
*/
const char *phrases_concat_all(const phrasesADT ph);

/*
* Retorna un string con todas las frases concatenadas cuyas claves estén entre
* from y to inclusive. Si from o to son inválidas (están fuera del rango)
* retorna NULL
* Si no hay frases en ese rango, retorna un string vacío
*/
const char *phrases_concat(const phrasesADT ph, size_t from, size_t to);

#endif
