#include <stdio.h>
#include <string.h>

void insert_from(char str1[], const char str2[], char c);

int main(void) {
  char str1[20] = "manuel";
  insert_from(str1, "javi", 'n');
  printf("%s\n", str1);

  char str2[20] = "manuel";
  insert_from(str2, "javi", 'l');
  printf("%s\n", str2);

  char str3[20] = "manuel";
  insert_from(str3, "javi", 'j');
  printf("%s\n", str3);

#ifdef SEGFAULT

  char str4[20] = "manuel";

  // Almost guaranteed to segfault (overflows program memory)
  char long_str[10000];
  memset(long_str, 'A', 10000);
  long_str[9999] = '\0';

  insert_from(str4, long_str, 'l');
  printf("%s\n", str4);

#endif

  return 0;
}

void insert_from(char str1[], const char str2[], char c) {
  int i = 0;
  char end;

  // Skip until we find c, or str1 ends
  while ((end = str1[i]) != '\0' && end != c)
    i++;

  // Found c, insert str2 at this point
  if (end == c) {
    int j = 0;
    do {
      str1[i++] = str2[j];
    } while (str2[j++] != '\0');
  }
  // If end is '\0' str1 ended without containing c, do nothing
}
