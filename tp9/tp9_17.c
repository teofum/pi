#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int well_formed(char *s);

int main(void) {
  char *zero[] = {"abcd4a10bb2", "", "0000", "a1", "abc3", "0a1"};

  char *not_zero[] = {"a", "1", "a2", "abc2", "abc4", "abc33", "0123", "2aa",
                      "$1", "@@2", "abcd22", "@@"};

  for (int i = 0; i < sizeof(zero) / sizeof(zero[0]); i++) {
    printf("%s\n", zero[i]);
    assert(well_formed(zero[i]) == 0);
  }

  for (int i = 0; i < sizeof(not_zero) / sizeof(not_zero[0]); i++) {
    printf("%s\n", not_zero[i]);
    assert(well_formed(not_zero[i]) != 0);
  }

  puts("OK!");
  return 0;
}

int well_formed(char *s) {
  if (*s == '\0') return 0;

  int next = well_formed(s + 1);
  if (next < 0) return next;
  if (isdigit(*s)) {
    if (next > 0) return -1;
    return next + ((*s) - '0');
  }
  if (isalpha(*s)) return next - 1;
  return -1;
}
