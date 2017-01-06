#include <stdlib.h>
#include <string.h>

#include "expression.h"

peg_expr_t *peg_init() {
  peg_expr_t *node = malloc(sizeof(*node));
  node->type = Node_Invalid;
  node->data = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void peg_free(peg_expr_t *node) {
  if(!node) {
    return;
  }

  if(node->data) {
    free(node->data);
  }

  if(node->left) {
    peg_free(node->left);
  }

  if(node->right) {
    peg_free(node->right);
  }
}

peg_expr_t *peg_empty() {
  peg_expr_t *node = peg_init();
  node->type = Node_Empty;
  return node;
}

peg_expr_t *peg_terminal(const char *t) {
  peg_expr_t *node = peg_init();
  node->type = Node_Terminal;
  node->data = malloc((sizeof(char) * strlen(t)) + 1);
  strcpy(node->data, t);
  return node;
}
