#ifndef _llist_h
#define _llist_h

typedef int list_t;

#define DEF_LIST_TYPE(t) typedef t list_t;

typedef struct node *llist;

typedef struct node {
  list_t elem;
  llist tail;
} lnode;

int list_empty(llist l);

llist list_new(list_t value);

llist from_array(list_t *arr, size_t size);

list_t list_get(llist l, size_t i);

llist list_delete(llist l);

void list_free(llist l);

int check_elems(llist l, const list_t *v, size_t size);

#endif
