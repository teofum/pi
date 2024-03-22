#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ERROR 0
#define SUCCESS 1
#define VOWEL_COUNT 5

#define isvowel(c)                                                             \
  ((c) == 'a' || (c) == 'e' || (c) == 'i' || (c) == 'o' || (c) == 'u')

int remove_vowels(char *s, int m[][VOWEL_COUNT], unsigned int n);

int main(void) {
  int m[6][VOWEL_COUNT];
  char s[] = "las buenas ideas escasean, si";

  assert(remove_vowels(s, m, 6) == SUCCESS);
  assert(strcmp(s, "ls bns ds scsn, s") == 0);
  assert(m[0][0] == 1);
  assert(m[1][0] == 8);
  assert(m[2][0] == 14);
  assert(m[3][0] == 20);
  assert(m[4][0] == 23);
  assert(m[5][0] == -1);

  assert(m[0][1] == 6);
  assert(m[1][1] == 13);
  assert(m[2][1] == 17);
  assert(m[3][1] == 22);
  assert(m[4][1] == -1);

  assert(m[0][2] == 11);
  assert(m[1][2] == 28);
  assert(m[2][2] == -1);

  assert(m[0][3] == -1);

  assert(m[0][4] == 5);
  assert(m[1][4] == -1);

  strcpy(s, "las buenas ideas escasean, si");
  assert(remove_vowels(s, m, 1) == ERROR);
  assert(strcmp(s, "las buenas ideas escasean, si") == 0);
  assert(m[0][0] == -1);
  assert(m[0][1] == -1);
  assert(m[0][2] == -1);
  assert(m[0][3] == -1);
  assert(m[0][4] == -1);

  assert(remove_vowels(s, m, 5) == ERROR);
  assert(strcmp(s, "ls bns ds scsan, s") == 0);
  assert(m[0][0] == 1);
  assert(m[1][0] == 8);
  assert(m[2][0] == 14);
  assert(m[3][0] == 20);
  assert(m[4][0] == -1);

  assert(m[0][1] == 6);
  assert(m[1][1] == 13);
  assert(m[2][1] == 17);
  assert(m[3][1] == 22);
  assert(m[4][1] == -1);

  assert(m[0][2] == 11);
  assert(m[1][2] == 28);
  assert(m[2][2] == -1);

  assert(m[0][3] == -1);

  assert(m[0][4] == 5);
  assert(m[1][4] == -1);

  printf("OK!\n");
  return 0;
}

int remove_vowels(char *s, int m[][VOWEL_COUNT], unsigned int n) {
  int cursor = 0, input_cursor = 0, removed[VOWEL_COUNT] = {0}, m_full = 0;
  char c;
  while ((c = getchar) != '\0' && !m_full) {
  }

  return m_full ? ERROR : SUCCESS;
}
