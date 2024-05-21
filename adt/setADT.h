typedef struct setCDT *setADT;

typedef const char *set_elem_t;

typedef int (*set_comp_fn)(set_elem_t, set_elem_t);

setADT set_new(set_comp_fn comp);

void set_free(setADT set);

setADT set_union(setADT a, setADT b);

setADT set_intersection(setADT a, setADT b);

setADT set_diff(setADT a, setADT b);

int set_includes(setADT set, set_elem_t elem);

size_t set_size(setADT set);

int set_empty(setADT set);

int set_insert(setADT set, set_elem_t elem);

void set_remove(setADT set, set_elem_t elem);
