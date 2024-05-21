#include <stdlib.h>

#include "complexADT.h"

typedef struct complexCDT {
  double real, imag;
} complexCDT;

complexADT comp_new(double real, double imag) {
  complexADT c = malloc(sizeof(complexCDT));
  c->real = real;
  c->imag = imag;
  return c;
}

void comp_free(complexADT c) {
  free(c);
}

complexADT comp_add(complexADT lhs, complexADT rhs) {
  return comp_new(lhs->real + rhs->real, lhs->imag + rhs->imag);
}

complexADT comp_sub(complexADT lhs, complexADT rhs) {
  return comp_new(lhs->real - rhs->real, lhs->imag - rhs->imag);
}

complexADT comp_mul(complexADT lhs, complexADT rhs) {
  return comp_new(
    lhs->real * rhs->real - lhs->imag * rhs->imag,
    lhs->imag * rhs->real + lhs->real * rhs->imag
  );
}

complexADT comp_div(complexADT lhs, complexADT rhs) {
  double den = rhs->imag * rhs->imag + rhs->real * rhs->real;

  return comp_new(
    (lhs->real * rhs->real + lhs->imag * rhs->imag) / den,
    (lhs->imag * rhs->real - lhs->real * rhs->imag) / den
  );
}

complexADT comp_conj(complexADT c) {
  return comp_new(c->real, -c->imag);
}

double real(complexADT c) {
  return c->real;
}

double imag(complexADT c) {
  return c->imag;
}
