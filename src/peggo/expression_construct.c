#include <stdlib.h>
#include <string.h>

#include "expression.h"

peg_expr_t *peg_expr_init(peg_expr_node_t type) {
  peg_expr_t *node = malloc(sizeof(*node));
  if(!node) {
    exit(EXIT_FAILURE);
  }

  node->type = type;
  node->data = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void peg_expr_free(peg_expr_t *node) {
  if(!node) {
    return;
  }

  if(node->data) {
    free(node->data);
  }

  if(node->left) {
    peg_expr_free(node->left);
  }

  if(node->right) {
    peg_expr_free(node->right);
  }
}

void peg_init_data(peg_expr_t *node, const char *s) {
  if(node->data) {
    free(node->data);
  }

  node->data = malloc(strlen(s) + 1);
  if(!node->data) {
    exit(EXIT_FAILURE);
  }

  strcpy(node->data, s);
}

void peg_init_left(peg_expr_t *node, peg_expr_t *left) {
  if(node->left) {
    peg_expr_free(node->left);
  }

  node->left = left;
}

void peg_init_right(peg_expr_t *node, peg_expr_t *right) {
  if(node->right) {
    peg_expr_free(node->right);
  }

  node->right = right;
}

peg_expr_t *peg_empty() {
  return peg_expr_init(Node_Empty);
}

peg_expr_t *peg_terminal(const char *t) {
  peg_expr_t *node = peg_expr_init(Node_Terminal);
  peg_init_data(node, t);
  return node;
}

peg_expr_t *peg_non_terminal(const char *nt) {
  peg_expr_t *node = peg_expr_init(Node_Non_Terminal);
  peg_init_data(node, nt);
  return node;
}

peg_expr_t *peg_sequence(peg_expr_t *left, peg_expr_t *right) {
  peg_expr_t *node = peg_expr_init(Node_Sequence);
  peg_init_left(node, left);
  peg_init_right(node, right);
  return node;
}

peg_expr_t *peg_zero_or_more(peg_expr_t *expr) {
  peg_expr_t *node = peg_expr_init(Node_Zero_Or_More);
  peg_init_left(node, expr);
  return node;
}

peg_expr_t *peg_one_or_more(peg_expr_t *expr) {
  peg_expr_t *node = peg_expr_init(Node_One_Or_More);
  peg_init_left(node, expr);
  return node;
}

peg_expr_t *peg_choice(peg_expr_t *left, peg_expr_t *right) {
  peg_expr_t *node = peg_expr_init(Node_Choice);
  peg_init_left(node, left);
  peg_init_right(node, right);
  return node;
}

peg_expr_t *peg_optional(peg_expr_t *expr) {
  peg_expr_t *node = peg_expr_init(Node_Optional);
  peg_init_left(node, expr);
  return node;
}

peg_expr_t *peg_and(peg_expr_t *left, peg_expr_t *right) {
  peg_expr_t *node = peg_expr_init(Node_And);
  peg_init_left(node, left);
  peg_init_right(node, right);
  return node;
}

peg_expr_t *peg_not(peg_expr_t *expr) {
  peg_expr_t *node = peg_expr_init(Node_Not);
  peg_init_left(node, expr);
  return node;
}

bool isa(peg_expr_t *node, peg_expr_node_t type) {
  return node->type == type;
}
