#include <stdio.h>
#include <assert.h>
#include <string.h>

const char *strpbrk_rec(const char *s, const char *c);

int main(void) {
  char *s = "abcde";
  char *t = "abcdeab";

  assert(strpbrk(s, "") == strpbrk_rec(s, ""));
  assert(strpbrk(s, "a") == strpbrk_rec(s, "a"));
  assert(strpbrk(s, "xa") == strpbrk_rec(s, "xa"));
  assert(strpbrk(s, "xye") == strpbrk_rec(s, "xye"));
  assert(strpbrk(s, "r") == strpbrk_rec(s, "r"));
  assert(strpbrk(t, "ba") == t);
  assert(strpbrk_rec(t, "ba") == t);

  puts("OK");
  return 0;
}

const char *strpbrk_rec(const char *s, const char *c) {
  if (*s == '\0') return NULL;

  const char *res = strchr(c, *s) ? s : NULL;

  const char *next = strpbrk_rec(s + 1, c);
  return (res != NULL) ? res : next;
}
