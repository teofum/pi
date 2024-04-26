#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256

char *read(int *size);

int main(void) {
  int size = 0;
  char *buf = read(&size);

  printf("\n------------------------\n");

  for (int i = 0; i < size; i++)
    putchar(buf[i]);

  free(buf);
  return 0;
}

char *read(int *size) {
  char *buf = NULL;

  int c;
  while ((c = getchar()) != EOF) {
    if (*size % BLOCK_SIZE == 0)
      buf = realloc(buf, *size + BLOCK_SIZE);
    buf[(*size)++] = (char) c;
  }

  buf = realloc(buf, *size);
  return buf;
}
