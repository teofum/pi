#include <stdio.h>

int main(void) {
  float lower = 0.0;
  float upper = 300.0;
  float step = 20.0;

  printf("Fahrenheit | Celsius\n"
         "-----------|--------\n");

  float fahrenheit = lower, celsius;
  while (fahrenheit <= upper) {
    celsius = (5.0 / 9.0) * (fahrenheit - 32.0);
    printf("%10.0f | %7.1f\n", fahrenheit, celsius);
    fahrenheit += step;
  }

  return 0;
}
