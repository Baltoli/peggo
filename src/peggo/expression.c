#include <stdlib.h>

#include "expression.h"

peg_expr_t *peg_init() {
  peg_expr_t *node = malloc(sizeof(*node));
  node->type = Node_Invalid;
  node->data = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

peg_expr_t *peg_empty() {
  peg_expr_t *node = peg_init();
  node->type = Node_Empty;
  return node;
}
