#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <skipListADT.h>
#include <random.h>

int compare_int(int n1, int n2) {
  return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
}

int main(void) {
  seed_with_timestamp();
  skipListADT list = sk_new(10, compare_int);

  sk_insert(list, 3);
  sk_insert(list, 3);
  sk_insert(list, 19);
  sk_insert(list, 3);
  sk_insert(list, 17);

  assert(sk_search(list, 19));
  assert(sk_search(list, 3));
  assert(sk_search(list, 17));
  assert(!sk_search(list, 1));
  assert(!sk_search(list, -3));
  assert(!sk_search(list, 100));

  sk_begin(list);
  assert(sk_has_next(list));
  assert(sk_next(list) == 3);
  assert(sk_next(list) == 3);
  assert(sk_next(list) == 3);
  assert(sk_next(list) == 17);
  assert(sk_next(list) == 19);
  assert(!sk_has_next(list));

  sk_display(list);

  for (int i = 0; i < 100; i++) {
    sk_insert(list, random_int(0, 199));
  }

  sk_display(list);
  putchar('\n');
  sk_free(list);

  // Probamos de un solo nivel
  list = sk_new(1, compare_int);
  for (int i = 0; i < 50; i++) {
    sk_insert(list, random_int(0, 99));
  }

  sk_display(list);
  putchar('\n');
  sk_free(list);

  puts("OK!");
  return 0;
}
