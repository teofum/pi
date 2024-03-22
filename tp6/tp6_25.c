#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

uint my_strncpy(
    const char *src,
    char *dst,
    uint start,
    uint end,
    uint dst_size
);

int main(void) {
  char s[100];
  assert(my_strncpy("un texto", s, 0, 0, 1) == 0);
  assert(strcmp(s, "") == 0);
  assert(my_strncpy("un texto", s, 0, 0, 10) == 1);
  assert(strcmp(s, "u") == 0);
  assert(my_strncpy("un texto", s, 0, 10, 1) == 0);
  assert(strcmp(s, "") == 0);

  assert(my_strncpy("un texto", s, 45, 130, 1) == 0);

  assert(my_strncpy("un texto", s, 0, 130, 2) == 1);
  assert(strcmp(s, "u") == 0);

  assert(my_strncpy("un texto", s, 0, 130, 202) == 8);
  assert(strcmp(s, "un texto") == 0);

  assert(my_strncpy("un texto", s, 0, 7, 202) == 8);
  assert(strcmp(s, "un texto") == 0);

  assert(my_strncpy("un texto", s, 0, 7, 9) == 8);
  assert(strcmp(s, "un texto") == 0);

  assert(my_strncpy("un texto", s, 2, 5, 8) == 4);
  assert(strcmp(s, " tex") == 0);

  assert(my_strncpy("un texto", s, 45000, 130000, 10) == 0);

  printf("OK!\n");
  return 0;
}

uint my_strncpy(
    const char *src,
    char *dst,
    uint start,
    uint end,
    uint dst_size
) {
  // sanity check: start index should not be >= src length
  if (start >= strlen(src))
    return 0;

  uint cpy_size = end + 1 - start;
  if ((dst_size - 1) < cpy_size)
    cpy_size = (dst_size - 1); // limit copy length to destination size

  const char *cursor = src + start;
  const char *end_ptr = cursor + cpy_size;
  while (cursor < end_ptr && *cursor != '\0') {
    *(dst++) = *(cursor++);
  }
  *dst = '\0';

  return cursor - start - src;
}
