#include <stdio.h>

#include "random.h"
#include "utils.h"

#define N 20
#define MIN_R 5
#define STEP 5
#define ITERATIONS 1000

typedef struct {
  uint r;
  double t;
  double ratio;
} result;

void simulate(result *res);

void simulate_once(result *res);

int main(void) {
  seed_with_timestamp();
  
  result results[N];

  printf(" Radius |  Time  | Ratio  \n");
  for (int i = 0; i < N; i++) {
    results[i].r = MIN_R + i * STEP;
    simulate(&results[i]);
    printf(
      " %6d | %6.0f | %6.2f \n",
      results[i].r,
      results[i].t,
      results[i].ratio
    );
  }

  return 0;
}

void simulate(result *res) {
  res->t = 0.0;
  for (int i = 0; i < ITERATIONS; i++)
    simulate_once(res);

  res->t /= ITERATIONS;
  res->ratio = res->r / res->t;
}

void simulate_once(result *res) {
  uint rr = res->r * res->r;

  int x = 0, y = 0, t = 0;

  while (x * x + y * y < rr) {
    int step = random_int(0, 3);
    int *p = (step & 2) ? &x : &y;
    (*p) += (step & 1) ? 1 : -1;

    t++;
  }

  res->t += t;
  res->ratio = res->r / res->t;
}
