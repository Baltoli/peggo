#ifndef EXPRESSION_H
#define EXPRESSION_H

typedef enum peg_expr_node_en {
  Node_Terminal,
  Node_Non_Terminal,
  Node_Empty,
  Node_Sequence,
  Node_Choice,
  Node_Zero_Or_More,
  Node_One_Or_More,
  Node_Optional,
  Node_And,
  Node_Or,
  Node_Invalid
} peg_expr_node_t;

typedef struct peg_expr_st {
  enum peg_expr_node_en type;
  char *data;
  struct peg_expr_st *left;
  struct peg_expr_st *right;
} peg_expr_t;

peg_expr_t *peg_init();
peg_expr_t *peg_empty();

#endif
