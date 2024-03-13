#include <stdio.h>

#define HEADER_COL_WIDTH 5
#define COLUMN_WIDTH 10

#define N 20

void print_row(int n);

int main(void) {
  // Print header
  printf(
      "%-*s%-*s%-*s%-*s\n\n", //
      HEADER_COL_WIDTH, "N",  //
      COLUMN_WIDTH, "10*N",   //
      COLUMN_WIDTH, "100*N",  //
      COLUMN_WIDTH, "1000*N"
  );

  for (int i = 1; i <= N; i++)
    print_row(i);

  return 0;
}

void print_row(int n) {
  printf(
      "%-*d%-*d%-*d%-*d\n",  //
      HEADER_COL_WIDTH, n,   //
      COLUMN_WIDTH, 10 * n,  //
      COLUMN_WIDTH, 100 * n, //
      COLUMN_WIDTH, 1000 * n
  );
}
