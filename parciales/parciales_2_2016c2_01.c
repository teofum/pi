#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include <llist.h>

llist delete_all(llist l, llist m) {
  if (l == NULL || m == NULL) return l;
  if (l->elem == m->elem) {
    llist tail = l->tail;
    free(l);
    return delete_all(tail, m->tail);
  }
  if (l->elem > m->elem) return delete_all(l, m->tail);

  l->tail = delete_all(l->tail, m);
  return l;
}

int main(void) {
  int a1[] = {1, 2, 3, 4, 5, 6, 7};
  int a2[] = {0, 1, 3, 5, 10, 11, 14};
  llist l = from_array(a1, 7);
  llist m = from_array(a2, 7);

  l = delete_all(l, m);

  int res[] = {2, 4, 6, 7};
  assert(check_elems(l, res, 4));
  puts("OK");

  list_free(l);
  list_free(m);
  return 0;
}
