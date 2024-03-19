#include <ctype.h>
#include <math.h>
#include <stdio.h>

int main(void) {
  for (int i = 46; i <= 'H'; i++) {
    printf("%d %c %c\t", i, i, tolower(i));
    printf("%s ", isalnum(i) ? "si" : "no");
    printf("%s ", isalpha(i) ? "si" : "no");
    printf("%s ", isdigit(i) ? "si" : "no");
    printf("%s ", islower(i) ? "si" : "no");
    printf("%s ", isupper(i) ? "si" : "no");
    printf("%s ", isxdigit(i) ? "si" : "no");
    printf("%s ", iscntrl(i) ? "si" : "no");
    printf("%s \n", ispunct(i) ? "si" : "no");
  }

  for (float x = -1; x < 2; x += 0.5) {
    printf("%f  %f   %f   %f\n", x, fabs(x), ceil(x), floor(x));
    printf("%f  %f\n", pow(x, 2), pow(x, .5));
  }

  return 0;
}
