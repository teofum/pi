#include <stdio.h>

#include "utils.h"

void read_radix(uint *in, uint *out);
uint read_num(uint radix);
uint convert(uint n, uint in_radix, uint out_radix);

int main(void) {
  uint in_radix, out_radix;
  read_radix(&in_radix, &out_radix);

  uint in = read_num(in_radix);
  uint res = convert(in, in_radix, out_radix);

  printf("%d\n", res);
  return 0;
}

void read_radix(uint *in, uint *out) {
  *in = *out = 0;

  int n = 0;
  do {
    n = scanf("< %u > %u", in, out);
    flush_stdin();
  } while (n != 2 || *in < 2 || *in > 10 || *out < 2 || *out > 10);
}

uint read_num(uint radix) {
  char buf[256];
  char fmt[10];
  sprintf(fmt, "%%[0-%d]", radix - 1);

  int n = 0;
  do {
    n = scanf(fmt, buf);
  } while (n != 1);

  uint in;
  sscanf(buf, "%u", &in);

  return in;
}

uint convert(uint n, uint in_radix, uint out_radix) {
  uint power = 1, num = 0, res = 0;

  while (n > 0) {
    uint d = n % 10;
    num += d * power;

    power *= in_radix;
    n /= 10;
  }

  power = 1;
  while (num > 0) {
    uint d = num % out_radix;
    res += d * power;

    power *= 10;
    num /= out_radix;
  }

  return res;
}
