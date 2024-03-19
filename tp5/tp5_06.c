#include <ctype.h>
#include <stdio.h>

enum option { TO_LOWER = 0, TO_UPPER, NEXT_CHAR, NEXT_LETTER };

enum option get_option(void);
void print_lower(char c);
void print_upper(char c);
void next_char(char c);
void next_letter(char c);

int main(void) {
  printf("Enter a character: ");
  int c = getchar();

  enum option opt = get_option();
  switch (opt) {
  case TO_LOWER:
    print_lower(c);
    break;
  case TO_UPPER:
    print_upper(c);
    break;
  case NEXT_CHAR:
    next_char(c);
    break;
  case NEXT_LETTER:
    next_letter(c);
    break;
  }

  return 0;
}

enum option get_option(void) {
  printf("Select an option:\n"
         "  1) Convert to lowercase\n"
         "  2) Convert to uppercase\n"
         "  3) Print the next character\n"
         "  4) Print the next letter (wrapped)\n");

  int opt;
  do {
    printf("Enter a number 1-4\n");
    opt = getchar();
  } while (opt < '1' || opt > '4');

  return opt - '1';
}

void print_lower(char c) { printf("%c\n", tolower(c)); }

void print_upper(char c) { printf("%c\n", toupper(c)); }

void next_char(char c) { printf("%c\n", c + 1); }

void next_letter(char c) {
  if (!isalpha(c)) {
    printf("Not a letter!\n");
    return;
  }

  int upper = isupper(c);
  int alpha_value = c - (upper ? 'A' : 'a');
  alpha_value = (alpha_value + 1) % 26;
  printf("%c\n", alpha_value + (upper ? 'A' : 'a'));
}
