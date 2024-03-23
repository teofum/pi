#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int exp_notation(const char *s, char *out);

int main(void) {
  char s[100];

  assert(exp_notation("1.1.1", s) == 0);
  assert(exp_notation("a", s) == 0);
  assert(exp_notation("1.a11", s) == 0);
  assert(exp_notation("1-1", s) == 0);
  puts("Test 1 OK!");

  assert(exp_notation("1", s));
  assert(strcmp(s, "1E+00") == 0);
  assert(exp_notation("0012", s));
  assert(strcmp(s, "1.2E+01") == 0);
  puts("Test 2 OK!");

  assert(exp_notation("145.720", s));
  assert(strcmp(s, "1.4572E+02") == 0);
  assert(exp_notation("134597", s));
  assert(strcmp(s, "1.34597E+05") == 0);
  puts("Test 3 OK!");

  assert(exp_notation("0.34", s));
  assert(strcmp(s, "3.4E-01") == 0);
  assert(exp_notation("0.00200", s));
  assert(strcmp(s, "2E-03") == 0);
  assert(exp_notation("987654321011", s));
  assert(strcmp(s, "9.87654321011E+11") == 0);
  puts("Test 4 OK!");

  puts("OK!");
  return 0;
}

int exp_notation(const char *s, char *out) {
  int exp = -1, cur_in = 0, cur_out = 0;
  char c;

  // Handle integer part
  int in_number = 0;
  while ((c = s[cur_in++]) != '\0' && c != '.') {
    if (!isdigit(c)) {
      out[0] = '\0'; // Put empty string in out
      return 0;      // Error out of the function
    }

    in_number = in_number || c != '0';
    if (in_number) { // Ignore leading zeroes
      // Print out '.' after first significant digit
      if (cur_out == 1)
        out[cur_out++] = '.';

      out[cur_out++] = c; // Print out digit
      exp++;
    }
  }

  if (c == '.') {
    // Handle decimal part
    int zero_span = 0;
    while ((c = s[cur_in++]) != '\0') {
      if (!isdigit(c)) {
        out[0] = '\0'; // Put empty string in out
        return 0;      // Error out of the function
      }

      in_number = in_number || c != '0';
      if (!in_number) { // Handle leading zeroes in decimal place
        exp--;
      } else if (c == '0') {
        // When we find zeroes, buffer them
        // This lets us ignore trailing zeroes
        zero_span++;
      } else {
        // Print out '.' after first significant digit
        if (cur_out == 1)
          out[cur_out++] = '.';

        // If there are any buffered zeroes, print them out
        while (zero_span > 0) {
          out[cur_out++] = '0';
          zero_span--;
        }

        out[cur_out++] = c; // Print out digit
      }
    }
  }

  sprintf(out + cur_out, "E%+03d", exp); // Add exponent and null-terminate str
  printf("%s\n", out);
  return 1;
}
