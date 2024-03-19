#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STEP 0.001
#define EPSILON 1e-12
#define sign(x) (((x) < 0) ? -1 : 1)

void eval(double (*f)(double), double min, double max);

double f(double x);
double g(double x);
double h(double x);

int main(void) {
  printf("sin(x)\n");
  eval(sin, -10, 10);
  printf("\ncos(x)\n");
  eval(cos, -10, 10);
  printf("\nf(x) = 2^x * x^3\n");
  eval(f, -10, 10);
  printf("\ng(x) = sin(x) + ln(x)\n");
  eval(g, 0, 10);
  printf("\nh(x) = sqrt(x) + e^x\n");
  eval(h, 0, 10);

  return 0;
}

void eval(double (*f)(double), double min, double max) {
  if (min > max) {
    double tmp = min;
    min = max;
    max = tmp;
  }

  double last_eval = 0;
  for (double x = min; x <= max; x += STEP) {
    double eval = f(x);

    if (fabs(eval) < EPSILON) {
      eval = 0;
      printf("x = %.3f\n", eval);
    } else if (last_eval != 0 && sign(eval) != sign(last_eval)) {
      printf("%.3f < x < %.3f\n", x - STEP, x);
    }

    last_eval = eval;
  }
}

double f(double x) { return pow(2, x) * pow(x, 3); }
double g(double x) { return sin(x) + log(x); }
double h(double x) { return sqrt(x) + exp(x); }
