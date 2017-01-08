#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>

/**
 * Data type definitions
 */
typedef enum expr_node_en {
  Node_Invalid = 0,
  Node_Empty,
  Node_Terminal,
  Node_Non_Terminal,
  Node_Sequence,
  Node_Choice,
  Node_Zero_Or_More,
  Node_One_Or_More,
  Node_Optional,
  Node_And,
  Node_Not
} expr_node_t;

typedef struct expr_st {
  enum expr_node_en type;
  char *data;
  struct expr_st *left;
  struct expr_st *right;
} expr_t;

/**
 * Constructors and memory management
 */
void expr_free(expr_t *node);
expr_t *empty();
expr_t *terminal(const char *t);
expr_t *non_terminal(const char *nt);
expr_t *sequence(expr_t *left, expr_t *right);
expr_t *zero_or_more(expr_t *expr);
expr_t *one_or_more(expr_t *expr);
expr_t *choice(expr_t *left, expr_t *right);
expr_t *optional(expr_t *expr);
expr_t *and(expr_t *expr);
expr_t *not(expr_t *expr);
bool isa(expr_t *node, expr_node_t type);

/**
 * Printing expression trees
 */
const char *expr_name(expr_t *node);
void print_expr(expr_t *node);
void print_expr_indented(expr_t *node, int indent);

#endif
