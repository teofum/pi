#include <stdio.h>

#define MAX_LENGTH 25 // Most English words are not over 25 letters long

#ifdef VERTICAL
#define HISTOGRAM_SIZE 24
#else
#define HISTOGRAM_SIZE 60
#endif

#define SPACE ' '
#define TAB '\t'

enum state { OUT = 0, IN };

int main(void) {
  int c, word_length = 0;
  enum state state = OUT;

  int words_of_length[MAX_LENGTH];
  for (int i = 0; i < MAX_LENGTH; i++) {
    words_of_length[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if ((c == SPACE || c == TAB || c == '\n') && state == IN) {
      if (word_length > 0 && word_length <= 25) {
        words_of_length[word_length - 1] += 1;
      }

      state = OUT;
      word_length = 0;
    } else {
      if (state == OUT)
        state = IN;

      word_length++;
    }
  }

  int max = 0;
  int max_length = 0;
  for (int i = 0; i < MAX_LENGTH; i++) {
    if (words_of_length[i] > max)
      max = words_of_length[i];
    if (words_of_length[i] > 0)
      max_length = i;
  }

#ifdef VERTICAL

  int bar_size[MAX_LENGTH];
  for (int i = 0; i < MAX_LENGTH; i++) {
    bar_size[i] = words_of_length[i] * HISTOGRAM_SIZE / max;
  }

  for (int i = HISTOGRAM_SIZE; i > 0; i--) {
    for (int j = 0; j <= max_length; j++)
      printf("%s ", i <= bar_size[j] ? "###" : "   ");
    putchar('\n');
  }

  for (int j = 0; j <= max_length; j++)
    printf("----");
  putchar('\n');

  for (int j = 0; j <= max_length; j++)
    printf("%-3d ", j + 1);
  putchar('\n');

  for (int j = 0; j <= max_length; j++)
    printf("%-3d ", words_of_length[j]);
  putchar('\n');

#else

  for (int i = 0; i <= max_length; i++) {
    printf("%2d |", i + 1);

    int bar_size = words_of_length[i] * HISTOGRAM_SIZE / max;
    for (int j = 0; j < HISTOGRAM_SIZE; j++) {
      putchar(j < bar_size ? '#' : ' ');
    }

    printf(" (%4d)\n", words_of_length[i]);
  }

#endif

  return 0;
}
