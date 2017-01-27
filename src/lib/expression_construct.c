#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "log.h"

expr_t *expr_init(expr_node_t type) {
  expr_t *node = malloc(sizeof(*node));
  if(!node) {
    fatal_error("Could not allocate memory for parsing expression");
  }

  node->type = type;
  node->data = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void expr_free(expr_t *node) {
  if(!node) {
    return;
  }

  if(node->data) {
    free(node->data);
  }

  if(node->left) {
    expr_free(node->left);
  }

  if(node->right) {
    expr_free(node->right);
  }
}

void init_data(expr_t *node, const char *s) {
  if(node->data) {
    free(node->data);
  }

  node->data = malloc(strlen(s) + 1);
  if(!node->data) {
    fatal_error("Could not allocate memory for parsing expression symbol");
  }

  strcpy(node->data, s);
}

void init_left(expr_t *node, expr_t *left) {
  if(node->left) {
    expr_free(node->left);
  }

  node->left = left;
}

void init_right(expr_t *node, expr_t *right) {
  if(node->right) {
    expr_free(node->right);
  }

  node->right = right;
}

expr_t *empty() {
  return expr_init(Node_Empty);
}

expr_t *terminal(const char *t) {
  expr_t *node = expr_init(Node_Terminal);
  init_data(node, t);
  return node;
}

expr_t *non_terminal(const char *nt) {
  expr_t *node = expr_init(Node_Non_Terminal);
  init_data(node, nt);
  return node;
}

expr_t *sequence(expr_t *left, expr_t *right) {
  expr_t *node = expr_init(Node_Sequence);
  init_left(node, left);
  init_right(node, right);
  return node;
}

expr_t *zero_or_more(expr_t *expr) {
  expr_t *node = expr_init(Node_Zero_Or_More);
  init_left(node, expr);
  return node;
}

expr_t *one_or_more(expr_t *expr) {
  expr_t *node = expr_init(Node_One_Or_More);
  init_left(node, expr);
  return node;
}

expr_t *choice(expr_t *left, expr_t *right) {
  expr_t *node = expr_init(Node_Choice);
  init_left(node, left);
  init_right(node, right);
  return node;
}

expr_t *optional(expr_t *expr) {
  expr_t *node = expr_init(Node_Optional);
  init_left(node, expr);
  return node;
}

expr_t *and(expr_t *expr) {
  expr_t *node = expr_init(Node_And);
  init_left(node, expr);
  return node;
}

expr_t *not(expr_t *expr) {
  expr_t *node = expr_init(Node_Not);
  init_left(node, expr);
  return node;
}

bool isa(expr_t *node, expr_node_t type) {
  return node->type == type;
}
