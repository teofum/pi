#include <stdio.h>

int main(void) {
  int age = 25;
  float length = 185.654;
  char letter = 'Z';

  printf("%-5d\n", age);
  printf("%010d\n", age);
  printf("%-10.2f\n", length);
  printf("%8d\n", letter);

  return 0;
}