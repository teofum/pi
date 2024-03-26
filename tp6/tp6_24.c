#include <assert.h>
#include <stdio.h>
#include <string.h>

void collapse_whitespace(char str[]);

int main(void) {
  char s[60] = "   ";
  collapse_whitespace(s);
  assert(strcmp(s, " ") == 0);
  printf("Test 1 OK!\n");

  collapse_whitespace(s);
  assert(strcmp(s, " ") == 0);
  printf("Test 2 OK!\n");

  strcpy(s, "  ");
  collapse_whitespace(s);
  assert(strcmp(s, " ") == 0);
  printf("Test 3 OK!\n");

  strcpy(s, " . . .  ");
  collapse_whitespace(s);
  assert(strcmp(s, " . . . ") == 0);
  printf("Test 4 OK!\n");

  strcpy(s, "");
  collapse_whitespace(s);
  assert(strcmp(s, "") == 0);
  printf("Test 5 OK!\n");

  strcpy(s, "sinblancos");
  collapse_whitespace(s);
  assert(strcmp(s, "sinblancos") == 0);
  printf("Test 6 OK!\n");

  printf("All OK!\n");
  return 0;
}

void collapse_whitespace(char str[]) {
  int i = 0, j = 0;
  char c;
  do {
    c = str[i];
    if (i == 0 || c != ' ' || str[i - 1] != ' ')
      str[j++] = c;

    i++;
  } while (c != '\0');
}
