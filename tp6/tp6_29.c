#include <assert.h>
#include <stdio.h>
#include <string.h>

void delete_chars(char *s1, char *s2);

int main(void) {
  char s3[] = "abc";
  char s4[] = "axc123456789012345678901234567890";
  delete_chars(s3, s4);
  assert(strcmp(s3, "b") == 0);
  assert(strcmp(s4, "x123456789012345678901234567890") == 0);

  char s1[] = "Hola, soy un string";
  char s2[] = "Yo soy otro string";

  delete_chars(s1, s2);
  assert(strcmp(s1, "Hla, sy un string") == 0);
  assert(strcmp(s2, "Y soy tro string") == 0);

  char empty[] = "";
  delete_chars(s1, empty);
  assert(strcmp(s1, "Hla, sy un string") == 0);
  assert(strcmp(empty, "") == 0);

  strcpy(s1, "ABCDE");
  strcpy(s2, "abcde");
  delete_chars(s1, s2);
  assert(strcmp(s1, "ABCDE") == 0);
  assert(strcmp(s2, "abcde") == 0);

  delete_chars(s1, s1);
  assert(strcmp(s1, "") == 0);

  char s5[] = "abc";
  char s6[] = "axc123456789012345678901234567890";
  delete_chars(s5, s6);
  assert(strcmp(s5, "b") == 0);
  assert(strcmp(s6, "x123456789012345678901234567890") == 0);

  puts("OK!");
  return 0;
}

void remove_char(char *s, int idx) {
  int cursor = idx + 1;
  char c;
  do {
    s[cursor - 1] = c = s[cursor];
    cursor++;
  } while (c != '\0');
}

void delete_chars(char *s1, char *s2) {
  int cursor = 0;
  char c1, c2;
  while ((c1 = s1[cursor]) != '\0' && (c2 = s2[cursor]) != '\0') {
    if (c1 == c2) {
      remove_char(s1, cursor);
      remove_char(s2, cursor);
    } else {
      cursor++;
    }
  }
}
