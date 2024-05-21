#include <stdio.h>
#include <assert.h>

#include <complexADT.h>

#define EPS 0.01

int main(void) {
  complexADT comp1 = comp_new(1, 2); // comp1 = 1 + 2i
  complexADT comp2 = comp_new(2, -3); // comp2 = 2 - 3i
  complexADT ans;

  ans = comp_add(comp1, comp2);
  assert(real(ans) - 3 < EPS && imag(ans) + 1 < EPS);
  comp_free(ans);

  ans = comp_sub(comp1, comp2);
  assert(real(ans) - 1 < EPS && imag(ans) - 5 < EPS);
  comp_free(ans);

  ans = comp_mul(comp1, comp2);
  assert(real(ans) - 8 < EPS && imag(ans) - 1 < EPS);
  comp_free(ans);

  ans = comp_div(comp1, comp2);
  assert(real(ans) + 0.31 < EPS && imag(ans) - 0.54 < EPS);
  comp_free(ans);

  ans = comp_conj(comp1);
  assert(real(ans) - 1 < EPS && imag(ans) + 2 < EPS);

  comp_free(comp1);
  comp_free(comp2);
  comp_free(ans);

  printf("OK!\n");
}
