#include <stdio.h>
#include <assert.h>
#include <strings.h>

#include <bagADT.h>

// Utilizamos char * como elemType y strcasemp como compare

int main(void) {
  bagADT bag = bag_new(strcasecmp);
  assert(bag_insert(bag, "agustina") == 1);
  assert(bag_insert(bag, "Agustina") == 2);
  assert(bag_insert(bag, "belen") == 1);
  assert(bag_insert(bag, "carla") == 1);
  assert(bag_insert(bag, "CARLA") == 2);
  assert(bag_insert(bag, "carla") == 3);
  assert(bag_insert(bag, "daniel") == 1);
  assert(bag_insert(bag, "emilio") == 1);

  assert(bag_count(bag, "carla") == 3);
  assert(bag_count(bag, "agustina") == 2);
  assert(bag_count(bag, "amelia") == 0);
  assert(bag_count(bag, "emilio") == 1);
  assert(bag_count(bag, "daniel") == 1);
  assert(bag_count(bag, "belen") == 1);
  assert(bag_size(bag) == 5);
  assert(strcasecmp(bag_highest(bag), "carla") == 0);

  for (int i = 2; i <= 10001; i++)
    assert(bag_insert(bag, "belen") == i);
  assert(bag_count(bag, "carla") == 3);
  assert(bag_count(bag, "belen") == 10001);
  assert(strcasecmp(bag_highest(bag), "belen") == 0);

  assert(bag_remove(bag, "carla") == 2);
  assert(bag_size(bag) == 5);
  assert(bag_remove(bag, "carla") == 1);
  assert(bag_size(bag) == 5);
  assert(bag_remove(bag, "carla") == 0);
  assert(bag_size(bag) == 4);
  assert(bag_remove(bag, "carla") == 0);


  assert(bag_remove(bag, "un desconocido") == 0);


  bag_free(bag);
  puts("OK!");

  bag = bag_new(strcasecmp);
  puts("Al buscar el más popular de un bag vacío debe abortar");
  bag_highest(bag);
  puts("Si ud. ve esto, entonces no abortó como debería haber hecho");
  return 0;
}
