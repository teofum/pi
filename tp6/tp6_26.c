#include <assert.h>
#include <stdio.h>
#include <string.h>

/**
 * Inserts s2 into s1 (overwriting s1) at the first ocurrence of c
 * Assumes s1 is long enough, for safe usage s1 should have capacity for
 * its own length + length of s2.
 */
void insert_from(char *s1, const char *s2, char c);

int main(void) {
  char str1[60] = "manuel";
  char str2[] = "javi";
  insert_from(str1, str2, 'n');
  assert(strcmp(str1, "majavi") == 0);

  char str3[20];
  strcpy(str3, "manuel");
  insert_from(str3, "javi", 'l');
  assert(strcmp(str3, "manuejavi") == 0); // muestra manuejavi

  char str4[60];
  strcpy(str4, "lalala");
  insert_from(str4, "javi", 'j');
  assert(strcmp("lalala", str4) == 0);

  insert_from(str4, "javier ibaniez de toledo", 'l');
  assert(strcmp("javier ibaniez de toledo", str4) == 0);

  strcpy(str4, "12345");
  insert_from(str4, "6789abcdefgh", '5');
  assert(strcmp("12346789abcdefgh", str4) == 0);

  puts("OK!");
  return 0;
}

void insert_from(char *s1, const char *s2, char c) {
  char i;
  int cursor = 0;
  while ((i = s1[cursor]) != '\0') {
    if (i == c) {
      int s1_pos = cursor;
      cursor = 0;
      do {
        i = s2[cursor];
        s1[cursor + s1_pos] = i;
        cursor++;
      } while (i != '\0');
    }
    cursor++;
  }
}
