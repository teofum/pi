#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define lowercmp(a, b) (tolower(a) == tolower(b))

int compress(char *str, char c, int reps[]);

int main(void) {
  int reps[100];
  char s[] = "AAA aaaabbaa a b aaaa capital federal";
  int dim;

  dim = compress(s, 'a', reps);
  assert(strcmp(s, "A abba a b a capital federal") == 0);
  assert(dim == 8);
  assert(reps[0] == 2); // se eliminan 2 de "AAA"
  assert(reps[1] == 3); // se eliminan 3 de "aaaa"
  assert(reps[2] == 1);
  assert(reps[3] == 0);
  assert(reps[4] == 3);
  assert(reps[5] == 0);
  assert(reps[6] == 0);
  assert(reps[7] == 0);

  dim = compress(s, 'x', reps);
  assert(strcmp(s, "A abba a b a capital federal") == 0);
  assert(dim == 0);

  char t[] = "AAAaaaa aAaA";
  dim = compress(t, 'a', reps);
  assert(strcmp(t, "A a") == 0); // Se deja la primer aparición
  assert(dim == 2);
  assert(reps[0] == 6);
  assert(reps[1] == 3);

  printf("OK!\n");
  return 0;
}

int compress(char *str, char c, int reps[]) {
  int i = 0, j = 0, k = -1;

  while (str[i] != '\0') {
    if (lowercmp(str[i], c)) {
      if (i == 0 || !lowercmp(str[i - 1], c)) {
        // first c in sequence
        reps[++k] = 0;
        str[j++] = str[i];
      } else {
        // not first in sequence, skip
        reps[k]++;
      }
    } else {
      str[j++] = str[i];
    }

    i++;
  }

  str[j] = '\0';

  return ++k;
}
