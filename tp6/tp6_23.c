#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LEN 10 // dd/mm/yyyy
#define isleap(year) (!((year) % 400) || ((year) % 100 && !((year) % 4)))

typedef unsigned int uint;

static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int parse_date(const char *date, uint *d, uint *m, uint *y);

int main(void) {
  unsigned int d = 100, m = 200, y = 300;
  int res;

  res = parse_date("", &d, &m, &y);
  assert(res == 0);
  assert(d == 100);
  assert(m == 200);
  assert(y == 300);

  res = parse_date("29/02/1999", &d, &m, &y);
  assert(res == 0);
  assert(d == 100);
  assert(m == 200);
  assert(y == 300);

  res = parse_date("30/14/2020", &d, &m, &y);
  assert(res == 0);
  assert(d == 100);
  assert(m == 200);
  assert(y == 300);

  res = parse_date("12/12/", &d, &m, &y);
  assert(res == 0);
  assert(d == 100);
  assert(m == 200);
  assert(y == 300);

  res = parse_date("1/1/2000", &d, &m, &y);
  assert(res == 0);
  assert(d == 100);
  assert(m == 200);
  assert(y == 300);

  res = parse_date("12/01/2000", &d, &m, &y);
  assert(res == 1);
  assert(d == 12);
  assert(m == 1);
  assert(y == 2000);

  res = parse_date("29/02/1900", &d, &m, &y);
  assert(res == 0);
  assert(d == 12);
  assert(m == 1);
  assert(y == 2000);

  res = parse_date("29/02/2000", &d, &m, &y);
  assert(res == 1);
  assert(d == 29);
  assert(m == 2);
  assert(y == 2000);

  puts("All OK!");
  return 0;
}

int parse_date(const char *date, uint *d, uint *m, uint *y) {
  int len = strlen(date);
  if (len != DATE_LEN)
    return 0;

  uint day = atoi(date);
  uint month = atoi(date + 3);
  uint year = atoi(date + 6);

  // Validate month
  if (month > 12)
    return 0;

  // Validate day
  int max_day = (month == 2 && isleap(year)) ? 29 : days[month - 1];
  if (day > max_day)
    return 0;

  *d = day;
  *m = month;
  *y = year;

  return 1;
}
