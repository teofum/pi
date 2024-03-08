#include <stdio.h>

int main(void) {
  // "3" + "4";
  printf("%x\n", '3' + '4');
  printf("%x\n", 3 + 4);
  printf("%x\n", '3' + 4);
  printf("%x\n", 3 + '4');
  printf("%x\n", "3" + '4');
  printf("%x\n", "3" + 4);

  return 0;
}