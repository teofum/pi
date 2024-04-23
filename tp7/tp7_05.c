#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX 5

typedef char *str_array[MAX];

void split_classes(
  const str_array students,
  const char *classes,
  str_array classG,
  str_array classH
);

int main(void) {
  str_array students = {"Juan", "Pedro", "Martin", ""}, classG, classH;
  char class[MAX] = {'H', 'G', 'H', 0};
  split_classes(students, class, classG, classH);

  assert(!strcmp(classG[0], students[1]));
  assert(!strcmp(classH[0], students[0]));
  assert(!strcmp(classH[1], students[2]));
  assert(!strcmp(classG[1], students[3]) && !strcmp(classH[2], students[3]));

  students[0] = "";
  class[0] = 0;
  split_classes(students, class, classG, classH);
  assert(!strcmp(classG[0], students[0]) && !strcmp(classH[0], students[0]));

  puts("OK!");
  return 0;
}

void split_classes(
  const str_array students,
  const char *classes,
  str_array classG,
  str_array classH
) {
  int i = 0, g = 0, h = 0;

  while (students[i][0] != '\0' && classes[i] != '\0') {
    if (classes[i] == 'G') {
      classG[g++] = students[i];
    } else {
      classH[h++] = students[i];
    }

    i++;
  }
  
  classG[g] = classH[h] = "";
}
