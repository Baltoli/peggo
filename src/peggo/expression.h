#ifndef EXPRESSION_H
#define EXPRESSION_H

/**
 * Data type definitions
 */
typedef enum peg_expr_node_en {
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
} peg_expr_node_t;

typedef struct peg_expr_st {
  enum peg_expr_node_en type;
  char *data;
  struct peg_expr_st *left;
  struct peg_expr_st *right;
} peg_expr_t;

/**
 * Constructors and memory management
 */
void peg_free(peg_expr_t *node);
peg_expr_t *peg_empty();
peg_expr_t *peg_terminal(const char *t);
peg_expr_t *peg_non_terminal(const char *nt);
peg_expr_t *peg_sequence(peg_expr_t *left, peg_expr_t *right);
peg_expr_t *peg_zero_or_more(peg_expr_t *expr);
peg_expr_t *peg_one_or_more(peg_expr_t *expr);
peg_expr_t *peg_choice(peg_expr_t *left, peg_expr_t *right);
peg_expr_t *peg_optional(peg_expr_t *expr);
peg_expr_t *peg_and(peg_expr_t *left, peg_expr_t *right);
peg_expr_t *peg_not(peg_expr_t *expr);

/**
 * Printing expression trees
 */
const char *peg_expr_name(peg_expr_t *node);

#endif
