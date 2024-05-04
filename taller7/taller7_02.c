#include <stdio.h>
#include <stdlib.h>

#include "my_getnum.h"

#define ITEM_COUNT 2
#define MAX_LEN 10

typedef struct {
  int code;
  char desc[MAX_LEN];
  float price;
} item;

typedef item bill[ITEM_COUNT];

void read_item(item *it);

void read(bill bill, int count);

float get_total(bill bill, int count);

int main(void) {
  bill f;
  read(f, ITEM_COUNT);
  printf("%.2f", get_total(f, ITEM_COUNT));
  return 0;
}

void read_item(item *it) {
  it->code = get_int("Enter product code: ");
  printf("Enter product name (9 char max): ");
  scanf("%9s", it->desc);
  it->price = get_float("Enter price for %s: ", it->desc);
}

void read(bill bill, int count) {
  for (int i = 0; i < count; i++)
    read_item(&bill[i]);
}

float get_total(bill bill, int count) {
  float total = 0;
  for (int i = 0; i < count; i++)
    total += bill[i].price;

  return total;
}
