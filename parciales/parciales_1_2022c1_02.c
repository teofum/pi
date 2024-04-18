#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define islowervowel(c)                                                        \
  ((c) == 'a' || (c) == 'e' || (c) == 'i' || (c) == 'o' || (c) == 'u')
#define isvowel(c) islowervowel(tolower(c))
#define isconsonant(c) (isalpha(c) && !isvowel(c))

void rm_vowels(char *str);
int has_adj_consonant(char *str, int i);

int main(void) {
  char str[30] = "hola mundo";
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "hola a todo el mundo");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "xyz");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "aholoaaa");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "aa eo iu oa uo");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "pa po pi po pu");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "aeiou");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  strcpy(str, "a,e,i,o,u");
  printf("%s -> ", str);
  rm_vowels(str);
  printf("%s\n", str);

  return 0;
}

void rm_vowels(char *str) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    // if a vowel has at least one adjacent consonant, remove (skip) it
    if (isvowel(str[i]) && has_adj_consonant(str, i)) {
      i++;
    } else {
      // otherwise it's a "loose" vowel or not a vowel, keep it
      str[j++] = str[i++];
    }
  }

  str[j] = '\0'; // append null-terminator
}

int has_adj_consonant(char *str, int i) {
  // no need to bounds-check next letter, if str[i] is the last letter str[i+1]
  // will be \0 which is obviously not a letter and the check will work fine
  // we do need to check the case where i = 0 for the previous letter to avoid
  // going out of bounds
  return (isconsonant(str[i + 1]) || (i > 0 && isconsonant(str[i - 1])));
}
