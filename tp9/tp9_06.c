#include <assert.h>
#include <stdio.h>
#include <string.h>

int palindrome(const char *str);

int palindrome_impl(const char *str, size_t len);

int main(void) {
  assert(palindrome("a") == 1);
  assert(palindrome("") == 1);
  assert(palindrome("neuquen") == 1);
  assert(palindrome("abba") == 1);
  assert(palindrome("12345654321") == 1);

  assert(palindrome("abab") == 0);
  assert(palindrome("123456") == 0);

  printf("OK!\n");
  return 0;
}

int palindrome(const char *str) {
  return palindrome_impl(str, strlen(str));
}

int palindrome_impl(const char *str, size_t len) {
  if (len <= 1) return 1;
  return str[0] == str[len - 1] && palindrome_impl(str + 1, len - 2);
}
