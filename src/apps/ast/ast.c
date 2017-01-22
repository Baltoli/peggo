#include <stdlib.h>

#include "ast.h"

ast_t *literal(long long v) {
  ast_t *node = malloc(sizeof(*node));
  if(!node) {
    exit(EXIT_FAILURE);
  }

  node->type = LEAF;
  node->value = v;

  return node;
}

ast_t *op(ast_t *left, op_type ty, ast_t *right) {
  ast_t *node = malloc(sizeof(*node));
  if(!node) {
    exit(EXIT_FAILURE);
  }

  node->type = BRANCH;
  node->left = left;
  node->right = right;

  return node;
}

void ast_free(ast_t *node) {
  if(!node) {
    return;
  }

  if(node->type == BRANCH) {
    ast_free(node->left);
    ast_free(node->right);
  }

  free(node);
}
