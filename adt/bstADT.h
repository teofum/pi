#ifndef _bstADT_h_
#define _bstADT_h_

typedef int bst_elem_t;

typedef int (*bst_comp_fn)(bst_elem_t elem1, bst_elem_t elem2);

typedef struct bstCDT *bstADT;

bstADT bst_new(bst_comp_fn comp);

void bst_free(bstADT bst);

size_t bst_size(const bstADT bst);

size_t bst_height(const bstADT bst);

int bst_belongs(const bstADT bst, bst_elem_t elem);

int bst_insert(bstADT bst, bst_elem_t elem);

int bst_remove(bstADT bst, bst_elem_t elem);

bst_elem_t *bst_inorder(const bstADT bst);

bst_elem_t *bst_preorder(const bstADT bst);

bst_elem_t *bst_postorder(const bstADT bst);

int bst_is_height_balanced(const bstADT bst);

void bst_begin_in(bstADT bst);

void bst_begin_pre(bstADT bst);

void bst_begin_post(bstADT bst);

int bst_has_next(const bstADT bst);

bst_elem_t bst_next(bstADT bst);

#endif
