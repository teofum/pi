#include <stdio.h>
#include <assert.h>
#include <string.h>

void reverse(char *s, char *t);

int main(void) {
  char s[20] = {0};

  reverse("1234567890", s);
  assert(strcmp(s, "0987654321") == 0);

  memset(s, 0, 20);
  reverse("", s);
  assert(strcmp(s, "") == 0);

  memset(s, 0, 20);
  reverse("a", s);
  assert(strcmp(s, "a") == 0);

  memset(s, 0, 20);
  reverse("ab", s);
  assert(strcmp(s, "ba") == 0);

  memset(s, 0, 20);
  reverse("abc", s);
  assert(strcmp(s, "cba") == 0);

  printf("OK!\n");
  return 0;
}

// slow and awful!
void reverse(char *s, char *t) {
  if (s[0] != '\0') {
    t[strlen(s) - 1] = s[0];
    reverse(s + 1, t);
  }
}
