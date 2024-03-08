#include <stdio.h>

int main() {
  unsigned char var, var1, var2, var3, var4;
  var = 0xd8;
  var1 = (var & 0xc0) >> 6;
  var2 = (var & 0x30) >> 4;
  var3 = (var & 0x0c) >> 2;
  var4 = (var & 0x03);

  printf("%x %x %x %x\n", var1, var2, var3, var4);

  return 0;
}