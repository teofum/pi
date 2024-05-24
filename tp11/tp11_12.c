#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <socialADT.h>

int main(void) {
  socialADT soc = social_new();
  char **rel;
  rel = social_get_persons(soc); // rel = {NULL}
  assert(rel[0] == 0);
  free(rel);

  rel = social_get_related(soc, "carlitos"); // rel = {NULL};
  assert(rel[0] == NULL);
  free(rel);

  char aux[30] = "juan";
  social_add_person(soc, aux); // soc contiene a "juan"
  strcpy(aux, "luisa");
  social_add_person(soc, aux); // soc contiene a "juan" y "luisa"
  strcpy(aux, "ana");
  social_add_related(soc, "juan", "pedro");
  social_add_related(soc, "juan", aux);
  social_add_related(soc, "juan", "juana");
  char **juanFriends = social_get_related(
    soc,
    "juan"
  ); // juanFriends es {"ana", "juana", "pedro", NULL};
  assert(!strcmp(juanFriends[0], "ana") && !strcmp(juanFriends[1], "juana"));
  assert(!strcmp(juanFriends[2], "pedro") && juanFriends[3] == NULL);
  for (int i = 0; juanFriends[i] != NULL; i++)
    free(juanFriends[i]);
  free(juanFriends);

  social_add_person(soc, "andres");
  social_add_person(soc, "analia");
  char **p = social_get_persons(soc); // p={"analia","andres","juan","luisa",NULL}
  assert(!strcmp(p[0], "analia") && !strcmp(p[1], "andres"));
  assert(!strcmp(p[2], "juan") && !strcmp(p[3], "luisa") && p[4] == NULL);
  for (int i = 0; p[i] != NULL; i++)
    free(p[i]);
  free(p);

  social_add_related(
    soc,
    "juan",
    "john"
  ); // Ahora los amigos de juan son "ana", "john", "juana" y "pedro"
  social_add_related(
    soc,
    "juan",
    "john"
  ); // Ahora los amigos de juan son "ana", "john", "john", juana" y "pedro"
  juanFriends = social_get_related(soc, "juan");
  assert(!strcmp(juanFriends[0], "ana") && !strcmp(juanFriends[1], "john") &&
         !strcmp(juanFriends[2], "john"));
  assert(!strcmp(juanFriends[3], "juana") && !strcmp(juanFriends[4], "pedro") &&
         juanFriends[5] == NULL);
  for (int i = 0; juanFriends[i] != NULL; i++)
    free(juanFriends[i]);
  free(juanFriends);

  social_free(soc);
  puts("OK!");

  // El enunciado decía que a lo sumo eran 20 chars lo que tenía cada nombre
  // Pero si el TAD aplica programación defensiva no debería causar problemas el pasarle un
  // nombre de mayor longitud, a lo sumo podría cortarlo.
  soc = social_new();
  social_add_person(soc, "012345678901234567890123456789");
  p = social_get_persons(soc);
  assert(!strncmp(p[0], "01234567890123456789", 20));
  for (int i = 0; p[i] != NULL; i++)
    free(p[i]);
  free(p);
  social_free(soc);

  puts("Great!");
  return 0;
}
