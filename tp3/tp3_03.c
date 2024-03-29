#include <stdio.h>

#include "my_getnum.h"

#define BASE_WAGE 300
#define SALES_THRESHOLD_1 1000
#define SALES_COMMISSION_1 0.05
#define SALES_THRESHOLD_2 2000
#define SALES_COMMISSION_2 0.07
#define SALES_THRESHOLD_3 4000
#define SALES_COMMISSION_3 0.09

int main(void) {
  double sales = -1, commission = 0;
  do {
    sales = get_double("Enter weekly sales amount: ");
  } while (sales < 0);

  if (sales > SALES_THRESHOLD_3)
    commission = sales * SALES_COMMISSION_3;
  else if (sales > SALES_THRESHOLD_2)
    commission = sales * SALES_COMMISSION_2;
  else if (sales > SALES_THRESHOLD_1)
    commission = sales * SALES_COMMISSION_1;

  printf("Weekly wage: $%d\n", BASE_WAGE + commission);
}
