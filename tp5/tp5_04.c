#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int rand_in_range(int min, int max);

int main(void) {

  int rand = rand_in_range(1, 10);
  assert(rand <= 10 && rand >= 1);
  rand = rand_in_range(-10, -2);
  assert(rand <= -2 && rand >= -10);
  assert(rand_in_range(0, 0) == 0);
  assert(rand_in_range(10, 10) == 10);

  // Solo estamos testeando que caiga dentro del rango, habria que realizar un
  // test mas sofisticado que analizara la desviacion estandar
  for (int i = 0; i < 1000; i++) {
    rand = rand_in_range(-10, 10);
    assert(rand <= 10 && rand >= -10);
  }

  puts("OK!");
  return 0;
}

int rand_in_range(int min, int max) { return rand() % (max + 1 - min) + min; }
