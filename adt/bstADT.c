#include <stdlib.h>
#include "bstADT.h"

#define BLOCK_SIZE 256
#define IT_MAX_SIZE 256

typedef struct bst_node {
  bst_elem_t value;

  struct bst_node *left;
  struct bst_node *right;
} bst_node;

typedef struct bstCDT {
  bst_comp_fn comp;
  bst_node *root;

  // TODO these should be implemented in the heap to remove the size limit
  bst_node *it_stack[IT_MAX_SIZE];
  size_t it_idx;
} bstCDT;

/**
 * Create an empty BST
 * @param comp comparator function to use
 * @return pointer to a new BST
 */
bstADT bst_new(bst_comp_fn comp) {
  bstADT bst = calloc(1, sizeof(bstCDT));
  bst->comp = comp;
  return bst;
}

/**
 * Free a BST node and its children recursively
 * @param node
 */
static void free_node(bst_node *node) {
  if (node) {
    free_node(node->left);
    free_node(node->right);
    free(node);
  }
}

/**
 * Free all resources allocated by a BST
 * @param bst
 */
void bst_free(bstADT bst) {
  free_node(bst->root);
  free(bst);
}

/**
 * Get the size of a node and its children recursively
 * @param node
 */
static size_t node_size(bst_node *node) {
  if (!node) return 0;
  return 1 + node_size(node->left) + node_size(node->right);
}

/**
 * Get the number of elements in a BST
 * @param bst
 */
size_t bst_size(const bstADT bst) {
  return node_size(bst->root);
}

/**
 * Get max of two numbers
 */
static size_t max(size_t lhs, size_t rhs) {
  return lhs > rhs ? lhs : rhs;
}

/**
 * Get the height of a node and its children recursively
 * @param node
 */
static size_t node_height(bst_node *node) {
  if (!node) return 0;
  return 1 + max(node_height(node->left), node_height(node->right));
}

/**
 * Get the height of a BST
 * @param bst
 * @return height of the tree (max level from root)
 */
size_t bst_height(const bstADT bst) {
  return node_height(bst->root);
}

/**
 * Test for inclusion of a value in a BST node recursively
 * @param node node to test
 * @param elem element to find
 * @param comp comparator func
 * @return 1 if found, 0 if not
 */
static int node_belongs(bst_node *node, bst_elem_t elem, bst_comp_fn comp) {
  if (!node) return 0;
  int cmp_res = comp(elem, node->value);
  if (!cmp_res) return 1;
  if (cmp_res > 0) return node_belongs(node->right, elem, comp);
  return node_belongs(node->left, elem, comp);
}

/**
 * Test for inclusion of an element in the BST
 * @param bst
 * @param elem element to find
 * @return 1 if elem is included in bst, 0 otherwise
 */
int bst_belongs(const bstADT bst, bst_elem_t elem) {
  return node_belongs(bst->root, elem, bst->comp);
}

/**
 * Create a new empty BST node
 * @param value
 * @return a node with value "value" and no children
 */
