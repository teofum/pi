#include <ctype.h>
#include <stdio.h>

#include "random.h"

int count_letters(char letter, int limit);

int main(void) {
  seed_with_timestamp();

  int limit = random_int(1, 256);
  char letter = random_int('A', 'Z');
  printf("limit: %d, letter: %c\n", limit, letter);

  int count = count_letters(letter, limit);
  printf("%d\n", count);

  return 0;
}

int count_letters(char letter, int limit) {
  int c, count = 0;
  for (int i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; i++) {
    if (islower(c))
      c = toupper(c);

    if (c == letter)
      count++;
  }

  return count;
}
