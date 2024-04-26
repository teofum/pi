#include <stdio.h>
#include <assert.h>

int balance(const char *str);

int main(void) {
  assert(balance("") == 0);
  assert(balance("((()))") == 0);
  assert(balance(")(") == 0);
  assert(balance("()()") == 0);
  assert(balance(")))(((") == 0);
  assert(balance("))) ((( ))( ()() ()()(") == 0);

  assert(balance(")") != 0);
  assert(balance("(") != 0);
  assert(balance(")()") != 0);
  assert(balance(" ) ") != 0);
  assert(
    balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))") != 0);
  assert(
    balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))((((((((((((") !=
    0);

  printf("OK!\n");
  return 0;
}

int balance(const char *str) {
  if (*str == 0) return 0;
  return balance(str + 1) + (*str == '(' ? 1 : (*str == ')' ? -1 : 0));
}
