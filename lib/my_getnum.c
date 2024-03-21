#include "my_getnum.h"

// Checks the buffer to ensure there is only whitespace after parsed value
static int check_buffer(void) {
  int c, flag = 1;
  while ((c = getchar()) != '\n') {
    if (!isspace(c)) {
      flag = 0;
    }
  }

  return flag;
}

int get_int(const char prompt[], ...) {
  int n, end = 0;
  va_list args; // Variable arguments

  do {
    // Prints the prompt with format
    va_start(args, prompt);
    vprintf(prompt, args);
    va_end(args);

    // scanf returns the # of arguments successfully parsed
    // In this case we only need one
    if (scanf("%d", &n) != 1) {
      // Parsed a number, skip the rest of the line
      while (getchar() != '\n')
        ;
    } else {
      end = check_buffer();
    }

    if (!end) {
      puts("\nInvalid input");
    }
  } while (!end);
  return n;
}

long get_long(const char prompt[], ...) {
  long n;
  int end = 0;
  va_list args; // Variable arguments

  do {
    // Prints the prompt with format
    va_start(args, prompt);
    vprintf(prompt, args);
    va_end(args);

    // scanf returns the # of arguments successfully parsed
    // In this case we only need one
    if (scanf("%ld", &n) != 1) {
      // Parsed a number, skip the rest of the line
      while (getchar() != '\n')
        ;
    } else {
      end = check_buffer();
    }

    if (!end) {
      puts("\nInvalid input");
    }
  } while (!end);
  return n;
}

float get_float(const char prompt[], ...) {
  float n;
  int end = 0;
  va_list args; // Variable arguments

  do {
    // Prints the prompt with format
    va_start(args, prompt);
    vprintf(prompt, args);
    va_end(args);

    // scanf returns the # of arguments successfully parsed
    // In this case we only need one
    if (scanf("%g", &n) != 1) {
      // Parsed a number, skip the rest of the line
      while (getchar() != '\n')
        ;
    } else {
      end = check_buffer();
    }

    if (!end) {
      puts("\nInvalid input");
    }
  } while (!end);
  return n;
}

double get_double(const char prompt[], ...) {
  double n;
  int end = 0;
  va_list args; // Variable arguments

  do {
    // Prints the prompt with format
    va_start(args, prompt);
    vprintf(prompt, args);
    va_end(args);

    // scanf returns the # of arguments successfully parsed
    // In this case we only need one
    if (scanf("%lg", &n) != 1) {
      // Parsed a number, skip the rest of the line
      while (getchar() != '\n')
        ;
    } else {
      end = check_buffer();
    }

    if (!end) {
      puts("\nInvalid input");
    }
  } while (!end);
  return n;
}

int get_yes_no(const char prompt[], ...) {
  int input, end = 0;
  va_list args; // Variable arguments

  do {
    // Prints the prompt with format
    va_start(args, prompt);
    vprintf(prompt, args);
    va_end(args);

    input = getchar();
    if (!strchr("YySsNn", input)) {
      printf("\nInvalid input\n");
      if (input != '\n') {
        while (getchar() != '\n')
          ;
      }
    } else {
      end = 1;
    }
  } while (!end);

  while (getchar() != '\n')
    ;

  return strchr("SsYy", input) != 0;
}
