#include <assert.h>
#include <stdio.h>
#include <string.h>

#define PASS_GRADE 6

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"

int get_passed(
  const char *students[],
  size_t size,
  char *passed[],
  const int grades[]
);

static void print_names(const char *names[], size_t n);

int main(void) {
  const char *names[] = {"anita", "pepe", "fabi", "carlos", "tere"};
  char *passed[5];
  int grades[] = {3, 4, 8, 10, 1};
  size_t size, passed_size;
  size = sizeof(names) / sizeof(char *);
  print_names(names, size);
  passed_size = get_passed(names, size, passed, grades);
  printf("Aprobados:\n");
  print_names(passed, passed_size);

  // Test del ejemplo
  char *aprobados1[5];
  assert(get_passed(names, 0, aprobados1, grades) == 0);
  assert(get_passed(names, 1, aprobados1, grades) == 0);
  assert(get_passed(names, 2, aprobados1, grades) == 0);
  assert(get_passed(names, 3, aprobados1, grades) == 1);
  assert(strcmp(aprobados1[0], "fabi") == 0);
  char *aprobados2[5];
  assert(get_passed(names, 4, aprobados2, grades) == 2);
  assert(strcmp(aprobados2[0], "fabi") == 0);
  assert(strcmp(aprobados2[1], "carlos") == 0);
  char *aprobados3[5];
  assert(get_passed(names, 5, aprobados3, grades) == 2);
  assert(strcmp(aprobados3[0], "fabi") == 0);
  assert(strcmp(aprobados3[1], "carlos") == 0);

  printf("\nOK!\n");
  return 0;
}

int get_passed(
  const char *students[],
  size_t size,
  char *passed[],
  const int grades[]
) {
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (grades[i] >= PASS_GRADE)
      passed[j++] = students[i];
  }

  return j;
}

#pragma clang diagnostic pop

static void print_names(const char *names[], size_t n) {
  for (int i = 0; i < n; i++)
    printf("%s ", names[i]);
  putchar('\n');
}
