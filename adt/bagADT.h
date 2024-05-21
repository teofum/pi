#ifndef _bagADT_h
#define _bagADT_h

typedef struct bagCDT *bagADT;

typedef const char *bag_elem_t;

typedef int (*bag_comp_fn)(bag_elem_t, bag_elem_t);

bagADT bag_new(bag_comp_fn comp);

void bag_free(bagADT bag);

bagADT bag_union(bagADT a, bagADT b);

bagADT bag_intersection(bagADT a, bagADT b);

bagADT bag_diff(bagADT a, bagADT b);

int bag_count(bagADT bag, bag_elem_t elem);

size_t bag_size(bagADT bag);

int bag_empty(bagADT bag);

unsigned bag_insert(bagADT bag, bag_elem_t elem);

unsigned bag_remove(bagADT bag, bag_elem_t elem);

bag_elem_t bag_highest(bagADT bag);

#endif
