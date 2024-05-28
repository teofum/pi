#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <bstADT.h>

int comp(int lhs, int rhs) {
  return lhs - rhs;
}

int main(void) {
  bstADT tree = bst_new(comp);
  assert(bst_size(tree) == 0);
  assert(bst_height(tree) == 0);

  assert(bst_insert(tree, 50) == 1);
  assert(bst_height(tree) == 1);
  int *ord = bst_inorder(tree);
  assert(ord[0] == 50);
  free(ord);

  assert(bst_insert(tree, 20) == 1);
  assert(bst_height(tree) == 2);
  assert(bst_insert(tree, 70) == 1);
  assert(bst_insert(tree, 10) == 1);
  assert(bst_insert(tree, 25) == 1);

  assert(bst_belongs(tree, 50));
  assert(bst_belongs(tree, 20));
  assert(bst_belongs(tree, 70));
  assert(bst_belongs(tree, 10));
  assert(bst_belongs(tree, 70));
  assert(!bst_belongs(tree, 5));
  assert(!bst_belongs(tree, -5));
  assert(!bst_belongs(tree, 100));

  assert(bst_size(tree) == 5);
  assert(bst_height(tree) == 3);

  ord = bst_inorder(tree);
  assert(ord[0] == 10);
  assert(ord[1] == 20);
  assert(ord[2] == 25);
  assert(ord[3] == 50);
  assert(ord[4] == 70);
  free(ord);

  bst_begin_in(tree);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 10);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 20);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 25);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 50);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 70);
  assert(bst_has_next(tree) == 0);

  ord = bst_preorder(tree);
  assert(ord[0] == 50);
  assert(ord[1] == 20);
  assert(ord[2] == 10);
  assert(ord[3] == 25);
  assert(ord[4] == 70);
  free(ord);

  bst_begin_pre(tree);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 50);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 20);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 10);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 25);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 70);
  assert(bst_has_next(tree) == 0);

  ord = bst_postorder(tree);
  assert(ord[0] == 10);
  assert(ord[1] == 25);
  assert(ord[2] == 20);
  assert(ord[3] == 70);
  assert(ord[4] == 50);
  free(ord);

  bst_begin_post(tree);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 10);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 25);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 20);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 70);
  assert(bst_has_next(tree) == 1);
  assert(bst_next(tree) == 50);
  assert(bst_has_next(tree) == 0);

  assert(bst_remove(tree, 100) == 0);
  assert(bst_remove(tree, 20) == 1);

  ord = bst_inorder(tree);
  assert(ord[0] == 10);
  assert(ord[1] == 25);
  assert(ord[2] == 50);
  assert(ord[3] == 70);
  free(ord);

  assert(bst_is_height_balanced(tree) == 1);

  bst_free(tree);

  puts("You nailed it !!!");
  return 0;
}
