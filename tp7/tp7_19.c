#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

char *copy_prefix(const char *s, uint n);

int main(void) {
  char *corto = "Corto";
  char *largo = "La Constitución de la Nacion Argentina, que rige actualmente a la República Argentina, fue aprobada por una asamblea constituyente integrada por representantes de trece provincias, hecha en la ciudad de Santa Fe en el año 1853. Los diferentes textos de esta Constitución han sido reformados varias veces, siendo la última llevada a cabo en 1994, y han sido dejados sin efecto o modificados por autoridades de facto en nueve oportunidades. El propósito de la Constitución de 1853 fue poner fin al ciclo de las guerras civiles y sentar las bases de la Organización Nacional, objetivos que tardaron unas décadas mas en cumplirse. Antes de esta aprobación hubo varios intentos (en 1819 y 1826) que fueron rechazados por diversos motivos. El texto constitucional consta de un preámbulo y dos partes normativas:";

  char *aux;
  aux = copy_prefix(largo, 0);
  assert(!strcmp("", aux));
  free(aux);

  aux = copy_prefix(corto, 120);
  assert(!strcmp("Corto", aux));
  free(aux);

  aux = copy_prefix(largo, 2);
  assert(!strcmp("La", aux));
  free(aux);

  aux = copy_prefix(corto, 0);
  assert(!strcmp("", aux));
  free(aux);

  puts("OK!");
  return 0;
}

char *copy_prefix(const char *s, uint n) {
  char *prefix = malloc(n + 1);
  int i;
  for (i = 0; s[i] != 0 && i < n; i++)
    prefix[i] = s[i];
  prefix[i] = 0;

  return prefix;
}
