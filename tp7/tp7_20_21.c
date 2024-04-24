#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **passed(char **students, const int *grades);

void delete_student_list(char **students);

int main(void) {
  char *students[4] = {"Juan", "Pedro", "Martin", ""};
  int grades[] = {1, 4, 10, 2, 10, 11};

  char **pass = passed(students, grades);
  if (pass == NULL) {
    printf("Out of memory!\n");
    return 1;
  }
  assert(
    !strcmp(students[1], pass[0]) &&
    !strcmp(students[2], pass[1]) &&
    !strcmp(students[3], pass[2])
  );

  puts("OK!");
  delete_student_list(pass);
  return 0;
}

char **passed(char **students, const int *grades) {
  size_t size = 10;
  char **res = malloc(size * sizeof(char *));
  if (!res) return NULL;

  int i = 0, j = 0;
  for (; students[i][0] != 0; i++) {
    if (grades[i] >= 4) {
      if (j == size - 1) {
        size += 10;
        char **aux = realloc(res, size);
        if (!aux) {
          free(res);
          return NULL;
        }
        res = aux;
      }

      res[j] = malloc(strlen(students[i]) + 1);
      if (!res[j]) return NULL;

      strcpy(res[j], students[i]);
      j++;
    }
  }
  res[j] = malloc(1);
  if (!res[j]) return NULL;

  res[j][0] = 0;

  return res;
}

void delete_student_list(char **students) {
  int i;
  for (i = 0; students[i][0] != 0; i++)
    free(students[i]);
  free(students[i]);

  free(students);
}
