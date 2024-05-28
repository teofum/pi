#include <stdio.h>
#include <assert.h>

#include <squirrelADT.h>

int main(void) {
  // Reserva los recursos para contabilizar las ardillas del parque
  // agrupando las cantidades en bloques (manzanas) de 100 metros x 100 metros.
  // Por ejemplo:
  // - El bloque 0,0 comprende de [0, 100) metros en vertical y de [0, 100) metros en horizontal
  // - El bloque 0,1 comprende de [0, 100) metros en vertical y de [100, 200) metros en horizontal
  // - El bloque 1,0 comprende de [100, 200) metros en vertical y de [0, 100) metros en horizontal
  squirrelCensusADT central_park = squirrel_new(100);

  // Se registra a una ardilla a
  // - 299 metros en línea vertical del extremo superior izquierdo del parque
  // - 120 metros en línea horizontal del extremo superior izquierdo del parque
  // de forma que se contabilizará a la ardilla en el bloque 2,1
  assert(squirrel_count(central_park, 299, 120) == 1);
  // Se registra a otra ardilla en el mismo bloque que la invocación anterior
  assert(squirrel_count(central_park, 201, 140) == 2);

  // Se registra a una ardilla en el bloque 0,0
  assert(squirrel_count(central_park, 15, 98) == 1);

  // Se consulta la cantidad de ardillas del bloque de las primeras dos invocaciones a squirrel_count
  assert(squirrel_in_block(central_park, 250, 150) == 2);
  // Se consulta la cantidad de ardillas del bloque de la tercera invocación a squirrel_count
  assert(squirrel_in_block(central_park, 0, 0) == 1);
  // Se consulta la cantidad de ardillas en un bloque distinto a los dos anteriores, el bloque 29,15
  assert(squirrel_in_block(central_park, 2965, 1540) == 0);

  // Libera los recursos utilizados para contabilizar las ardillas del parque
  squirrel_free(central_park);

  puts("OK!");
  return 0;
}
