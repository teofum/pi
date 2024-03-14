#include <stdio.h>

int main(void) {
  float lower = 0.0;
  float upper = 300.0;
  float step = 20.0;

  printf("Celsius | Fahrenheit\n"
         "--------|-----------\n");

  float celsius = lower, fahrenheit;
  while (celsius <= upper) {
    fahrenheit = (9.0 / 5.0) * celsius + 32.0;
    printf("%7.0f | %10.0f\n", celsius, fahrenheit);
    celsius += step;
  }

  return 0;
}
