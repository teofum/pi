#ifndef _squirrelADT_h
#define _squirrelADT_h

#include <stdlib.h>

typedef struct squirrelCensusCDT *squirrelCensusADT;

/**
 * Reserva los recursos para el conteo de ardillas en un parque agrupando las cantidades
 * por bloques (manzanas) de tamaño blockSizeMetres metros x blockSizeMetres metros
 * desde el extremo superior izquierdo del parque
 * Si blockSizeMetres es igual a 0 aborta
 */
squirrelCensusADT squirrel_new(size_t block_size);

/**
 * Registra una ardilla en el bloque (manzana) correspondiente al punto (yDistance, xDistance) donde
 * - yDistance es la distancia vertical en metros del extremo superior izquierdo del parque
 * - xDistance es la distancia horizontal en metros del extremo superior izquierdo del parque
 * Retorna cuántas ardillas fueron registradas en ese mismo bloque
 */
size_t squirrel_count(
  squirrelCensusADT squirrels,
  size_t y_dist,
  size_t x_dist
);

/**
 * Retorna cuántas ardillas fueron registradas en el bloque correspondiente al punto (yDistance, xDistance)
 */
size_t squirrel_in_block(
  const squirrelCensusADT squirrels,
  size_t y_dist,
  size_t x_dist
);

/**
 * Libera los recursos utilizados para el conteo de ardillas en un parque
 */
void squirrel_free(squirrelCensusADT squirrels);

#endif
