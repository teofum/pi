#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <setADT.h>

/* Utilizamos char * como elemType y strcmp como compare */
int main(void) {
  setADT set1 = set_new(strcmp);
  setADT set2 = set_new(strcmp);
  setADT ans;

  int ok;
  ok = set_insert(set1, "amelia");
  assert(ok && set_includes(set1, "amelia"));
  ok = set_insert(set1, "amelia");
  assert(ok == 0);
  set_insert(set1, "belen");
  set_insert(set1, "carlos"); // set1 = {"amelia", "belen", "carlos"}
  set_insert(set2, "carlos");
  set_insert(set2, "daniel");
  set_insert(set2, "emilia"); // set2 = {"carlos", "daniel", "emilia"}

  ans = set_union(set1, set2);
  assert(set_includes(ans, "amelia") && set_includes(ans, "daniel"));
  set_free(ans);

  ans = set_intersection(set1, set2);
  assert(set_includes(ans, "carlos") && set_includes(ans, "amelia") == 0);
  set_free(ans);

  ans = set_diff(set1, set2);
  assert(set_includes(ans, "amelia") && set_includes(ans, "carlos") == 0);
  set_free(ans);

  set_remove(set1, "carlos");
  ans = set_intersection(set1, set2);
  assert(set_empty(ans));

  set_free(set1);
  set_free(set2);
  set_free(ans);

  // test con conjuntos de un elemento
  set1 = set_new(strcmp);
  set2 = set_new(strcmp);
  ok = set_insert(set1, "amelia");
  ok = set_insert(set2, "amelia");
  ans = set_intersection(set1, set2);
  assert(set_includes(ans, "amelia") == 1);
  assert(set_size(ans) == 1);
  set_free(ans);

  ans = set_union(set1, set2);
  assert(set_includes(ans, "amelia") == 1);
  assert(set_size(ans) == 1);
  set_free(ans);

  // Diferencia de un conjunto con un solo elemento
  set_free(set2);
  set2 = set_new(strcmp);
  ans = set_diff(set1, set2);
  assert(set_size(ans) == 1);

  set_free(ans);
  set_free(set1);
  set_free(set2);

  puts("OK!");
}
