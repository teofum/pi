#include <assert.h>
#include <stdio.h>
#include <string.h>

int strend(const char *s1, const char *s2);

int main(void) {
  assert(strend("", "") == 1);
  assert(strend("something", "") == 1);
  assert(strend("something", "thing") == 1);
  assert(strend("something", "something") == 1);
  assert(strend("something", "plus something") == 0);
  assert(strend("not at the eeeeeend", " end") == 0);
  assert(strend("not at the eeeeeennnnnd", "end") == 0);
  assert(strend("", "s") == 0);
  assert(strend("ssss", "sss") == 1);
  assert(strend("ssss", "sssss") == 0);
  puts("OK!");
  return 0;
}

int strend(const char *s1, const char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);

  int d = len1 - len2, cursor = 0;
  char c;
  int match = d >= 0;
  while ((c = s1[cursor + d]) != '\0' && match) {
    putchar(c);
    if (s2[cursor++] != c)
      match = 0;
  }
  putchar('\n');

  return match;
}
