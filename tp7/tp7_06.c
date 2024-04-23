#include <stdio.h>
#include <string.h>

#include "my_getnum.h"
#include "random.h"
#include "utils.h"

#define X 5
#define N 10

typedef char num_t[X];

void shuffle(int vec[], int size);

void gen_random_array(num_t vec);

uchar read_difficulty(void);

void read_guess(num_t vec);

int validate_guess(const num_t secret, const num_t guess);

int correct_digits(const num_t secret, const num_t guess);

int semi_correct_digits(const num_t secret, const num_t guess);

int index_of(const num_t vec, char n);

int main(void) {
  seed_with_timestamp();

  num_t secret, guess;
  gen_random_array(secret);

  uchar guesses = read_difficulty();
  int won = 0;
  while (!won && (guesses--) > 0) {
    read_guess(guess);
    won = validate_guess(secret, guess);
  }

  if (won) {
    printf("Congratulations! You win\n");
  } else {
    char secret_str[X + 1];
    strncpy(secret_str, secret, X);
    secret_str[X] = '\0';

    printf("Sorry! The secret number was %s\n", secret_str);
  }

  return 0;
}

void shuffle(int vec[], int size) {
  int j;
  for (int i = 0; i < size; i++) {
    j = random_int(0, size - 1);
    swap(&vec[i], &vec[j]);
  }
}

void gen_random_array(num_t vec) {
  int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  shuffle(digits, 10);

  for (int i = 0; i < X; i++) {
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

void read_guess(num_t vec) {
  char fmt[10];
  sprintf(fmt, "%%%d[0-9]", X);
  char input[X + 1];

  while (scanf(fmt, input) != 1) {
    flush_stdin();
  }

  for (int i = 0; i < X; i++) {
    vec[i] = input[i];
  }
}

int validate_guess(const num_t secret, const num_t guess) {
  int correct = correct_digits(secret, guess);
  int semi_correct = semi_correct_digits(secret, guess);

  printf("%d correct, %d in wrong place\n", correct, semi_correct);

  return correct == X;
}

int correct_digits(const num_t secret, const num_t guess) {
  int hits = 0;
  for (int i = 0; i < X; i++) {
    hits += secret[i] == guess[i];
  }

  return hits;
}

int semi_correct_digits(const num_t secret, const num_t guess) {
  int hits = 0;
  for (int i = 0; i < X; i++) {
    int idx = index_of(secret, guess[i]);
    hits += idx != -1 && idx != i;
  }

  return hits;
}

int index_of(const num_t vec, char n) {
  for (int i = 0; i < X; i++) {
    if (vec[i] == n) return i;
  }

  return -1;
}
