#include <ctype.h>
#include <stdio.h>

#include "my_getnum.h"
#include "random.h"

#define N 20
#define MAX_LIVES 6
#define BLANK '_'

#define caselesscmp(a, b) (tolower(a) == tolower(b))

int play(const char *secret, char *revealed, int *lives);

char read_guess(void);

int check_char(const char *secret, char *revealed, int *lives, char guess);

void draw_hangman(int lives);

int main(void) {
  char *words[N] = {
    "wood",
    "discussion",
    "motion",
    "jeans",
    "wrench",
    "edge",
    "current",
    "mass",
    "oil",
    "jellyfish",
    "needle",
    "moon",
    "kitty",
    "fold",
    "size",
    "throat",
    "birds",
    "nation",
    "toys",
    "rate"
  };

  int exit = 0, lives;
  char *secret;
  seed_with_timestamp();

  while (!exit) {
    secret = words[random_int(0, N - 1)];
    char *revealed = malloc((strlen(secret) + 1) * sizeof(char));
    int i;
    for (i = 0; secret[i] != '\0'; i++)
      revealed[i] = BLANK;
    revealed[i] = '\0';

    lives = MAX_LIVES;

    int win = play(secret, revealed, &lives);
    if (win) {
      printf("Congratulations! You win\n");
    } else {
      printf("You're dead! Better luck next time\n");
    }

    free(revealed);
    exit = !get_yes_no("Play again? (y/n) ");
  }

  return 0;
}

int play(const char *secret, char *revealed, int *lives) {
  int win = 0;
  while (!win && (*lives) > 0) {
    draw_hangman(*lives);
    printf("%s\n", revealed);

    char guess = read_guess();
    win = check_char(secret, revealed, lives, guess);
  }

  draw_hangman(*lives);
  printf("%s\n", revealed);

  return win;
}

char read_guess(void) {
  char c = 0;
  while (!isalpha(c)) {
    printf("Enter a letter: ");
    c = getchar();
    while (getchar() != '\n');
  }

  return c;
}

int check_char(const char *secret, char *revealed, int *lives, char guess) {
  int match = 0, missing = 0;
  for (int i = 0; secret[i] != '\0'; i++) {
    if (caselesscmp(secret[i], guess)) {
      match++;
      revealed[i] = secret[i];
    }
    if (revealed[i] == BLANK) missing++;
  }

  if (!match) (*lives)--;
  return !missing;
}

void draw_hangman(int lives) {
  printf(
    " ╔══╤\n"
    " ║  %c \n"
    " ║ %c%c%c\n"
    " ║ %c %c\n"
    " ║\n"
    "██████\n",
    lives > 5 ? ' ' : 'O',
    lives > 3 ? ' ' : '/',
    lives > 4 ? ' ' : '|',
    lives > 2 ? ' ' : '\\',
    lives > 1 ? ' ' : '/',
    lives > 0 ? ' ' : '\\'
  );
}
