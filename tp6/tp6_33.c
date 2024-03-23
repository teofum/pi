#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "random.h"

#define MAX 100
#define ALPHABET_LENGTH ('Z' - 'A')

// Shuffle an array in place
void shuffle(char *vec, int size);

void create_cipher(char *cipher);
void encode(const char *msg, const char *cipher, char *out);
void decode(const char *msg, const char *cipher, char *out);

int main(void) {
  char msg[MAX];
  char dest[MAX];

  seed_with_timestamp();

  // Debemos probar con mayusculas, porque siempre decodifica a mayuscuas
  char *s = "MENSAJE A CODIFICAR";
  char *s2 = "Mensaje a codificar";
  char alpha[MAX];
  create_cipher(alpha);
  encode(s, alpha, msg);
  assert(strlen(s) == strlen(msg));
  assert(strcmp(s, msg) != 0);
  decode(msg, alpha, dest);
  assert(strcmp(dest, s) == 0);

  encode(s2, alpha, msg);
  assert(strlen(s2) == strlen(msg));
  assert(strcmp(s2, msg) != 0);
  decode(msg, alpha, dest);
  assert(strcmp(dest, s) == 0);

  puts("OK");
  return 0;
}

void shuffle(char *vec, int size) {
  int j;
  for (int i = 0; i < size; i++) {
    j = random_int(0, size);
    char tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
  }
}

void create_cipher(char *cipher) {
  for (int i = 0; i <= ALPHABET_LENGTH; i++) {
    cipher[i] = i + 'A';
  }
  shuffle(cipher, ALPHABET_LENGTH);
}

void encode(const char *msg, const char *cipher, char *out) {
  int cur = 0;
  char c;
  do {
    c = msg[cur];
    out[cur++] = isalpha(c) ? (cipher[toupper(c) - 'A']) : c;
  } while (c != '\0');

  printf("\"%s\" -> \"%s\"\n", msg, out);
}

void decode(const char *msg, const char *cipher, char *out) {
  int cur = 0;
  char c;
  do {
    c = msg[cur];
    if (isupper(c)) { // Encoded letters are always uppercase
      int letter_idx = 0;
      while (letter_idx <= ALPHABET_LENGTH && cipher[letter_idx] != c)
        letter_idx++;

      out[cur++] = letter_idx + 'A';
    } else {
      out[cur++] = c;
    }
  } while (c != '\0');

  printf("\"%s\" -> \"%s\"\n", msg, out);
}
