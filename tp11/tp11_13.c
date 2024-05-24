#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <rankingADT.h>

// Utilizamos char * como elemType y strcmp como compare
int main(void) {
  rankingADT r = rank_new(NULL, 0, strcmp);
  rank_add(r, "Footloose");
  rank_add(r, "Footloose");  // no hace nada
  rank_add(r, "Footloose");  // no hace nada
  rank_add(r, "Yesterday");
  rank_add(r, "La bamba");
  rank_add(r, "Sucio y desprolijo");
  rank_add(r, "Ride of the Valkyries");
  rank_add(r, "Yesterday");
  rank_add(r, "Ride of the Valkyries");

  const char *aux = "default";
  int n;
  n = rank_get_by_ranking(r, 6, &aux);
  assert(n == 0 && !strcmp(aux, "default"));

  n = rank_get_by_ranking(r, 1, &aux);
  assert(n == 1 && !strcmp(aux, "Yesterday"));

  n = rank_get_by_ranking(r, 0, &aux);
  assert(n == 0 && !strcmp(aux, "Yesterday"));

  n = rank_get_by_ranking(r, 2, &aux);
  assert(n == 1 && !strcmp(aux, "Footloose"));

  n = rank_get_by_ranking(r, 1, &aux);
  assert(n == 1 && !strcmp(aux, "Footloose"));

  assert(rank_contains(r, "Ride of the Valkyries"));
  assert(rank_contains(r, "Sucio y desprolijo"));
  assert(rank_contains(r, "Desarma y sangra") == 0);

  size_t dimTop = 10;
  const char **top = rank_get_top(r, &dimTop);
  assert(dimTop == 5 && !strcmp(top[0], "Footloose") &&
         !strcmp(top[1], "Yesterday"));
  assert(!strcmp(top[2], "Ride of the Valkyries") &&
         !strcmp(top[3], "Sucio y desprolijo"));
  assert(strcmp(top[4], "La bamba") == 0);
  free(top);

  rank_down(r, 1);
  dimTop = 2;
  top = rank_get_top(r, &dimTop);
  assert(dimTop == 2 && !strcmp(top[0], "Yesterday") &&
         !strcmp(top[1], "Footloose"));

  free(top);
  rank_free(r);

  // Creamos un ranking con miles de elementos
  int qty = 5000;
  char *songs[qty];

  for (int i = 0; i < qty; i++) {
    songs[i] = malloc(100);
    sprintf(songs[i], "Cancion %04d", i + 1);
  }
  r = rank_new(songs, qty, strcmp);
  assert(rank_size(r) == qty);

  assert(rank_get_pos(r, "Cancion 0001") == 1);
  assert(rank_get_pos(r, "Cancion 4500") == 4500);

  assert(rank_contains(r, "Cancion 0001"));
  assert(rank_get_pos(r, "Cancion 0001") == 1);
  assert(rank_contains(r, "Cancion 1234"));
  assert(rank_get_pos(r, "Cancion 1234") == 1233);
  assert(rank_get_pos(r, "Cancion 1233") == 1234);
  assert(rank_get_pos(r, "Cancion 5000") == 5000);
  assert(rank_get_pos(r, "Cancion xxx") == 0);
  assert(rank_size(r) == qty);


  for (int i = 0; i < qty; i++) {
    free(songs[i]);
  }
  rank_free(r);

  puts("rankingADT: OK!");
  return 0;
}
