#include <assert.h>
#include <stdio.h>
#include <string.h>

char *my_strncpy(char *dst, const char *src, unsigned int n);
char *my_strncat(char *dst, const char *src, unsigned int n);
int my_strncmp(char *s, char *t, unsigned int n);

int main(void) {
  char s[100];
  for (int i = 0; i < 100; i++)
    s[i] = 'x';
  assert(my_strncpy(s, "prueba copiar", 100) == s);
  assert(strcmp(s, "prueba copiar") == 0);
  for (int i = strlen(s); i < 100; i++)
    assert(s[i] == '\0');

  my_strncpy(s, "", 100);
  for (int i = 0; i < 100; i++)
    assert(s[i] == '\0');

  my_strncpy(s, "123456", 4);
  assert(strcmp(s, "1234") == 0);

  my_strncpy(s, "777777777", 2);
  assert(strcmp(s, "7734") == 0);
  printf("my_strncpy OK!\n");

  assert(my_strncat(s, " end", 10) == s);
  assert(strcmp(s, "7734 end") == 0);

  assert(my_strncat(s, "abcde", 2) == s);
  assert(strcmp(s, "7734 endab") == 0);
  printf("my_strncat OK!\n");

  assert(my_strncmp(s, "7734 endab", 10) == 0);
  assert(my_strncmp(s, "7734 endab", 12) == 0);
  assert(my_strncmp(s, "7734", 4) == 0);
  assert(my_strncmp(s, "7735", 4) < 0);
  assert(my_strncmp(s, "7732", 4) > 0);
  assert(my_strncmp(s, "7734", 0) == 0);
  assert(my_strncmp(s, "", 4) > 0);
  assert(my_strncmp(s, "", 0) == 0);

  printf("my_strncmp OK!\n");
  return 0;
}

char *my_strncpy(char *dst, const char *src, unsigned int n) {
  int src_end = 0;
  char c;
  for (int i = 0; i < n; i++) {
    if (!src_end && (c = src[i]) == '\0')
      src_end = 1;

    dst[i] = src_end ? '\0' : c;
  }

  return dst;
}

char *my_strncat(char *dst, const char *src, unsigned int n) {
  char *dst_end = dst + strlen(dst);
  int cursor = 0;
  char c;
  while (cursor < n && (c = src[cursor]) != '\0')
    dst_end[cursor++] = c;

  dst_end[cursor] = '\0';
  return dst;
}

int my_strncmp(char *s, char *t, unsigned int n) {
  for (int i = 0; i < n && (s[i] != '\0' || t[i] != '\0'); i++) {
    int d = s[i] - t[i];
    if (d != 0)
      return d;
  }

  return 0;
}
