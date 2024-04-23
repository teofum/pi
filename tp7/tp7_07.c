#include <stdio.h>
#include <string.h>

#include "my_getnum.h"
#include "random.h"
#include "utils.h"

#define N 10

void shuffle(int vec[], int size);

void gen_random_array(char *vec, uint x);

uchar read_difficulty(void);

void read_guess(char *vec, uint x);

int validate_guess(const char *secret, const char *guess, uint x);

int correct_digits(const char *secret, const char *guess, uint x);

int semi_correct_digits(const char *secret, const char *guess, uint x);

int index_of(const char *vec, uint len, char n);

int main(void) {
  seed_with_timestamp();

  int x;
  do {
    x = get_int("Enter # of digits (1-10): ");
  } while (x < 1 || x > 10);

  char *secret = malloc(x * sizeof(char)), *guess = malloc(x * sizeof(char));
  gen_random_array(secret, x);

  uchar guesses = read_difficulty();
  int won = 0;
  while (!won && (guesses--) > 0) {
    read_guess(guess, x);
    won = validate_guess(secret, guess, x);
  }

  if (won) {
    printf("Congratulations! You win\n");
  } else {
    char secret_str[x + 1];
    strncpy(secret_str, secret, x);
    secret_str[x] = '\0';

    printf("Sorry! The secret number was %s\n", secret_str);
  }

  free(secret);
  free(guess);
  return 0;
}

void shuffle(int vec[], int size) {
  int j;
  for (int i = 0; i < size; i++) {
    j = random_int(0, size - 1);
    swap_int(&vec[i], &vec[j]);
  }
}

void gen_random_array(char *vec, uint x) {
  int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle(digits, 10);

  for (int i = 0; i < x; i++) {
    vec[i] = (char) (digits[i] + '0');
  }
}

uchar read_difficulty(void) {
  int i;
  do {
    i = get_int("Enter difficulty level (1-%d): ", N);
  } while (i < 1 || i > N);

  return N + 1 - i;
}

void read_guess(char *vec, uint x) {
  char fmt[10];
  sprintf(fmt, "%%%d[0-9]", x);
  char input[x + 1];

  while (scanf(fmt, input) != 1) {
    flush_stdin();
  }

  for (int i = 0; i < x; i++) {
    vec[i] = input[i];
  }
}

int validate_guess(const char *secret, const char *guess, uint x) {
  int correct = correct_digits(secret, guess, x);
  int semi_correct = semi_correct_digits(secret, guess, x);

  printf("%d correct, %d in wrong place\n", correct, semi_correct);

  return correct == x;
}

int correct_digits(const char *secret, const char *guess, uint x) {
  int hits = 0;
  for (int i = 0; i < x; i++) {
    hits += secret[i] == guess[i];
  }

  return hits;
}

int semi_correct_digits(const char *secret, const char *guess, uint x) {
  int hits = 0;
  for (int i = 0; i < x; i++) {
    int idx = index_of(secret, x, guess[i]);
    hits += idx != -1 && idx != i;
  }

  return hits;
}

int index_of(const char *vec, uint len, char n) {
  for (int i = 0; i < len; i++) {
    if (vec[i] == n) return i;
  }

  return -1;
}
