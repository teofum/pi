#include <stdio.h>
#include <string.h>
#include <assert.h>

const char *strrchr_rec(const char *s, char c);

int main(void) {
  char *s = "vamos a buscar";

  for (int i = 0; s[i]; i++) {
    assert(strrchr(s, s[i]) == strrchr_rec(s, s[i]));
  }

  puts("OK!");
}

const char *strrchr_rec(const char *s, char c) {
  const char *res = (*s == c) ? s : NULL;

  if (*s == '\0') return res;

  const char *next = strrchr_rec(s + 1, c);
  return (next == NULL) ? res : next;
}
