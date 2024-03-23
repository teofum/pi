#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#define isvowel(c)                                                             \
  ((c) == 'a' || (c) == 'e' || (c) == 'i' || (c) == 'o' || (c) == 'u')

int is_accented(int syllable_count, int accented_syllable, char last_letter);
int count_accents(const char *str);

int main(void) {
  char s[] = "|El ca-|fe |del me-|nu |tie-ne |mal |gus-to";
  assert(2 == count_accents(s));

  char s2[] = "Da-|mian com-|pro |es-te |ar-bol";
  assert(3 == count_accents(s2));

  char s3[] = "";
  assert(0 == count_accents(s3));

  char s4[] = " ";
  assert(0 == count_accents(s4));

  assert(0 == count_accents(""));
  assert(0 == count_accents("A-pro-|ba-mos |el e-|xa-men"));
  assert(0 == count_accents("A-pro-|ba-mos |el e-|xa-men   "));

  puts("OK!");
  return 0;
}

int is_accented(int syllable_count, int accented_syllable, char last_letter) {
  int accented_from_last = syllable_count - accented_syllable;
  switch (accented_from_last) {
  case 0:
    // Aguda
    return last_letter == 'n' || last_letter == 's' || isvowel(last_letter);
  case 1:
    // Grave
    return last_letter != 'n' && last_letter != 's' && !isvowel(last_letter);
  default:
    // Esdrújula o sobreesdrújula
    return 1;
  }
}

int count_accents(const char *str) {
  int cursor = 0, accented_words = 0;
  char c;

  int syllable_count = 1, accented_syllable = 1;
  char last_letter = '\0';
  do {
    switch ((c = str[cursor++])) {
    case ' ':
    case '\0': {
      // End of word, check if it should be accented
      if (is_accented(syllable_count, accented_syllable, last_letter))
        accented_words++;

      // Reset variables
      syllable_count = accented_syllable = 1;
      last_letter = '\0';
      break;
    }
    case '|': {
      accented_syllable = syllable_count;
      break;
    }
    case '-': {
      syllable_count++;
      break;
    }
    default: {
      last_letter = tolower(c);
      break;
    }
    }
  } while (c != '\0');

  return accented_words;
}
