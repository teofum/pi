#ifndef _complexADT_h
#define _complexADT_h

typedef struct complexCDT *complexADT;

complexADT comp_new(double real, double imag);

void comp_free(complexADT c);

complexADT comp_add(complexADT lhs, complexADT rhs);

complexADT comp_sub(complexADT lhs, complexADT rhs);

complexADT comp_mul(complexADT lhs, complexADT rhs);

complexADT comp_div(complexADT lhs, complexADT rhs);

complexADT comp_conj(complexADT c);

double real(complexADT c);

double imag(complexADT c);

#endif