static bst_node *new_node(bst_elem_t value) {
  bst_node *node = malloc(sizeof(bst_node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/**
 * Insert a node into the tree recursively
 * @param root root node of the tree
 * @param elem element to insert
 * @param comp comparator function
 * @param found (out) 1 if the element is already in tree, 0 otherwise
 * @return pointer to the new root of the tree, might be different
 */
static bst_node *node_insert(
  bst_node *root,
  bst_elem_t elem,
  bst_comp_fn comp,
  int *found
) {
  if (!root) return new_node(elem);

  int cmp_res = comp(elem, root->value);
  if (!cmp_res) {
    *found = 1;
  } else if (cmp_res > 0) {
    root->right = node_insert(root->right, elem, comp, found);
  } else {
    root->left = node_insert(root->left, elem, comp, found);
  }
  return root;
}

/**
 * Insert an element into the BST if not already included
 * @param bst
 * @param elem
 * @return 1 if successfully inserted, 0 if elem was already in the tree
 */
int bst_insert(bstADT bst, bst_elem_t elem) {
  int found = 0;
  bst->root = node_insert(bst->root, elem, bst->comp, &found);
  return !found;
}

/**
 * Find the smallest element in a tree
 * @param root
 */
static bst_node *find_smallest(bst_node *root) {
  if (!root->left) return root;
  return find_smallest(root->left);
}

static bst_node *node_remove(
  bst_node *root,
  bst_elem_t elem,
  bst_comp_fn comp,
  int *removed
);

/**
 * Delete the root node of a BST
 * @param node
 * @param comp
 * @return oew root
 */
static bst_node *node_delete(bst_node *node, bst_comp_fn comp) {
  // Replace with left child if only child (NULL if no children)
  if (!node->right) {
    bst_node *ret = node->left;
    free(node);
    return ret;
  }
  if (!node->left) { // Only right child
    bst_node *ret = node->right;
    free(node);
    return ret;
  }

  // If the node has both left and right children: find node with smallest value
  // in right subtree, replace, delete
  bst_node *smallest_right_descendant = find_smallest(node->right);
  node->value = smallest_right_descendant->value;
  node->right = node_remove(
    node->right,
    smallest_right_descendant->value,
    comp,
    NULL);
  return node;
}

/**
 * Remove a node from a tree recursively
 * @param root root node of the tree
 * @param elem element to remove
 * @param comp comparator function
 * @param removed (out) 1 if the element was removed, 0 if it was not in the tree
 * @return new root of the tree
 */
static bst_node *node_remove(
  bst_node *root,
  bst_elem_t elem,
  bst_comp_fn comp,
  int *removed
) {
  if (!root) return NULL;
  int cmp_res = comp(elem, root->value);
  if (!cmp_res) {
    if (removed) *removed = 1;
    return node_delete(root, comp);
  }
  if (cmp_res > 0) {
    root->right = node_remove(root->right, elem, comp, removed);
  } else {
    root->left = node_remove(root->left, elem, comp, removed);
  }
  return root;
}

/**
 * Remove an element from the BST
 * @param bst
 * @param elem
 * @return 1 if the element was removed, 0 if it was not included
 */
int bst_remove(bstADT bst, bst_elem_t elem) {
  int removed = 0;
  bst->root = node_remove(bst->root, elem, bst->comp, &removed);
  return removed;
}

/**
 * Helper function: add elem to a dynamic array, grow as needed
 * @param elem
 * @param vec
 * @param size
 */
static void add_elem(bst_elem_t elem, bst_elem_t **vec, size_t *size) {
  if (*size % BLOCK_SIZE == 0) {
    *vec = realloc(*vec, (*size + BLOCK_SIZE) * sizeof(bst_elem_t));
  }

  (*vec)[(*size)++] = elem;
}

/**
 * Fill an array with the in-order traversal of a tree
 * @param root
 * @param out (out) output dynamic array, contains the in-order traversal
 * @param out_size (out) ouput array size
 */
static void node_inorder(
  const bst_node *root,
  bst_elem_t **out,
  size_t *out_size
) {
  if (root) {
    node_inorder(root->left, out, out_size);
    add_elem(root->value, out, out_size);
    node_inorder(root->right, out, out_size);
  }
}

/**
 * Fill an array with the in-order traversal of the BST
 * @param bst
 * @return an array containing the elements of the BST in in-order
 */
bst_elem_t *bst_inorder(const bstADT bst) {
  bst_elem_t *vec = NULL;
  size_t vec_size = 0;
  node_inorder(bst->root, &vec, &vec_size);
  vec = realloc(vec, vec_size * sizeof(bst_elem_t)); // resize to fit
  return vec;
}

/**
 * Fill an array with the pre-order traversal of a tree
 * @param root
 * @param out (out) output dynamic array, contains the pre-order traversal
 * @param out_size (out) ouput array size
 */
static void node_preorder(
  const bst_node *root,
  bst_elem_t **out,
  size_t *out_size
) {
  if (root) {
    add_elem(root->value, out, out_size);
    node_preorder(root->left, out, out_size);
    node_preorder(root->right, out, out_size);
  }
}

/**
 * Fill an array with the pre-order traversal of the BST
 * @param bst
 * @return an array containing the elements of the BST in pre-order
 */
bst_elem_t *bst_preorder(const bstADT bst) {
  bst_elem_t *vec = NULL;
  size_t vec_size = 0;
  node_preorder(bst->root, &vec, &vec_size);
  vec = realloc(vec, vec_size * sizeof(bst_elem_t)); // resize to fit
  return vec;
}

/**
 * Fill an array with the post-order traversal of a tree
 * @param root
 * @param out (out) output dynamic array, contains the post-order traversal
 * @param out_size (out) ouput array size
 */
static void node_postorder(
  const bst_node *root,
  bst_elem_t **out,
  size_t *out_size
) {
  if (root) {
    node_postorder(root->left, out, out_size);
    node_postorder(root->right, out, out_size);
    add_elem(root->value, out, out_size);
  }
}

/**
 * Fill an array with the post-order traversal of the BST
 * @param bst
 * @return an array containing the elements of the BST in post-order
 */
bst_elem_t *bst_postorder(const bstADT bst) {
  bst_elem_t *vec = NULL;
  size_t vec_size = 0;
  node_postorder(bst->root, &vec, &vec_size);
  vec = realloc(vec, vec_size * sizeof(bst_elem_t)); // resize to fit
  return vec;
}

/**
 * Check if a BST is height-balanced (left and right subtrees have a height difference <= 1)
 * @param bst
 * @return 1 if balanced, 0 if not
 */
int bst_is_height_balanced(const bstADT bst) {
  if (!bst->root) return 1;

  int diff =
    (int) node_height(bst->root->left) - (int) node_height(bst->root->right);
  return diff <= 1 && diff >= -1;
}

static void push_in(bstADT bst, bst_node *node) {
  if (!node) return;

  if (node->right) push_in(bst, node->right);
  bst->it_stack[bst->it_idx++] = node;
  if (node->left) push_in(bst, node->left);
}

void bst_begin_in(bstADT bst) {
  push_in(bst, bst->root);
}

static void push_pre(bstADT bst, bst_node *node) {
  if (!node) return;

  if (node->right) push_pre(bst, node->right);
  if (node->left) push_pre(bst, node->left);
  bst->it_stack[bst->it_idx++] = node;
}

void bst_begin_pre(bstADT bst) {
  push_pre(bst, bst->root);
}

static void push_post(bstADT bst, bst_node *node) {
  if (!node) return;

  bst->it_stack[bst->it_idx++] = node;
  if (node->right) push_post(bst, node->right);
  if (node->left) push_post(bst, node->left);
}

void bst_begin_post(bstADT bst) {
  push_post(bst, bst->root);
}

int bst_has_next(const bstADT bst) {
  return bst->it_idx > 0;
}

bst_elem_t bst_next(bstADT bst) {
  bst_node *top = bst->it_stack[--bst->it_idx];
  return top->value;
}
