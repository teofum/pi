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
  int cursor = 0, ws_start = -1, ws_span = -1;
  char c;
  do {
    c = str[cursor];

    if (c == ' ') {
      if (ws_start == -1) {
        ws_start = cursor;
        ws_span = 1;
      } else {
        ws_span++;
      }
    } else {
      if (ws_span > 1) {
        // end of a span of more than one space
        // shift everything right of the cursor (ws_span - 1) spaces to the left
        do {
          c = str[cursor];
          str[cursor - ws_span + 1] = str[cursor];
          cursor++;
        } while (c != '\0');

        // reset the cursor and span variables
        cursor = ws_start + 1;
        c = str[cursor];
      }
      ws_start = -1;
      ws_span = -1;
    }

    cursor++;
  } while (c != '\0');

  printf("\"%s\"\n", str);
}
