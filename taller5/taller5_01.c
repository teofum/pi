#include <stdio.h>

int month_length[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int leap(int y);

int add_day(int *d, int *m, int *y);
void add_and_print(int *d, int *m, int *y);

int main(void) {
  int d = 12, m = 4, y = 2024;
  add_and_print(&d, &m, &y);

  d = 28, m = 2, y = 2024;
  add_and_print(&d, &m, &y);

  d = 28, m = 2, y = 2023;
  add_and_print(&d, &m, &y);

  d = 31, m = 12, y = 1999;
  add_and_print(&d, &m, &y);

  return 0;
}

int leap(int y) { return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0); }

void add_and_print(int *d, int *m, int *y) {
  printf("Current date: %02d/%02d/%d\n", *d, *m, *y);
  if (add_day(d, m, y))
    printf("Updated date: %02d/%02d/%d\n", *d, *m, *y);
  else
    printf("Invalid date\n");
}

int add_day(int *d, int *m, int *y) {
  if (*m < 1 || *m > 12)
    return 0;

  int days = *m == 2 ? (leap(*y) ? 29 : 28) : month_length[(*m) - 1];
  if (*d < 1 || *d > days)
    return 0;

  if (*d == days) {
    *d = 1;
    if (*m == 12) {
      *m = 1;
      (*y)++;
    } else {
      (*m)++;
    }
  } else {
    (*d)++;
  }

  return 1;
}
