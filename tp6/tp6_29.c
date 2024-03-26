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

void delete_chars(char *s1, char *s2) {
  int i = 0, j = 0, end1 = 0, end2 = 0;
  while (!end1 || !end2) {
    if (end1) {
      s2[j++] = s2[i];
    } else if (end2) {
      s1[j++] = s1[i];
    } else if (s1[i] != s2[i]) {
      s1[j] = s1[i];
      s2[j++] = s2[i];
    }

    if (!end1 && s1[i] == '\0') {
      end1 = 1;
      s1[j] = '\0';
    }
    if (!end2 && s2[i] == '\0') {
      end2 = 1;
      s2[j] = '\0';
    }
    i++;
  }
}
