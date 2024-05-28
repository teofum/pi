#include <stdlib.h>
#include "bstADT.h"

#define BLOCK_SIZE 256

typedef struct bst_node {
  bst_elem_t value;

  struct bst_node *left;
  struct bst_node *right;
} bst_node;

typedef struct bstCDT {
  bst_comp_fn comp;
  bst_node *root;
} bstCDT;

/**
 * Create an empty BST
 * @param comp comparator function to use
 * @return pointer to a new BST
 */
bstADT bst_new(bst_comp_fn comp) {
  bstADT bst = malloc(sizeof(bstCDT));
  bst->root = NULL;
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

static void add_elem(bst_elem_t elem, bst_elem_t **vec, size_t *size) {
  if (*size % BLOCK_SIZE == 0) {
    *vec = realloc(*vec, (*size + BLOCK_SIZE) * sizeof(bst_elem_t));
  }

  (*vec)[(*size)++] = elem;
}

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
 *
 * @param bst
 * @return
 */
bst_elem_t *bst_inorder(const bstADT bst) {
  bst_elem_t *vec = NULL;
  size_t vec_size = 0;
  node_inorder(bst->root, &vec, &vec_size);
  return vec;
}
