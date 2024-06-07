#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <bibleADT.h>

int
main(void) {
  bibleADT b = new_bible();
  assert(get_verse(b, 1, 1) == NULL);
  char aux[2000];
  strcpy(aux, "En el principio creo Dios los cielos y la tierra.");
  assert(add_verse(b, 1, 1, aux) == 1);
  strcpy(aux, "Y atardecio y amanecio: dia tercero.");
  assert(add_verse(b, 1, 13, aux) == 1);
  assert(add_verse(b, 1, 13, "Amaos los unos a los otros") == 0); // Ya estaba
  strcpy(aux,
         "los contados de la tribu de Dan fueron sesenta y dos mil setecientos.");
  assert(add_verse(b, 4, 39, aux) == 1);
  assert(add_verse(
    b,
    4,
    46,
    "fueron todos los contados seiscientos tres mil quinientos cincuenta."
  ) == 1);
  const char *v = get_verse(b, 4, 45);
  assert(v == NULL);
  v = get_verse(b, 4, 39);
  assert(strncmp(v, "los con", 7) == 0);
  free(v);

  free_bible(b);
  puts("Aleluya !");
  return 0;
}
