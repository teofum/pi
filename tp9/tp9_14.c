#include <stdio.h>
#include <assert.h>

int paired(const char *str);

int main(void) {
  assert(paired("") == 0);
  assert(paired("()") == 0);
  assert(paired("(())()(()())") == 0);
  assert(paired("((((()))))") == 0);

  assert(paired("(") != 0);
  assert(paired(")") != 0);
  assert(paired(")(") != 0);
  assert(paired("())") != 0);
  assert(paired("()(") != 0);
  assert(paired("((()))())(") != 0);

  printf("OK!\n");
  return 0;
}

int paired(const char *str) {
  if (*str == 0) return 0;

  int next = paired(str + 1);
  if (next > 0) return next;
  return next + (*str == '(' ? 1 : (*str == ')' ? -1 : 0));
}
