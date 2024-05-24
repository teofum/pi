#include <ctype.h>
#include <stdio.h>

int main(void) {
  int lower = 0, upper = 0, non_letter = 0;
  int letters['Z' - 'A' + 1] = {0};

  int c;
  while ((c = getchar()) != EOF) {
    if (islower(c)) {
      lower++;
      letters[toupper(c) - 'A']++;
    } else if (isupper(c)) {
      upper++;
      letters[c - 'A']++;
    } else {
      non_letter++;
    }
  }

  printf("Text rank_contains:\n");
  printf(
    "%d letters (%d lowercase, %d uppercase)\n", lower + upper, lower, upper
  );
  printf("%d non-alphabetic characters\n", non_letter);
  printf("\nLetters in the text:\n");
  for (int i = 'A'; i <= 'Z'; i++) {
    if (letters[i - 'A'] > 0) {
      printf("%c - %3d\n", i, letters[i - 'A']);
    }
  }

  return 0;
}
